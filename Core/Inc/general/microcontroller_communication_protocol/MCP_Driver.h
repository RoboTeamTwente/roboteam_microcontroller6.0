#ifndef _MCP_DRIVER_H_
#define _MCP_DRIVER_H_

#include "MCP_BaseTypes.h"
#include "MCP_Ack.h"
#include "main.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct _mailbox_buffer{
	bool empty;
	uint8_t data_Frame[8];
	uint32_t message_id;
} mailbox_buffer;

extern mailbox_buffer MailBox_one;
extern mailbox_buffer MailBox_two;
extern mailbox_buffer MailBox_three;
extern uint32_t TxMailbox[1];
extern bool MCP_to_process;

void MCP_Init(CAN_HandleTypeDef *hcan, uint8_t board_id);
void MCP_Send_Message(CAN_HandleTypeDef *hcan, uint8_t *payload, CAN_TxHeaderTypeDef CAN_TxHeader, uint8_t to_board);
void MCP_Send_Message_Always(CAN_HandleTypeDef *hcan, uint8_t *payload, CAN_TxHeaderTypeDef CAN_TxHeader);
CAN_TxHeaderTypeDef MCP_Initialize_Header(uint16_t type, uint8_t receiving_board);
void MCP_Send_Ack(CAN_HandleTypeDef *hcan, uint8_t received_ack_number, uint32_t old_message_id);
void MCP_SetReadyToReceive(bool b);
bool MCP_GetFreeToSend(uint8_t to_board);
void MCP_timeout();

#endif /* _MCP_DRIVER_H_ */