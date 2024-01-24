#include "button.h"


static volatile uint32_t ButtonHoldTime[5] = {0};

/**
 *  @brief saves 0 when the button is pressed and saves the hold time is ms when released.
*/
void calculateButtonTime(uint8_t buttonId){
	static uint8_t toggle[5] = {0};
	static uint32_t ButtonPressTime[5] = {0};
	//xor if the button is pressed
	toggle[buttonId] ^= 1;

	if(toggle[buttonId]){
		ButtonPressTime[buttonId] = HAL_GetTick();
		ButtonHoldTime[buttonId] = 0;
	}else{
		ButtonHoldTime[buttonId] = HAL_GetTick() - ButtonPressTime[buttonId];
	}
}

uint32_t getButtonState(uint8_t buttonId){
	return ButtonHoldTime[buttonId];
}
void resetButtonState(uint8_t buttonId){
	ButtonHoldTime[buttonId] = 0;
}


