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

DEFINE_PIN(BAT_KILL_pin, Kill)