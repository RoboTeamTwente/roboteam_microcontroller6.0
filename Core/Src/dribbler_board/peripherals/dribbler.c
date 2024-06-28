#include "dribbler.h"
#include "dribbler_ctrl.h"


uint16_t dribbler_current_Buffer[current_Buffer_Size];
datactrl dribblerCtrl = {
	.current_limit = 0.3f 
};
void dribbler_Init(){
	HAL_TIM_Base_Start(PWM_DRIBBLER);
	start_PWM(PWM_Dribbler_a);
	start_PWM(PWM_Dribbler_b);
	dribbler_motor_Init();
	dribbler_SetSpeed(0.0f, 1);
}

void dribbler_motor_Init(){
	// Start the DMA for current of the motor
	//HAL_TIM_Base_Start_IT(ADC_TIMER);
	HAL_ADC_Start_DMA(CURRENT_DRIBBLER, (uint32_t*)dribbler_current_Buffer, current_Buffer_Size);

	// For the voltage
	dribbler_setCurrentLimit(dribblerCtrl.current_limit); // is in A
}

/**
 * @note 0 <= value <= 2.2 A
 * For motor go to 0.3 A
 * reference: https://deepbluembedded.com/stm32-dac-tutorial-example-hal-code-analog-signal-genreation/
 * The value you put in is the DOR Vout=DOR*(Vref/4096) where Vref is the reference voltage of the DAC (3.3V)
 * DOR=Vout*(4096/Vref)
 * 
 * I_TRIP (A) x A_IPROPI (μA/A) = V_VREF (V) / R_IPROPI (Ω)
 * I_TRIP = V_VREF / (A_IPROPI * R_IPROPI)
 * V_VREF = I_TRIP * A_IPROPI * R_IPROPI
 * R_IPROPI = 1000 (Ω) V_VREF = 3.3 (V), A_IPROPI = 1500 (μA/A)
 *
*/
void dribbler_setCurrentLimit(float value){
	// The value you put in is the DOR Vout=DOR*(Vref/4095) where Vref is the reference voltage of the DAC (3.3V)
	float V_set= (float)(value * 1.5f); //
	uint32_t DOR= (uint32_t)(V_set * 4095 / 3.3f);
	if (DOR>4095){
		DOR=4095;
		}

	HAL_DAC_Start(VOLTAGE_DRIBBLER, DAC1_CHANNEL_1);
	HAL_DAC_SetValue(VOLTAGE_DRIBBLER, DAC1_CHANNEL_1, DAC_ALIGN_12B_R, DOR);
 
}

uint32_t dribbler_getCurrent(){
	// For now we get the most recent reading
	// Value=ADC_Value/4095*Vref/1.5 where 1.5 is the conversion factor in combination with the resistor /4095*3.3/1.5
	uint32_t current=dribbler_current_Buffer[0];
	return dribbler_current_Buffer[0];
}

bool dribbler_hasBall(){
	uint32_t current = dribbler_getCurrent();
	return current > CURRENT_THRESHOLD;
}

void dribbler_DeInit(){
	HAL_TIM_Base_Stop(PWM_DRIBBLER);
	HAL_TIM_Base_Stop_IT(ADC_TIMER);
	stop_PWM(PWM_Dribbler_a);
	stop_PWM(PWM_Dribbler_b);
}

void dribbler_SetSpeed(float speed, bool brake){
	if (brake){ // The motor is in braking mode
		if (speed > 0){
			set_PWM_dribbler(&PWM_Dribbler_b, 1);
			set_PWM_dribbler(&PWM_Dribbler_a, 1-speed);
		}
		else{
			set_PWM_dribbler(&PWM_Dribbler_a, 1);
			set_PWM_dribbler(&PWM_Dribbler_b, 1 - -1*speed);
		}
	}
	else{ // The motor is in coasting mode
		if (speed > 0){
			set_PWM_dribbler(&PWM_Dribbler_a, 0);
			set_PWM_dribbler(&PWM_Dribbler_b, speed);
		}
		else{
			set_PWM_dribbler(&PWM_Dribbler_b, 0);
			set_PWM_dribbler(&PWM_Dribbler_a, -1*speed);
		}
	}
}

uint32_t dribbler_GetEncoderMeasurement(){
	encoder_value = get_encoder(PWM_Dribbler_a);
	return encoder_value;
}
