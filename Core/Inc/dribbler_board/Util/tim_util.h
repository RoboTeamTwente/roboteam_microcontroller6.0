/*
 * tim_util.h
 *
 *  Created on: 8 April 2019
 *      Author: Cas Doornkamp
 */

#ifndef UTILS_TIM_UTIL_H_
#define UTILS_TIM_UTIL_H_

#include "stm32f3xx_hal.h"
// Timers
extern TIM_HandleTypeDef htim1; // internal timer (not used ATM)
extern TIM_HandleTypeDef htim2; // encoder Dribbler 32 bit
extern TIM_HandleTypeDef htim3; // PWM (CH2: Dribbler)
extern TIM_HandleTypeDef htim6; // internal timer (not used ATM)
extern TIM_HandleTypeDef htim7; // internal timer (not used ATM)
extern TIM_HandleTypeDef htim15; // internal timer (not used ATM)
extern TIM_HandleTypeDef htim16; // internal timer (not used ATM)
extern TIM_HandleTypeDef htim17; // internal timer (not used ATM)


// structs
typedef struct PWM_struct{
    TIM_HandleTypeDef* TIM;
    uint16_t Channel;
} PWM_struct;

// Timer Helpers
// Encoders
#define ENC_DRIBBLER (&htim2)

// PWM
extern PWM_struct PWM_Dribbler; 

inline void start_PWM(PWM_struct PWM){
    HAL_TIM_PWM_Start(PWM.TIM, PWM.Channel);
}

inline void stop_PWM(PWM_struct PWM){
    HAL_TIM_PWM_Stop(PWM.TIM, PWM.Channel);
}

inline void set_PWM(PWM_struct PWM, uint32_t Value){
    __HAL_TIM_SET_COMPARE(PWM.TIM , PWM.Channel, Value);
}

inline uint32_t get_PWM(PWM_struct PWM){
    return __HAL_TIM_GET_COMPARE(PWM.TIM , PWM.Channel);
}

#endif //UTILS_TIM_UTIL_H_
