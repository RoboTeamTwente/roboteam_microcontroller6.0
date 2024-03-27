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
extern TIM_HandleTypeDef htim16;    // KickChipping

// Timer Helpers
#define TIM_SHOOT    (&htim16)


// structs
typedef struct PWM_struct{
    TIM_HandleTypeDef* TIM;
    uint16_t Channel;
} PWM_struct;

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