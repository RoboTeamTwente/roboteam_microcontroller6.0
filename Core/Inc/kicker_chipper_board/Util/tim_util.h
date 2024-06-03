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
extern TIM_HandleTypeDef htim2;     // Voltage readings
extern TIM_HandleTypeDef htim16;    // KickChipping

// Timer Helpers
#define TIM_SHOOT    (&htim16)
#define TIM_VOLTAGE  (&htim2)

#endif //UTILS_TIM_UTIL_H_