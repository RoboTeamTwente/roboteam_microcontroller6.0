#include "power_board.h"
#include "CanDriver.h"
#include "rem.h"
#include "main.h"


uint16_t heartbeat_10000ms = 0;
bool kill_flag, voltage_request = false;
uint16_t voltage_reading = 0;
uint64_t TxMailbox[0];  



/* ======================================================== */
/* ==================== INITIALIZATION ==================== */
/* ======================================================== */
void init() {
    // Set power circuit pin to HIGH, meaning on. When pulled again to LOW, it signals the power circuit to turn off, and power is then cut off instantly.
	// This pin must be set HIGH within a few milliseconds after powering on the robot, or it will turn the robot off again
	//set_Pin(BAT_KILL_pin, 0); //0 SHOULD BE 1 BUT ELECTRONICS NEEDS TO FIX IT

	CAN_Init(&hcan);
	
	/* === Wired communication with robot; Can now receive RobotCommands (and other REM packets) via UART */
	REM_UARTinit(UART_PC);

	LOG("HELLO WORLD");
	LOG_sendAll();

	heartbeat_10000ms = HAL_GetTick() + 100000;
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
	LOG("HELLO WORLD");
	LOG_sendAll();
    uint32_t current_time = HAL_GetTick();
    /* USER CODE END WHILE */
    if (CAN_to_process)
    {
        if (!MailBox_one.empty)
            CAN_Process_Message(&MailBox_one);
        if (!MailBox_two.empty)
            CAN_Process_Message(&MailBox_two);
        if (!MailBox_three.empty)
            CAN_Process_Message(&MailBox_three);
        CAN_to_process = false;
	}
    
    // 10 seconds passed now we send the reading of the voltage meter to the top board
    if (heartbeat_10000ms < current_time)
    {
      // voltage_reading = some_function  // Here we call the function to get the voltage from the sensor
      CAN_Send_Message(VOLTAGE_RESPONSE, TOP_ID, &hcan);
      heartbeat_10000ms = current_time + 10000;
    }
}


/*
 * Generate the message we want to transmit based on
 * ID arguments passed
 */
void CAN_Send_Message(uint8_t sending_message_ID, uint8_t reciever_ID ,CAN_HandleTypeDef *hcan){

    uint8_t payload[8];
    memset(payload, 0, sizeof(payload));
    CAN_TxHeaderTypeDef CAN_TxHeader = CAN_Initalize_Header();

	if (reciever_ID == TOP_ID)
	{
		if (sending_message_ID == VOLTAGE_RESPONSE)
		{
			set_voltage_response_header(&CAN_TxHeader);
			set_voltage_response(voltage_reading, &payload);
		}
		else if (sending_message_ID == IM_ALIVE_VOLTAGE)
		{
			set_powerBoard_im_alive_header(&CAN_TxHeader);
			set_MCP_version(payload);
			set_powerBoard_sensor_state(payload, true);
		}
	}
	if (HAL_CAN_AddTxMessage(hcan, &CAN_TxHeader, &payload, &TxMailbox[0]) != HAL_OK)
		CAN_error_LOG(&CAN_TxHeader);

	return;
}

/*
 * The header is 13 bits
 * The first two bits are for the IDE and RTR
 * After that, the first 7 bits is the message ID
 * While the left most 4 bits is used as the ID of the receiver
 * The pay load will be a list of length 8 with 8 bit numbers, for a total of 64 bits or 8 bytes
 */
void CAN_Process_Message(mailbox_buffer *to_Process){

	if (to_Process->message_id == KILL_REQUEST_VOLTAGE_MESSAGE)
	{
		kill_flag = get_kill_state(to_Process->data_Frame[0]);
		voltage_request = get_request_power_state(to_Process->data_Frame[0]);
	}
	else if (to_Process->message_id == ARE_YOU_ALIVE)
	{
		if (get_MCP_version(to_Process->data_Frame) != MCP_VERSION)
		{
			
		}
	}
	
	to_Process->empty = true;
	*to_Process->data_Frame  = 0;
	to_Process->message_id = 0;

	return;
}