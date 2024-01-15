#include "button.h"

static uint32_t calculateButtonTime(uint8_t LedId);


static volatile uint32_t ButtonHoldTime[5] = {0};

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

	switch(GPIO_Pin){
		case BTN_SW0_Pin:
			 ButtonHoldTime[0] = calculateButtonTime(0);
			break;
		case BTN_SW1_Pin:
			ButtonHoldTime[1] = calculateButtonTime(1);
			break;
		case BTN_SW2_Pin:
			ButtonHoldTime[2] = calculateButtonTime(2);
			break;
		case BTN_SW3_Pin:
			ButtonHoldTime[3] = calculateButtonTime(3);
			break;
//		case BTN_SW4_Pin:
//			ButtonHoldTime[4] = calculateButtonTime(4);
//			break;
		default:
			break;
		}

}


static uint32_t calculateButtonTime(uint8_t LedId){ // returns 0 when the button is pressed and returns the hold time when released.
	static uint8_t toggle[5] = {0};
	static uint32_t ButtonPressTime[5] = {0};
	toggle[LedId] ^= 1;

	if(toggle[LedId]){
		ButtonPressTime[LedId] = HAL_GetTick();
		return 0;
	}
	else{
		return HAL_GetTick() - ButtonPressTime[LedId];
	}


}

uint32_t getButtonState(uint8_t LedId){
	return ButtonHoldTime[LedId];
}
void resetButtonState(uint8_t LedId){
	ButtonHoldTime[LedId] = 0;
}


