#ifndef INC_OLED_H_
#define INC_OLED_H_

#include "ssd1306/OledDriver.h"
#include "button.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


typedef enum{
	MENU_OK,
	MENU_OUT_OF_BOUND,
	MENU_MEM_ALLOC_FAILED,
	MENU_ERROR
}Menu_StatusTypeDef;


Menu_StatusTypeDef Menu_Init();
void Menu_Loop();
void Menu_Update();
void Menu_Select(uint8_t page, uint8_t select0, uint8_t select1, uint8_t select2, uint8_t select3);
void Menu_NextPage();
void Menu_PreviousPage();
Menu_StatusTypeDef Menu_SetString(uint8_t item, uint8_t position, char* str);
Menu_StatusTypeDef Menu_SetVariable(uint8_t item, uint8_t position, int32_t variable);
Menu_StatusTypeDef Menu_SetVariableName(uint8_t item, uint8_t position, char* variableName);
int32_t Menu_GetVariable(uint8_t item, uint8_t position);
void Menu_DataUpdate();
void Menu_NextItem();
void Menu_PreviousItem();




#endif /* INC_OLED_H_ */
