/*
 * gpio_util.c
 *
 *  Created on: 8 April 2019
 *      Author: Cas Doornkamp
 */

#include "gpio_util.h"
#include "main.h"

// List known GPIO pins

// Kick/Chip
GPIO_Pin Kick_pin 			= { Kick_GPIO_Port			, Kick_Pin			};
GPIO_Pin Chip_pin 			= { Chip_GPIO_Port			, Chip_Pin			};
GPIO_Pin Charge_pin 		= { Charge_GPIO_Port		, Charge_Pin		};
GPIO_Pin Charge_done_pin 	= { Charge_done_GPIO_Port	, Charge_done_Pin	};
GPIO_Pin Fault_pin          = { Fault_GPIO_Port         , Fault_Pin         };