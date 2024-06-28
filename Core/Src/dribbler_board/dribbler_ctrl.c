/* 
The dribbler control of RoboTeam Twente
Created by Chris Krommendijk

To ask:
- What is the unit of the Current sensor
*/

#include "dribbler_ctrl.h"
//#include "roboteam_microcontroller6.0\Core\Src\dribbler_board\peripherals\dribbler.c" // Include the dribbler.c file to get the functions for the dribbler motor
void DribblerController()
{
	// Motor speed is computed from output current (measured) and voltage (controlled)
	// DCX 19 S Graphite Brushes 24V DC motor ∅19 mm
	int32_t avgVoltageDribbler = datactrl.avgVoltage*1000; // [mV] 
	int32_t avgCurrentDribbler = dribbler_getCurrent()*1000; // [mA]

	int32_t motorResistance = 22.8; // [Ohm] (5.84 Ohm)
	int32_t motorBackEmfConstantInv = 28.06; // [rad/(V*s)] is the speed constant 268 rpm/V = 28.06 rad/(V*s) in the datasheet

	int32_t restiveLossDribbler = (motorResistance * avgCurrentDribbler) >> 6;
	int32_t backEmfDribbler = avgVoltageDribbler - restiveLossDribbler; // [mV]

	if(backEmfDribbler > 32767) // This is the maximum value of a signed 16-bit integer divided by 2
		backEmfDribbler = 32767;

	if(backEmfDribbler < -32768)
		backEmfDribbler = -32768;

	int32_t modelSpeed = (backEmfDribbler * motorBackEmfConstantInv) >> 2; // [mrad/s]
	modelSpeed = modelSpeed >> 10; // [1000/1024 rad/s]

	// Q current input is used as limit for speed controller
	int32_t q_S12_0 = data.command.input[1];
	q_S12_0 = (q_S12_0*24855) >> 16; // Input +-10800mA, scale down  to +-4096
	if(q_S12_0 < 0)
	{
		data.ctrl.speed.outputMin = q_S12_0;
		data.ctrl.speed.outputMax = -q_S12_0;
	}
	else
	{
		data.ctrl.speed.outputMin = -q_S12_0;
		data.ctrl.speed.outputMax = q_S12_0;
	}

	if(data.command.encDeltaSetpoint > -50 && data.command.encDeltaSetpoint < 50)
	{
		// Setpoint close to zero, spin down to zero and go to voltage mode
		if(modelSpeed_S15_0 > -50 && modelSpeed_S15_0 < 50)
		{
			// Low speed, switch to constant voltage
			data.motor.Udq[1] = 0;

			PICtrlS12Enable(&data.ctrl.currentQ, 0);

			data.ctrl.speed.output = (data.sensors.adc.currentDQ_S16_0[1]*24855) >> 16;
			data.ctrl.currentQ.output = data.motor.Udq[1] >> 3;
		}
		else
		{
			// encDeltaSetpoint is used as hall speed setpoint
			PICtrlS12Setpoint(&data.ctrl.speed, 0);
			PICtrlS12Enable(&data.ctrl.speed, 1);
			PICtrlS12Update(&data.ctrl.speed, modelSpeed_S15_0);

			// Apply output to Q current controller input
			PICtrlS12Setpoint(&data.ctrl.currentQ, data.ctrl.speed.output);
			PICtrlS12Enable(&data.ctrl.currentQ, 1);
		}
	}
	else
	{
		// encDeltaSetpoint is used as hall speed setpoint
		PICtrlS12Setpoint(&data.ctrl.speed, data.command.encDeltaSetpoint);
		PICtrlS12Enable(&data.ctrl.speed, 1);
		PICtrlS12Update(&data.ctrl.speed, modelSpeed_S15_0);

		// Apply output to Q current controller input
		PICtrlS12Setpoint(&data.ctrl.currentQ, data.ctrl.speed.output);
		PICtrlS12Enable(&data.ctrl.currentQ, 1);
};
void PICtrlUpdate(PICtrl* pPI, int32_t measured)
{
	if(!pPI->enabled)
		return;

	if(measured > 4095) // This is the maximum value of a signed 12-bit integer divided by 2
		measured = 4095;
	if(measured < -4096)
		measured = -4096;

	// S13.0 = S12.0 - S12.0
	int32_t error = pPI->setpoint - measured;

	// S18.13 = S5.13 * S13.0
	int32_t iError = pPI->ki * error;

	// => S18.12
	iError >>= 1;

	// S19.12 = S12.12 + S18.12
	int32_t iTermNew = pPI->iTerm + iError;

	// => S12.12
	if(iTermNew > (pPI->outputMax << 12))
		iTermNew = pPI->outputMax << 12;
	if(iTermNew < (pPI->outputMin << 12))
		iTermNew = (pPI->outputMin << 12);

	pPI->iTerm = iTermNew;

	// S20.10 = S7.10 * S13.0
	int32_t pError = pPI->kp * error;

	// S21.10 = S20.10 + (S12.12 >> 2)
	int32_t output = pError + (iTermNew >> 2);

	// => S21.0
	output >>= 10;

    // Tigers uses the following code to implement anti-jitter, which is not used in the dribbler control currently as we don't know if we need it

	// if(pPI->antiJitter)
	// {
	// 	int32_t errorAbs = error < 0 ? -error : error;

	// 	if(errorAbs < pPI->antiJitter)
	// 	{
	// 		// S12.0 = (S0.12 * S13.0 * S12.0) >> 12;
	// 		//          \___________/ => due to errorAbs < antiJitter this can be a max of 4096 (S0.12)
	// 		output = (pPI->antiJitterReciprocal * errorAbs * output) >> 12;
	// 	}
	// }

	// => S12.0

    // Tiger: I set the overload to 0 in the following code because it is not used in the dribbler control currently
    // This is because we do not want to overload our motor
	if(output > pPI->outputMax)
	{
		output = pPI->outputMax;
		pPI->overload = 0;
	}
	else if(output < pPI->outputMin)
	{
		output = pPI->outputMin;
		pPI->overload = 0;
	}
	else
		pPI->overload = 0;

	pPI->output = output;
}

void PICtrlSetpoint(PICtrl* pPI, int32_t setpoint)
{
	if(setpoint > 4095)
		setpoint = 4095;
	if(setpoint < -4096)
		setpoint = -4096;

	pPI->setpoint = setpoint;
}

void PICtrlInit(PICtrl* pPI, int32_t kp, int32_t ki, int32_t outputMin, int32_t outputMax)
{
	pPI->kp = kp;
	pPI->ki = ki;
	pPI->outputMin = outputMin;
	pPI->outputMax = outputMax;
	pPI->antiJitter = 0;
	pPI->antiJitterReciprocal = 0;
	pPI->iTerm = 0;
	pPI->output = 0;
	pPI->overload = 0;
	pPI->setpoint = 0;
	pPI->enabled = 0;
}