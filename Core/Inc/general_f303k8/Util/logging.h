/*
 * logging.h
 *
 *  Created on: 15th may 2024
 *      Author: dario
 */
#ifndef _LOGGING_H_
#define _LOGGING_H_

#include "peripheral_util.h"
#include "power_board.h"
#include "stdarg.h"

#define STRING_SIZE 48


void LOG_init();

void LOG_deinit();

bool LOG_printf(char *format, ...);


#endif /* _LOGGING_H_ */