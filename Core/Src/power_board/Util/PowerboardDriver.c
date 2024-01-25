/*
 * PowerboardDriver.c
 *
 *  Created on: Dec 22, 2023
 *      Author: Csongor
 */
#include "main.h"
#include "PowerBoardDriver.h"

void DecodeCommand(uint8_t RxData[8], uint8_t MessageId, uint8_t MessageLength){


	if(MessageId == 2){
		switch (RxData[0]) {
			case 1://command1

				break;
			case 2://command2

				break;
			case 3://command3
				kill();
				break;
			default:
				break;

		}
	}


}
void kill(){
	HAL_GPIO_WritePin(Kill_GPIO_Port, Kill_Pin, GPIO_PIN_RESET);
}
