#include "power_board.h"
#include "main.h"
#include "gpio_util.h"


uint32_t heartbeat_10000ms = 0;
uint32_t heartbeat_10ms = 0;
float avg_voltage = 0;
uint16_t n_samples_voltage = 0;
bool send_powerVoltage = false;

void kill();
void MCP_Process_Message(mailbox_buffer *to_Process);
void MCP_Send_Im_Alive();

//Outgoing MCP headers
CAN_TxHeaderTypeDef powerAliveHeaderToTop = {0};
CAN_TxHeaderTypeDef powerAliveHeaderToDribbler = {0};
CAN_TxHeaderTypeDef powerAliveHeaderToKicker = {0};
CAN_TxHeaderTypeDef powerVoltageHeader = {0};

//Incoming MCP
MCP_Kill mcp_kill = {};


/* ======================================================== */
/* ==================== INITIALIZATION ==================== */
/* ======================================================== */
void init() {
	HAL_IWDG_Refresh(&hiwdg);
    // Set power circuit pin to HIGH, meaning on. When pulled again to LOW, it signals the power circuit to turn off, and power is then cut off instantly.
	// This pin must be set HIGH within a few milliseconds after powering on the robot, or it will turn the robot off again
	set_Pin(BAT_KILL_pin, 1);
	LOG_init();

	// MCP init
	MCP_Init(&hcan, MCP_POWER_BOARD);
	powerAliveHeaderToTop = MCP_Initialize_Header(MCP_PACKET_TYPE_MCP_POWER_ALIVE, MCP_TOP_BOARD);
	powerAliveHeaderToKicker = MCP_Initialize_Header(MCP_PACKET_TYPE_MCP_POWER_ALIVE, MCP_KICKER_BOARD);
	powerAliveHeaderToDribbler = MCP_Initialize_Header(MCP_PACKET_TYPE_MCP_POWER_ALIVE, MCP_DRIBBLER_BOARD);
	powerVoltageHeader = MCP_Initialize_Header(MCP_PACKET_TYPE_MCP_POWER_VOLTAGE, MCP_TOP_BOARD);

	// peripherals
	init_VPC_sensor();
	VPC_getVoltage(); // test to set write_OK and read_OK

	// MCP Alive
	MCP_SetReadyToReceive(true);
	MCP_Send_Im_Alive();
	/* === Wired communication with robot; Can now receive RobotCommands (and other REM packets) via UART */

	LOG_printf("Init Finished!");
	LOG_sendAll();
	heartbeat_10000ms = HAL_GetTick() + 10000;
	heartbeat_10ms = HAL_GetTick() + 10;
	HAL_IWDG_Refresh(&hiwdg);
}

uint8_t robot_get_ID(){
  return 0;
}

uint8_t robot_get_Channel(){
  return 0;
}

// Function to perform a kill operation
void kill() {
    set_Pin(BAT_KILL_pin, 0);
}

void MCP_resetSendMsg() {
	send_powerVoltage = false;
}

/* =================================================== */
/* ==================== MAIN LOOP ==================== */
/* =================================================== */
void loop() {
    uint32_t current_time = HAL_GetTick();

	HAL_IWDG_Refresh(&hiwdg);
	
	MCP_timeout();
    if (MCP_to_process){
        if (!MailBox_one.empty)
            MCP_Process_Message(&MailBox_one);
        if (!MailBox_two.empty)
            MCP_Process_Message(&MailBox_two);
        if (!MailBox_three.empty)
            MCP_Process_Message(&MailBox_three);
        MCP_to_process = false;
	}

	if (heartbeat_10ms < current_time) {
		n_samples_voltage += 1;
		avg_voltage = avg_voltage + ((VPC_getVoltage() - avg_voltage)/n_samples_voltage);
		heartbeat_10ms = current_time + 10;
	}

	// 10 seconds passed now we send the reading of the voltage meter to the top board
    if (heartbeat_10000ms < current_time || send_powerVoltage) {
		send_powerVoltage = true;
		LOG_printf("Sending voltage Meter\n");
		MCP_PowerVoltage pv = {0};
		MCP_PowerVoltagePayload pvp = {0};
		pv.voltagePowerBoard = avg_voltage;
		n_samples_voltage = 0;
		n_samples_voltage = 0;
		if (pv.voltagePowerBoard < MCP_PACKET_RANGE_MCP_POWER_VOLTAGE_VOLTAGE_POWER_BOARD_MIN) {
			pv.voltagePowerBoard = MCP_PACKET_RANGE_MCP_POWER_VOLTAGE_VOLTAGE_POWER_BOARD_MIN;
		} else if (pv.voltagePowerBoard > MCP_PACKET_RANGE_MCP_POWER_VOLTAGE_VOLTAGE_POWER_BOARD_MAX) {
			pv.voltagePowerBoard = MCP_PACKET_RANGE_MCP_POWER_VOLTAGE_VOLTAGE_POWER_BOARD_MAX;
		}
		encodeMCP_PowerVoltage(&pvp, &pv);
		MCP_Send_Message(&hcan, pvp.payload, powerVoltageHeader, MCP_TOP_BOARD);

    	heartbeat_10000ms = current_time + 10000;
		LOG_sendAll();
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

	bool send_ack = true;

	if (to_Process->message_id == MCP_PACKET_ID_TOP_TO_POWER_MCP_ARE_YOU_ALIVE) {
		MCP_Send_Im_Alive();
		send_ack = false;
	} else if (to_Process->message_id == MCP_PACKET_ID_TOP_TO_POWER_MCP_KILL) {
		kill();
	} else if (to_Process->message_id == MCP_PACKET_ID_TOP_TO_POWER_MCP_REBOOT) {
		HAL_Delay(1000);
	}

	if (send_ack) MCP_Send_Ack(&hcan, to_Process->data_Frame[0], to_Process->message_id);
	
	to_Process->empty = true;
	*to_Process->data_Frame  = 0;
	to_Process->message_id = 0;
}

void MCP_Send_Im_Alive() {
	MCP_PowerAlive pa = {0};
	MCP_PowerAlivePayload pap = {0};
	pa.sensorWorking = VPC_write_OK & VPC_read_OK;
	pa.voltagePowerBoard = VPC_getVoltage();
	encodeMCP_PowerAlive(&pap, &pa);
	MCP_Send_Message_Always(&hcan, pap.payload, powerAliveHeaderToTop);
	MCP_Send_Message_Always(&hcan, pap.payload, powerAliveHeaderToDribbler);
	MCP_Send_Message_Always(&hcan, pap.payload, powerAliveHeaderToKicker);
}