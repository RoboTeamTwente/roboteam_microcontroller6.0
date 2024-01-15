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

static CanRxCallback canRxCallback = NULL;
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
	canfilterconfig.SlaveStartFilterBank = 13;  // 13 to 27 are assigned to slave CAN (CAN 2) OR 0 to 12 are assgned to CAN1

	HAL_CAN_ConfigFilter(hcan, &canfilterconfig);



	HAL_CAN_Start(hcan);
	HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
}

void CAN_SendMessage(CAN_HandleTypeDef *hcan, uint32_t MessageId , uint8_t TxData[8], uint32_t Length){

	CAN_TxHeaderTypeDef Txheader;
	Txheader.DLC = (Length>8) ? 8 : Length;
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



