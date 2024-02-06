/*
 * peripheral_util.h
 *
 *  Created on: 9 apr. 2019
 *      Author: cjdoo
 */

#ifndef PERIPHERAL_UTIL_H_
#define PERIPHERAL_UTIL_H_

#include "stm32f3xx_hal.h"

extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart4;

#define UART_PC 	(&huart5)	// PC communication
#define UART_BACK 	(&huart4)	// UART going to backboard

#endif /* PERIPHERAL_UTIL_H_ */
