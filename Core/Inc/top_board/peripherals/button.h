/*
 * button.h
 *
 *  Created on: Dec 23, 2023
 *      Author: Csongor
 */

#ifndef INC_DRIVERS_BUTTON_H_
#define INC_DRIVERS_BUTTON_H_

typedef enum{
    BUTTON_LEFT,BUTTON_RIGHT,BUTTON_DOWN,BUTTON_OK,BUTTON_UP
}button_id_t;

#include "main.h"

void calculateButtonTime(button_id_t buttonId);
button_id_t getRecentlyPressedButton();
uint32_t getButtonState(button_id_t buttonId);
void resetButtonState(button_id_t buttonId);

#endif /* INC_DRIVERS_BUTTON_H_ */
