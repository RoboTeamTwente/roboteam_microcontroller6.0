/*
 * tim_util.c
 *
 *  Created on: 8 April 2019
 *      Author: Cas Doornkamp
 */

#include "tim_util.h"
#include "stm32f3xx_hal.h"

PWM_struct PWM_Dribbler_a	    = { PWM_DRIBBLER , ((uint16_t)TIM_CHANNEL_1)};
PWM_struct PWM_Dribbler_b       = { PWM_DRIBBLER , ((uint16_t)TIM_CHANNEL_2)}; 

void set_PWM(PWM_struct* PWM, float Value){
    if (PWM->Channel == ((uint16_t)TIM_CHANNEL_1))
        PWM->TIM->Instance->CCR1 = (uint16_t)(Value * 1000);
    else
        PWM->TIM->Instance->CCR2 = (uint16_t)(Value * 1000);
}
