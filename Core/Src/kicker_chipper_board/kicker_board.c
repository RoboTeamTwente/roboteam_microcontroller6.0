#include "kicker_board.h"
#include "CanDriver.h"
//#include "rem.h"
#include "main.h"

uint64_t TxMailbox[0];  
uint32_t heartbeat = 0;

/* ======================================================== */
/* ==================== INITIALIZATION ==================== */
/* ======================================================== */
void init() {
    CAN_Init(&hcan, KICK_CHIP_ID);
	//shoot_Init();
	heartbeat = HAL_GetTick() + 3000;
	CAN_Send_Message(IM_ALIVE_KICKER, TOP_ID, &hcan);
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
	uint32_t time = HAL_GetTick();
    if (CAN_to_process) {
        if (!MailBox_one.empty)
            CAN_Process_Message(&MailBox_one);
        if (!MailBox_two.empty)
            CAN_Process_Message(&MailBox_two);
        if (!MailBox_three.empty)
            CAN_Process_Message(&MailBox_three);
        CAN_to_process = false;
	}

	if (time > heartbeat) {
		heartbeat = time + 3000;
		CAN_Send_Message(CAPACITOR_VOLTAGE_MESSAGE, TOP_ID, &hcan);
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
			set_capacitor_sensor_state(payload, true);
			set_capacitor_charging_state(payload, true);
		} else if (sending_message_ID == CAPACITOR_VOLTAGE_MESSAGE) {
			set_response_capacitor_voltage_header(&CAN_TxHeader);
			set_capacitor_voltage_response(payload, 0);
		}
	}
	if (HAL_CAN_AddTxMessage(hcanP, &CAN_TxHeader, &payload, TxMailbox[0]) != HAL_OK) {
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

	if (to_Process->message_id == ARE_YOU_ALIVE) {
		CAN_Send_Message(IM_ALIVE_KICKER, TOP_ID, &hcan);
	} else if (to_Process->message_id == KICK_MESSAGE) {
		shoot_SetPower(get_shoot_power(to_Process->data_Frame));
		if (get_kick_state(to_Process->data_Frame)) shoot_Shoot(shoot_Kick);
	} else if (to_Process->message_id == CHIP_MESSAGE) {
		shoot_SetPower(get_shoot_power(to_Process->data_Frame));
		if (get_kick_state(to_Process->data_Frame)) shoot_Shoot(shoot_Chip);
	} else if (to_Process->message_id == DISCHARGE_MESSAGE) {
		
	} else if (to_Process->message_id == REQUEST_CAPACITOR_VOLTAGE_MESSAGE) {

	} 
		
	to_Process->empty = true;
	*to_Process->data_Frame  = 0;
	to_Process->message_id = 0;
}

// Handles the interrupts of the different timers.
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == TIM_SHOOT->Instance) {
			shoot_Callback();
		}
}
