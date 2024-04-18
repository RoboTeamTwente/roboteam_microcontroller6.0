#include "power_board.h"
#include "rem.h"
#include "main.h"
#include "gpio_util.h"


uint32_t heartbeat_10000ms = 0;

void kill();
void MCP_Process_Message(mailbox_buffer *to_Process);

//Outgoing MCP headers
CAN_TxHeaderTypeDef powerAliveHeader = {0};
CAN_TxHeaderTypeDef powerVoltageHeader = {0};

//Incoming MCP payload
MCP_AreYouAlive areYouAlive = {0};
MCP_Kill mcp_kill = {};


/* ======================================================== */
/* ==================== INITIALIZATION ==================== */
/* ======================================================== */
void init() {
    // Set power circuit pin to HIGH, meaning on. When pulled again to LOW, it signals the power circuit to turn off, and power is then cut off instantly.
	// This pin must be set HIGH within a few milliseconds after powering on the robot, or it will turn the robot off again
	//set_Pin(BAT_KILL_pin, 1);

	// MCP
	MCP_Init(&hcan, MCP_POWER_BOARD);
	powerAliveHeader = MCP_Initialize_Header(MCP_PACKET_TYPE_MCP_POWER_ALIVE, MCP_TOP_BOARD);
	powerVoltageHeader = MCP_Initialize_Header(MCP_PACKET_TYPE_MCP_POWER_VOLTAGE, MCP_TOP_BOARD);
	
	/* === Wired communication with robot; Can now receive RobotCommands (and other REM packets) via UART */
	//REM_UARTinit(UART_PC);

	heartbeat_10000ms = HAL_GetTick() + 10000;
}

uint8_t robot_get_ID(){
  return 0;
}

uint8_t robot_get_Channel(){
  return 0;
}

// Function to perform a kill operation
void kill() {
    //set_Pin(BAT_KILL_pin, 0);
}

/* =================================================== */
/* ==================== MAIN LOOP ==================== */
/* =================================================== */
void loop() {
    uint32_t current_time = HAL_GetTick();
	
    if (MCP_to_process){
        if (!MailBox_one.empty)
            MCP_Process_Message(&MailBox_one);
        if (!MailBox_two.empty)
            MCP_Process_Message(&MailBox_two);
        if (!MailBox_three.empty)
            MCP_Process_Message(&MailBox_three);
        MCP_to_process = false;
	}

	    // 10 seconds passed now we send the reading of the voltage meter to the top board
    if (heartbeat_10000ms < current_time) {
		// voltage_reading = some_function  // Here we call the function to get the voltage from the sensor
		MCP_PowerVoltage pv = {0};
		MCP_PowerVoltagePayload pvp = {0};
		pv.voltagePowerBoard = 24.0f; //TODO call method and check for min/max
		encodeMCP_PowerVoltage(&pvp, &pv);
		MCP_Send_Message(&hcan, &pvp, powerVoltageHeader);

    	heartbeat_10000ms = current_time + 10000;
    }
}

/*
 * The header is 13 bits
 * The first two bits are for the IDE and RTR
 * After that, the first 7 bits is the message ID
 * While the left most 4 bits is used as the ID of the receiver
 * The pay load will be a list of length 8 with 8 bit numbers, for a total of 64 bits or 8 bytes
 */
void MCP_Process_Message(mailbox_buffer *to_Process){

	if (to_Process->message_id == MCP_PACKET_ID_TO_POWER_MCP_ARE_YOU_ALIVE) {
		MCP_AreYouAlivePayload* ayap = (MCP_AreYouAlivePayload*) to_Process->data_Frame;
		decodeMCP_AreYouAlive(&areYouAlive, ayap);
		//TODO what if wrong version
		MCP_PowerAlive pa = {0};
		MCP_PowerAlivePayload pap = {0};
		pa.mcpVersion = MCP_LOCAL_VERSION;
		pa.sensorWorking = false;
		encodeMCP_PowerAlive(&pap, &pa);
		MCP_Send_Message(&hcan, &pap, powerAliveHeader);
	} else if (to_Process->message_id == MCP_PACKET_ID_TO_POWER_MCP_KILL) {
		kill();
	}
	
	to_Process->empty = true;
	*to_Process->data_Frame  = 0;
	to_Process->message_id = 0;
}