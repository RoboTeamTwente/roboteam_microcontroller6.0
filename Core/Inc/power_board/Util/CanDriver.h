/*
 * CanDriver.h
 *
 *  Created on: Dec 21, 2023
 *      Author: Csongor
 */

#ifndef INC_DRIVERS_CANDRIVER_H_
#define INC_DRIVERS_CANDRIVER_H_

	#include "main.h"

	typedef void (*CanRxCallback)(uint8_t RxData[8], uint8_t MessageId, uint8_t MessageLength);
	void CAN_SetRxCallback(CanRxCallback callback);

	void CAN_Init(CAN_HandleTypeDef *hcan);
	void CAN_SendMessage(CAN_HandleTypeDef *hcan, uint32_t MessageId ,const uint8_t TxData[], uint32_t Length);

	void process_Message(uint8_t Payload[8], CAN_RxHeaderTypeDef Header);

	void send_Message(uint8_t sending_message_ID, CAN_TxHeaderTypeDef Header, uint8_t payload);

	#define MCP_VERSION 0

	#define TOP_ID 0
	#define KILL_VOLTAGE_MESSAGE 1 //MESSAGE ID
	#define ARE_YOU_ALIVE 128
	#define IM_ALIVE 128
	#define RECEIVER_ID_LOCATION 7
	#define MESSAGE_ID_LOCATION 7 // To get the first 7 bits

	#define KILL_BATTERY 1
	#define DONT_KILL_BATTERY 0

	#define REQUEST_POWER_VOLTAGE 1
	#define DONT_REQUEST_POWER_VOLTAGE 0
	#define VOLTAGE_RESPONSE 1



#endif /* INC_DRIVERS_CANDRIVER_H_ */
