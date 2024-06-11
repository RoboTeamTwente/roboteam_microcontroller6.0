#include "dribbler.h"


uint16_t dribbler_current_Buffer[current_Buffer_Size];

void dribbler_Init(){
	HAL_TIM_Base_Start(PWM_DRIBBLER);
	start_PWM(PWM_Dribbler_a);
	start_PWM(PWM_Dribbler_b);
	dribbler_motor_Init();
	dribbler_SetSpeed(0.0f);
}

void dribbler_motor_Init(){
	// Start the DMA for current of the motor
	//HAL_TIM_Base_Start_IT(ADC_TIMER);
	HAL_ADC_Start_DMA(CURRENT_DRIBBLER, (uint32_t*)dribbler_current_Buffer, current_Buffer_Size);

	// For the voltage
	dribbler_setCurrentLimit(1500);
}

/**
 * @note 0 <= value <= 4000
*/
void dribbler_setCurrentLimit(uint16_t value){
	HAL_DAC_Start(VOLTAGE_DRIBBLER, DAC1_CHANNEL_1);
	HAL_DAC_SetValue(VOLTAGE_DRIBBLER, DAC1_CHANNEL_1, DAC_ALIGN_12B_R, value);
}

uint32_t dribbler_getCurrent(){
	// For now we get the most recent reading
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

void dribbler_SetSpeed(float speed){
	if (BOARD_INITIALIZED){
		if (speed > 0){
			set_PWM_dribbler(&PWM_Dribbler_b, 1);
			set_PWM_dribbler(&PWM_Dribbler_a, 1-speed);
		}
		else{
			set_PWM_dribbler(&PWM_Dribbler_a, 1);
			set_PWM_dribbler(&PWM_Dribbler_b, 1 - -1*speed);
		}
	}
}


uint32_t dribbler_GetEncoderMeasurement(){
	encoder_value = get_encoder(PWM_Dribbler_a);
	return encoder_value;
}
