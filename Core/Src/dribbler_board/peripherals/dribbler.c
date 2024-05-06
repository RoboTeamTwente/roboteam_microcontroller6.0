#include "dribbler.h"

DAC_HandleTypeDef* dribbler_DAC;

void dribbler_Init(HAL_TIM_StateTypeDef* timer, DAC_HandleTypeDef* dac){
	HAL_TIM_Base_Start(&timer);
	start_PWM(PWM_Dribbler_a);
	start_PWM(PWM_Dribbler_b);
	dribbler_DAC = &dac;
	dribbler_motor_Init();
}

void dribbler_motor_Init(){
	HAL_DAC_Start(&dribbler_DAC, DAC1_CHANNEL_1);
 	HAL_DAC_SetValue(&dribbler_DAC, DAC1_CHANNEL_1, DAC_ALIGN_12B_R, 400);
}

void dribbler_setCurrentLimit(uint16_t value){
	HAL_DAC_Start(&dribbler_DAC, DAC1_CHANNEL_1);
	HAL_DAC_SetValue(&dribbler_DAC, DAC1_CHANNEL_1, DAC_ALIGN_12B_R, 400);
}

void dribbler_DeInit(HAL_TIM_StateTypeDef* timer){
	HAL_TIM_Base_Stop(&timer);
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
