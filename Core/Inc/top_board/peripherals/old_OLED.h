#ifndef INC_OLD_OLED_H_
#define INC_OLD_OLED_H_

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

#define NUMBER_OF_MENU_ITEMS 8
#define NUMBER_OF_MENU_PAGES 4
#define NUMBER_OF_SUBMENU_ITEMS 8
#define MAX_STRING_LENGTH 23
#define STRINGS_PER_PAGE 8
#define VARIABLES_PER_PAGE 8
#define MAX_VAR_NAME_LENGTH 9
#define MAX_MENU_NAME_LENGTH 15
#define MAX_SUBMENU_NAME_LENGTH 23
#define NUMBER_OF_VARIABLE_PAGES 3
#define NUMBER_OF_DATA_PAGES 3


Menu_StatusTypeDef menu_Init();
void menu_Loop();
Menu_StatusTypeDef menu_SetString(uint8_t item, uint8_t position, char* str);
Menu_StatusTypeDef menu_SetVariable(uint8_t item, uint8_t position, int32_t variable);
Menu_StatusTypeDef menu_SetVariableName(uint8_t item, uint8_t position, char* variableName);
int32_t menu_GetVariable(uint8_t item, uint8_t position);
void menu_DataUpdate();



#endif /* INC_OLD_OLED_H_ */
