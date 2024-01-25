/*
 * CanDriver.c
 *
 *  Created on: Dec 21, 2023
 *      Author: Csongor
 */

#include "CanDriver.h"
#include "main.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static CanRxCallback canRxCallback = NULL;
uint8_t buffer_message[8];


void CAN_SetRxCallback(CanRxCallback callback){
	canRxCallback = callback;
}


void CAN_Init(CAN_HandleTypeDef *hcan){

	CAN_FilterTypeDef canfilterconfig;

	canfilterconfig.FilterActivation = CAN_FILTER_ENABLE;
	canfilterconfig.FilterBank = 10;  // anything between 0 to SlaveStartFilterBank
	canfilterconfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	canfilterconfig.FilterIdHigh = 0x000<<5;
	canfilterconfig.FilterIdLow = 0x0000;
	canfilterconfig.FilterMaskIdHigh = 0x000<<13;
	canfilterconfig.FilterMaskIdLow = 0x0000;
	canfilterconfig.FilterMode = CAN_FILTERMODE_IDMASK;
	canfilterconfig.FilterScale = CAN_FILTERSCALE_32BIT;
	canfilterconfig.SlaveStartFilterBank = 0;  // 13 to 27 are assigned to slave CAN (CAN 2) OR 0 to 12 are assgned to CAN1

	HAL_CAN_ConfigFilter(hcan, &canfilterconfig);



	HAL_CAN_Start(hcan);
	HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
}


void CAN_SendMessage(CAN_HandleTypeDef *hcan, uint32_t MessageId ,const uint8_t TxData[], uint32_t Length){

	CAN_TxHeaderTypeDef Txheader;
	Txheader.DLC = (Length>8) ? 0 : Length;
	Txheader.ExtId = 0;
	Txheader.IDE = CAN_ID_STD;
	Txheader.RTR = CAN_RTR_DATA;
	Txheader.StdId = MessageId;
	Txheader.TransmitGlobalTime = DISABLE;

	uint32_t TxMailbox[3];
	HAL_CAN_AddTxMessage(hcan, &Txheader, TxData, &TxMailbox[0]);
}


void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) // this is defined in the hal_can lib
{
	CAN_RxHeaderTypeDef RxHeader;
	uint8_t RxData[8];
	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData);



	if (canRxCallback != NULL) {//only if callback is set
		canRxCallback(RxData, RxHeader.StdId, RxHeader.DLC); //data[8], id, length
	}
}
/*
 * The header is 13 bits
 * The first two bits are for the IDE and RTR
 * After that, the first 7 bits is the message ID
 * While the left most 4 bits is used as the ID of the receiver
 * The pay load will be a list of length 8 with 8 bit numbers, for a total of 64 bits or 8 bytes
 */
void process_Message(uint8_t Payload[8], CAN_RxHeaderTypeDef Header){
	uint8_t message_ID = 0x7F & Header.StdId; // get the first 7 bits from the 32 bit integer Std_ID
	memcpy(buffer_message, Payload, sizeof(buffer_message));

	switch(message_ID)
	{
		case KILL_VOLTAGE_MESSAGE: ;
			// Here we have to extract two bits, from the pay load at byte 1
			uint8_t message = buffer_message[0];
			bool kill_message = message & 0x01;
			bool request_voltage = message & 0x02;
			// What do we do with this data ?
			break;
		case ARE_YOU_ALIVE:

			break;
		default:
			//Throw an error
			break;
	}

	return;
}

/*
 * Here we generate the basic message structure before sending it
 */
void send_Message(uint8_t sending_message_ID, CAN_TxHeaderTypeDef TxHeader, uint8_t payload){
	TxHeader.DLC = 1;
	TxHeader.ExtId = 0;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.TransmitGlobalTime = DISABLE;

	switch(sending_message_ID)
	{
		case VOLTAGE_RESPONSE:
			// The ID we want to send is 11 bits 0000 for top followed by 0000001 indicating a response
			TxHeader.StdId = (TOP_ID << RECEIVER_ID_LOCATION) & VOLTAGE_RESPONSE;

			//Following this we add data to the pay load at index 0 and 1 as 16 bits are needed
			break;
		case IM_ALIVE:
			// First we need an if statement if the initialization process went well!
			TxHeader.StdId = (TOP_ID << RECEIVER_ID_LOCATION) & IM_ALIVE;
			break;
		default:
			// Throw an error
			break;
	}

	return;
}




