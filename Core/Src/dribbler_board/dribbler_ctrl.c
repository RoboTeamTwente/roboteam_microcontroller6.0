/* 
The dribbler control of RoboTeam Twente
Created by Chris Krommendijk

*/

#include "dribbler_ctrl.h"


void PICtrlUpdate(PICtrl* pPI, int32_t measured)
{
	if(!pPI->enabled)
		return;

	if(measured > 4095)
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