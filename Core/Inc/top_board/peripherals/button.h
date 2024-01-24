/*
 * button.h
 *
 *  Created on: Dec 23, 2023
 *      Author: Csongor
 */

#ifndef INC_DRIVERS_BUTTON_H_
#define INC_DRIVERS_BUTTON_H_

#include "main.h"

void calculateButtonTime(uint8_t buttonId);
uint32_t getButtonState(uint8_t buttonId);
void resetButtonState(uint8_t buttonId);

#endif /* INC_DRIVERS_BUTTON_H_ */
