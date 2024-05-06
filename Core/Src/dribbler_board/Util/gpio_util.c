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

// LED pins
GPIO_Pin LED1 = { LED1_GPIO_Port, LED1_Pin };
GPIO_Pin LED2 = { LED2_GPIO_Port, LED2_Pin };

// // Ballsensor
GPIO_Pin IR_LED_pin = { Ball_sensor_out_GPIO_Port , Ball_sensor_out_Pin };