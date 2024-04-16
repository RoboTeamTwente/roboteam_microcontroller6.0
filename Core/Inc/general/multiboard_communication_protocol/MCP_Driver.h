#ifndef _MCP_DRIVER_H_
#define _MCP_DRIVER_H_

#include "MCP_BaseTypes.h"
#include "main.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct _mailbox_buffer{
	bool empty;
	uint8_t data_Frame[8];
	uint8_t message_id;
} mailbox_buffer;

extern mailbox_buffer MailBox_one;
extern mailbox_buffer MailBox_two;
extern mailbox_buffer MailBox_three;
extern bool CAN_to_process;

void CAN_Init(CAN_HandleTypeDef *hcan, uint8_t board_id);
bool extract_command(uint8_t RxData[], CAN_RxHeaderTypeDef *Header);
void CAN_Send_Message(CAN_HandleTypeDef *hcan, uint8_t* payload, CAN_TxHeaderTypeDef CAN_TxHeader);
CAN_TxHeaderTypeDef CAN_Initalize_Header(uint16_t type, uint8_t receiving_board);
void CAN_error_LOG(CAN_TxHeaderTypeDef *Header);

#endif /* _MCP_DRIVER_H_ */