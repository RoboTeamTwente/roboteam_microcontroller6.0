/*
 * tim_util.h
 *
 *  Created on: 8 April 2019
 *      Author: Cas Doornkamp
 */

#ifndef UTILS_TIM_UTIL_H_
#define UTILS_TIM_UTIL_H_

#include "stm32f3xx_hal.h"
#include "main.h"

// structs
typedef struct PWM_struct{
    TIM_HandleTypeDef* TIM;
    uint16_t Channel;
} PWM_struct;

// Timers
extern TIM_HandleTypeDef htim1; // internal timer (not used ATM)
extern TIM_HandleTypeDef htim2; // encoder Dribbler 32 bit
extern TIM_HandleTypeDef htim3; // PWM (CH1, CH2)
extern TIM_HandleTypeDef htim6; // ADC timer for ballsensor
extern TIM_HandleTypeDef htim7; // internal timer (not used ATM)
extern TIM_HandleTypeDef htim15; // internal timer (not used ATM)
extern TIM_HandleTypeDef htim16; // internal timer (not used ATM)
extern TIM_HandleTypeDef htim17; // internal timer (not used ATM)

extern PWM_struct PWM_Dribbler_a;
extern PWM_struct PWM_Dribbler_b;

// Timer Helpers
// Encoders
#define ENC_DRIBBLER (&htim2)
#define PWM_DRIBBLER (&htim3)
#define ADC_TIMER (&htim6)

// PWM

extern PWM_struct PWM_Dribbler; 
extern void set_PWM(PWM_struct* PWM, float Value);

inline void start_PWM(PWM_struct PWM){
    HAL_TIM_PWM_Start(PWM.TIM, PWM.Channel);
}

inline void stop_PWM(PWM_struct PWM){
    HAL_TIM_PWM_Stop(PWM.TIM, PWM.Channel);
}

inline uint32_t get_PWM(PWM_struct PWM){
    return __HAL_TIM_GET_COMPARE(PWM.TIM , PWM.Channel);
}

inline uint32_t get_encoder(PWM_struct PWM){
    return __HAL_TIM_GET_COUNTER(PWM.TIM);
}


#endif //UTILS_TIM_UTIL_H_
