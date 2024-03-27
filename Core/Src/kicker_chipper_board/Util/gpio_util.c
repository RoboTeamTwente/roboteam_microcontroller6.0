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

// Kick/Chip
GPIO_Pin Kick_pin 			= { Kick_GPIO_Port			, Kick_Pin			};
GPIO_Pin Chip_pin 			= { Chip_GPIO_Port			, Chip_Pin			};
GPIO_Pin Charge_pin 		= { Charge_GPIO_Port		, Charge_Pin		};
GPIO_Pin Charge_done_pin 	= { Charge_done_GPIO_Port	, Charge_done_Pin	};