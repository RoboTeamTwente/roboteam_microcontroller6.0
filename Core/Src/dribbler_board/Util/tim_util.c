/*
 * tim_util.c
 *
 *  Created on: 8 April 2019
 *      Author: Cas Doornkamp
 */

#include "tim_util.h"
#include "stm32f3xx_hal.h"

PWM_struct PWM_Dribbler	= { &htim3 , TIM_CHANNEL_2};