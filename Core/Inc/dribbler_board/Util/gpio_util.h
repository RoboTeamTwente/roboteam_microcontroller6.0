/*
 * gpio_util.h
 *
 *  Created on: 8 April 2019
 *      Author: Cas Doornkamp
*/

#ifndef UTILS_GPIO_UTIL_H_
#define UTILS_GPIO_UTIL_H_

#include "stdbool.h"
#include "stm32f3xx_hal.h"

#define LOW 0
#define HIGH 1

// abstract a GPIO pin combination to a struct
typedef struct GPIO_Pin{
	GPIO_TypeDef * PORT;
	uint16_t PIN;
} GPIO_Pin;

/////////////////////////////////// LIST OF KNOWN GPIO PINS

// Dribbler
extern GPIO_Pin Dribbler_PWM_pin;

// Ballsensor
extern GPIO_Pin BS_IRQ_pin;
extern GPIO_Pin IR_LED_pin;

/////////////////////////////////////////////// GPIO UTILITY FUNCTIONS

// Set a GPIO Pin
inline void set_Pin(GPIO_Pin p, bool value)
{
	HAL_GPIO_WritePin(p.PORT, p.PIN, value);
}

// Read a GPIO Pin
inline GPIO_PinState read_Pin(GPIO_Pin p)
{
	return HAL_GPIO_ReadPin(p.PORT, p.PIN);
}

// Toggle a GPIO Pin
inline void toggle_Pin(GPIO_Pin p)
{
	HAL_GPIO_TogglePin(p.PORT, p.PIN);
}

#endif /* UTILS_GPIO_UTIL_H_ */