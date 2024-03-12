#include "kicker_board.h"
#include "CanDriver.h"
//#include "rem.h"
#include "main.h"

uint64_t TxMailbox[0];  

/* ======================================================== */
/* ==================== INITIALIZATION ==================== */
/* ======================================================== */
void init() {
    CAN_Init(&hcan, KICK_CHIP_ID);
}

uint8_t robot_get_ID(){
  return 0;
}

uint8_t robot_get_Channel(){
  return 0;
}


/* =================================================== */
/* ==================== MAIN LOOP ==================== */
/* =================================================== */
void loop() {
    if (CAN_to_process) {
        if (!MailBox_one.empty)
            CAN_Process_Message(&MailBox_one);
        if (!MailBox_two.empty)
            CAN_Process_Message(&MailBox_two);
        if (!MailBox_three.empty)
            CAN_Process_Message(&MailBox_three);
        CAN_to_process = false;
	}
}

/*
 * Generate the message we want to transmit based on
 * ID arguments passed
 */
void CAN_Send_Message(uint8_t sending_message_ID, uint8_t reciever_ID ,CAN_HandleTypeDef *hcanP){

    uint8_t payload[8];
    memset(payload, 0, sizeof(payload));
    CAN_TxHeaderTypeDef CAN_TxHeader = CAN_Initalize_Header();

	if (reciever_ID == TOP_ID) {
		if (sending_message_ID == IM_ALIVE_KICKER) {
			set_kicker_im_alive(&CAN_TxHeader);
			set_MCP_version(payload);
            set_kick_state(payload, true);
		}
	}
	if (HAL_CAN_AddTxMessage(hcanP, &CAN_TxHeader, &payload, &TxMailbox[0]) != HAL_OK) {
		CAN_error_LOG(&CAN_TxHeader);
    }
}

/*
 * The header is 13 bits
 * The first two bits are for the IDE and RTR
 * After that, the first 7 bits is the message ID
 * While the left most 4 bits is used as the ID of the receiver
 * The pay load will be a list of length 8 with 8 bit numbers, for a total of 64 bits or 8 bytes
 */
void CAN_Process_Message(mailbox_buffer *to_Process){

	if (to_Process->message_id == ARE_YOU_ALIVE)
	{
		CAN_Send_Message(IM_ALIVE_KICKER, TOP_ID, &hcan);
		// if (get_MCP_version(to_Process->data_Frame) != MCP_VERSION)
		// {
			
		// }
	}
	
	to_Process->empty = true;
	*to_Process->data_Frame  = 0;
	to_Process->message_id = 0;
}