/*
 * PowerBoardDriver.h
 *
 *  Created on: Dec 22, 2023
 *      Author: Csongor
 */

#ifndef INC_DRIVERS_POWERBOARDDRIVER_H_
#define INC_DRIVERS_POWERBOARDDRIVER_H_

	#include "main.h"
	void DecodeCommand(uint8_t RxData[8], uint8_t MessageId, uint8_t MessageLength);
	void kill();


#endif /* INC_DRIVERS_POWERBOARDDRIVER_H_ */
