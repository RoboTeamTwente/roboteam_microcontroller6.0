/*
 * gpio_util.h
 *
 *  Created on: 8 April 2019
 *      Author: Cas Doornkamp
 */

#ifndef UTILS_GPIO_UTIL_H_
#define UTILS_GPIO_UTIL_H_

#include "gpio_util_functions.h"

// Kick/Chip
extern GPIO_Pin Kick_pin;
extern GPIO_Pin Chip_pin;
extern GPIO_Pin Charge_pin;
extern GPIO_Pin Charge_done_pin;
extern GPIO_Pin Fault_pin;
extern GPIO_Pin Temp_Sens;
extern GPIO_Pin Cap_VoltageP;
extern GPIO_Pin Cap_VoltageN;

#endif /* UTILS_GPIO_UTIL_H_ */