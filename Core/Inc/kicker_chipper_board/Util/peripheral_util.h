/*
 * peripheral_util.h
 *
 *  Created on: 9 apr. 2019
 *      Author: cjdoo
 */

#ifndef PERIPHERAL_UTIL_H_
#define PERIPHERAL_UTIL_H_

#include "stm32f3xx_hal.h"

extern UART_HandleTypeDef huart1;

#define UART_PC 	(&huart1)	// PC communication

#endif /* PERIPHERAL_UTIL_H_ */