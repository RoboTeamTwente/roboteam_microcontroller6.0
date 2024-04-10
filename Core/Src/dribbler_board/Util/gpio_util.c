/*
 * gpio_util.c
 *
 *  Created on: 8 April 2019
 *      Author: Cas Doornkamp
 */

#include "gpio_util.h"
#include "main.h"

#define DEFINE_PIN(label,pin_name) GPIO_Pin label = {pin_name##_GPIO_Port, pin_name##_Pin};
// List known GPIO pins

// Dribbler
GPIO_Pin Dribbler_PWM_pin	= { PWM_Dribbler_GPIO_Port	, PWM_Dribbler_Pin	};

// Ballsensor
GPIO_Pin BS_IRQ_pin = { BS_IRQ_GPIO_Port    , BS_IRQ_Pin   };
GPIO_Pin IR_LED_pin = { IR_LED_GPIO_Port    , IR_LED_Pin   };