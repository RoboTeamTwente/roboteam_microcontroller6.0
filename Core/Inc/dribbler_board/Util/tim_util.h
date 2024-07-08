/*
 * tim_util.h
 *
 *  Created on: 8 April 2019
 *      Author: Cas Doornkamp
 */

#ifndef UTILS_TIM_UTIL_H_
#define UTILS_TIM_UTIL_H_

#include "stm32f3xx_hal.h"
#include "tim_util_functions.h"

// Timers
extern TIM_HandleTypeDef htim1; // internal timer (not used ATM)
extern TIM_HandleTypeDef htim2; // encoder Dribbler 32 bit
extern TIM_HandleTypeDef htim3; // PWM (CH1, CH2)
extern TIM_HandleTypeDef htim6; // ADC timer for ballsensor
extern TIM_HandleTypeDef htim7; // internal timer (not used ATM)
extern TIM_HandleTypeDef htim15; // internal timer for the control loop
extern TIM_HandleTypeDef htim16; // internal timer (not used ATM)
extern TIM_HandleTypeDef htim17; // internal timer (not used ATM)

extern PWM_struct PWM_Dribbler_a;
extern PWM_struct PWM_Dribbler_b;

// Timer Helpers
// Encoders
#define ENC_DRIBBLER (&htim2)
#define PWM_DRIBBLER (&htim3)
#define ADC_TIMER (&htim6)
#define CONTROL_TIMER (&htim15)

// PWM

extern PWM_struct PWM_Dribbler; 
void set_PWM_dribbler(PWM_struct* PWM, float Value);

inline uint32_t get_encoder(PWM_struct PWM){
    return __HAL_TIM_GET_COUNTER(PWM.TIM);
}


#endif //UTILS_TIM_UTIL_H_
