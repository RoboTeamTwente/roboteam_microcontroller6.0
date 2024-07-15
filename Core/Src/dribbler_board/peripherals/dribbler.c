#include "dribbler.h"
#include <stdlib.h>



uint16_t dribbler_current_Buffer[current_Buffer_Size];
float current_limit;
bool motor_reversed = false;
bool has_encoder = true;
float dribbler_min_speed_PWM = 0.1f;
float dribbler_idle_speed_PWM = 0.2f;
float dribbler_max_speed_PWM = 0.8f;

float dribbler_min_speed = 0;
float dribbler_idle_speed = 0;
float dribbler_max_speed = 0;

int calculateDifference(int value1, int value2, int maxvalue);//calculated difference between 2 values, with wrapping
float dribbler_speed = 0;

void dribbler_Init(){
	current_limit=1.0f; // [A] 0.32A is the maximum continuous current of the dribbler motor
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
	dribbler_setCurrentLimit(current_limit);
	dribbler_test(); //Test the motor and see if it's reversed or not
}

/**
 * @note 0 <= value <= 2.2 A
 * For motor go to max 0.3 A
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
void dribbler_test(){
	dribbler_SetSpeed(0.15f, 1);
	HAL_Delay(100);

	if(dribbler_GetEncoderSpeed() == 0){
		has_encoder = false;
	} else if(dribbler_GetEncoderSpeed() < 0){
		motor_reversed = false;
	} else{
		motor_reversed = true;
	}
	dribbler_SetSpeed(0.0f, 1);
	HAL_Delay(100);

	if(has_encoder){
		for(float f = 0.0f; f <= 0.2f; f += 0.01f){
			dribbler_SetSpeed(f, 1);
			HAL_Delay(15);
			dribbler_min_speed = dribbler_GetEncoderSpeed();
			if(fabs(dribbler_min_speed) > 20){
				dribbler_min_speed_PWM = f;
				break;
			}
		}
		HAL_Delay(10);
	}
	
	
	// dribbler_SetIdleSpeed(1);
	// HAL_Delay(100);
	// dribbler_idle_speed = dribbler_GetEncoderSpeed();
	// dribbler_SetMaxSpeed(1);
	// HAL_Delay(100);
	// dribbler_max_speed = dribbler_GetEncoderSpeed();
	dribbler_SetSpeed(0.0f, 1);

}
void dribbler_setCurrentLimit(float value){
	// The value you put in is the DOR Vout=DOR*(Vref/4095) where Vref is the reference voltage of the DAC (3.3V)
	//float V_set= (float)(value * 1.5f); //
	uint32_t DOR = (uint32_t)(1939 * value + 232);
	if (DOR>4095){
		DOR=4095;
		}

	HAL_DAC_Start(VOLTAGE_DRIBBLER, DAC1_CHANNEL_1);
	HAL_DAC_SetValue(VOLTAGE_DRIBBLER, DAC1_CHANNEL_1, DAC_ALIGN_12B_R, DOR);
 
}

float dribbler_getCurrent(){
	// For now we get the most recent reading
	// Value=ADC_Value/4095*Vref/1.5 where 1.5 is the conversion factor in combination with the resistor /4095*3.3/1.5
	
	//average the first 10 elements of the dribbler_current_Buffer
	uint32_t current_sum = 0;
	for (int i = 0; i < current_Buffer_Size; i++){
		current_sum += dribbler_current_Buffer[i];
	}

	uint32_t current_temp =  current_sum / current_Buffer_Size;

	float currentA = ((float)(current_temp-232))/1939;
	return currentA;
}

bool dribbler_hasBall(){
	float currentA = dribbler_getCurrent();
	return (currentA>0.15f);
}

void dribbler_DeInit(){
	HAL_TIM_Base_Stop(PWM_DRIBBLER);
	HAL_TIM_Base_Stop_IT(ADC_TIMER);
	stop_PWM(PWM_Dribbler_a);
	stop_PWM(PWM_Dribbler_b);
}

void dribbler_SetSpeed(float speed, bool brake){

	if(motor_reversed){
		speed = -speed; // The motor is mounted in reverse
	}
	

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

void dribbler_SetMinSpeed(bool brake){
	dribbler_SetSpeed(dribbler_min_speed_PWM, brake);
}
void dribbler_SetIdleSpeed(bool brake){
	dribbler_SetSpeed(dribbler_idle_speed_PWM, brake);
}
void dribbler_SetMaxSpeed(bool brake){
	dribbler_SetSpeed(dribbler_max_speed_PWM, brake);
}

float dribbler_GetMinSpeed(bool brake){
	return dribbler_min_speed;
}
float dribbler_GetIdleSpeed(bool brake){
	return dribbler_idle_speed;
}
float dribbler_GetMaxSpeed(bool brake){
	return dribbler_max_speed;
}


bool dribbler_hasEncoder(){
	return has_encoder;
}


uint32_t dribbler_GetEncoderMeasurement(){
	uint32_t encoder_value = __HAL_TIM_GET_COUNTER(ENC_DRIBBLER);
	return encoder_value;
}

void dribbler_UpdateEncoderSpeed(){
	static uint32_t last_encoder_value = 0;
	uint32_t current_encoder_value = dribbler_GetEncoderMeasurement();
	float speed = (float)(calculateDifference(last_encoder_value, current_encoder_value, 65535))*(2.4576f);
	last_encoder_value = current_encoder_value;
	dribbler_speed =  speed;
}

float dribbler_GetEncoderSpeed(){
	return dribbler_speed;
}


int calculateDifference(int value1, int value2, int maxvalue) {
    int directDiff = value2 - value1;
    int wrapDiff;

    // Calculate wrap-around difference
    if (value1 > value2) {
        wrapDiff = (maxvalue - value1 + value2 + 1);
    } else {
        wrapDiff = -(maxvalue - value2 + value1 + 1);
    }

    // Determine which difference is smaller in magnitude
    if (abs(directDiff) < abs(wrapDiff)) {
        return directDiff;
    } else {
        return wrapDiff;
    }
}
