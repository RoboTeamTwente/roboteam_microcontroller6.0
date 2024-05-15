#include "dribbler.h"


uint32_t dribbler_current_Buffer[current_Buffer_Size];

void dribbler_Init(){
	HAL_TIM_Base_Start(PWM_DRIBBLER);
	start_PWM(PWM_Dribbler_a);
	start_PWM(PWM_Dribbler_b);
	dribbler_motor_Init();
}

void dribbler_motor_Init(){
	// Start the DMA for current of the motor
	HAL_TIM_Base_Start(DMA_TIMER);
	HAL_ADC_Start_DMA(CUR_DRIBBLER, (uint32_t*)dribbler_current_Buffer, current_Buffer_Size);
	// For the voltage
	HAL_DAC_Start(VOLT_DRIBBLER, DAC1_CHANNEL_1);
 	HAL_DAC_SetValue(VOLT_DRIBBLER, DAC1_CHANNEL_1, DAC_ALIGN_12B_R, volt_Start);
}

void dribbler_setVoltage(uint16_t value){
	HAL_DAC_Start(VOLT_DRIBBLER, DAC1_CHANNEL_1);
	HAL_DAC_SetValue(VOLT_DRIBBLER, DAC1_CHANNEL_1, DAC_ALIGN_12B_R, value);
}

uint32_t dribbler_getCurrent(){
	// For now we get the most recent reading
	return dribbler_current_Buffer[0];
}

bool dribbler_hasBall(){
	uint32_t current = dribbler_getCurrent();
	return current >  CURRENT_THRESHOLD;
}

void dribbler_DeInit(){
	HAL_TIM_Base_Stop(PWM_DRIBBLER);
	stop_PWM(PWM_Dribbler_a);
	stop_PWM(PWM_Dribbler_b);
}

void dribbler_SetSpeed(float speed){
	if (speed > 0){
		set_PWM(&PWM_Dribbler_a, 0);
		set_PWM(&PWM_Dribbler_b, speed);
	}
	else{
		set_PWM(&PWM_Dribbler_b, 0);
		set_PWM(&PWM_Dribbler_a, -1*speed);
	}
}


uint32_t dribbler_GetEncoderMeasurement(){
	encoder_value = get_encoder(PWM_Dribbler_a);
	return encoder_value;
}
