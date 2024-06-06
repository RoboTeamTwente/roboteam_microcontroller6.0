#include "kicker_board.h"

void MCP_Process_Message(mailbox_buffer *to_Process);
void MCP_Send_Im_Alive();
void checkVoltage();
void checkStatus();

volatile bool BOARD_INITIALIZED = false;
static bool sensor_working = false;
static bool send_Voltage = false;
static bool send_Status = false;

// Outgoing packet headers
CAN_TxHeaderTypeDef kickerAliveToTopHeader = {0};
CAN_TxHeaderTypeDef kickerAliveToPowerHeader = {0};
CAN_TxHeaderTypeDef kickerAliveToDribblerHeader = {0};
CAN_TxHeaderTypeDef kickerCapacitorHeader = {0};
CAN_TxHeaderTypeDef kickerStatusHeader = {0};

// Outgoing packet 
MCP_KickerCapacitorVoltage MCP_CapacitorVoltage = {0};
MCP_KickerStatus MCP_Status = {0};

// Incoming packet

/* ======================================================== */
/* ==================== INITIALIZATION ==================== */
/* ======================================================== */
void init() {
	HAL_IWDG_Refresh(&hiwdg);
    // MCP
	MCP_Init(&hcan, MCP_KICKER_BOARD);
	kickerAliveToTopHeader = MCP_Initialize_Header(MCP_PACKET_TYPE_MCP_KICKER_ALIVE, MCP_TOP_BOARD);
	kickerAliveToPowerHeader = MCP_Initialize_Header(MCP_PACKET_TYPE_MCP_KICKER_ALIVE, MCP_POWER_BOARD);
	kickerAliveToDribblerHeader = MCP_Initialize_Header(MCP_PACKET_TYPE_MCP_KICKER_ALIVE, MCP_DRIBBLER_BOARD);
	kickerCapacitorHeader = MCP_Initialize_Header(MCP_PACKET_TYPE_MCP_KICKER_CAPACITOR_VOLTAGE, MCP_TOP_BOARD);
	kickerStatusHeader = MCP_Initialize_Header(MCP_PACKET_TYPE_MCP_KICKER_STATUS, MCP_TOP_BOARD);

	// Peripherals
	voltage_Init();
	shoot_Init();

	// MCP Alive
	MCP_SetReadyToReceive(true);
	MCP_Send_Im_Alive();

	BOARD_INITIALIZED = true;
	HAL_IWDG_Refresh(&hiwdg);
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
	HAL_IWDG_Refresh(&hiwdg);
	uint32_t time = HAL_GetTick();

	MCP_timeout();
    if (MCP_to_process) {
        if (!MailBox_one.empty)
            MCP_Process_Message(&MailBox_one);
        if (!MailBox_two.empty)
            MCP_Process_Message(&MailBox_two);
        if (!MailBox_three.empty)
            MCP_Process_Message(&MailBox_three);
        MCP_to_process = false;
	}

	checkStatus();
	checkVoltage();
	
}

void MCP_Process_Message(mailbox_buffer *to_Process){
	bool send_ack = true;
	
	if (to_Process->message_id == MCP_PACKET_ID_TOP_TO_KICKER_MCP_ARE_YOU_ALIVE) {
		MCP_Send_Im_Alive();
		send_ack = false;
	} else if (to_Process->message_id == MCP_PACKET_ID_TOP_TO_KICKER_MCP_REBOOT) {
		HAL_Delay(1000);
	} else if (to_Process->message_id == MCP_PACKET_ID_TOP_TO_KICKER_MCP_CHIP) {
		MCP_ChipPayload* cp = (MCP_ChipPayload*) to_Process->data_Frame;
		MCP_Chip mcp_chip = {0};
		decodeMCP_Chip(&mcp_chip, cp);
		shoot_Shoot(shoot_Chip,mcp_chip.shootPower);
	} else if (to_Process->message_id == MCP_PACKET_ID_TOP_TO_KICKER_MCP_KICK) {
		MCP_KickPayload* kp = (MCP_KickPayload*) to_Process->data_Frame;
		MCP_Kick mcp_kick = {0};
		decodeMCP_Kick(&mcp_kick, kp);
		shoot_Shoot(shoot_Kick,mcp_kick.shootPower);
	} else if (to_Process->message_id == MCP_PACKET_ID_TOP_TO_KICKER_MCP_KICKER_CHARGE) {
		shoot_StartCharging();
	} else if (to_Process->message_id == MCP_PACKET_ID_TOP_TO_KICKER_MCP_KICKER_STOP_CHARGE) {
		shoot_DisableCharging();
	}

	if (send_ack) MCP_Send_Ack(&hcan, to_Process->data_Frame[0], to_Process->message_id);
		
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

void MCP_Send_Im_Alive() {
	MCP_KickerAlive ka = {0};
	MCP_KickerAlivePayload kap = {0};
	ka.sensorWorking = sensor_working;
	encodeMCP_KickerAlive(&kap, &ka);
	MCP_Send_Message_Always(&hcan, kap.payload, kickerAliveToDribblerHeader);
	MCP_Send_Message_Always(&hcan, kap.payload, kickerAliveToPowerHeader);
	MCP_Send_Message_Always(&hcan, kap.payload, kickerAliveToTopHeader);
}

void checkVoltage() {
	voltage_Read();
	uint32_t capVoltage = roundf(voltage_Get());
	if (capVoltage > MCP_PACKET_RANGE_MCP_KICKER_CAPACITOR_VOLTAGE_VOLTAGE_MAX) capVoltage = MCP_PACKET_RANGE_MCP_KICKER_CAPACITOR_VOLTAGE_VOLTAGE_MAX;
	if (MCP_CapacitorVoltage.voltage != capVoltage) {
		MCP_CapacitorVoltage.voltage = capVoltage;
		send_Voltage = true;
	}

	if (send_Voltage && MCP_GetFreeToSend(MCP_TOP_BOARD)) {
		// MCP_KickerCapacitorVoltagePayload kcvp = {0};
		// encodeMCP_KickerCapacitorVoltage(&kcvp, &MCP_CapacitorVoltage);
		// MCP_Send_Message(&hcan, &kcvp, kickerCapacitorHeader, MCP_TOP_BOARD);
		send_Voltage = false;
	}
}

void checkStatus() {
	bool on = shootState != shoot_Off;
	if (MCP_Status.kickerOn != on) {
		MCP_Status.kickerOn = on;
		send_Status = true;
	}

	if (MCP_Status.kickerFault != shoot_fault) {
		MCP_Status.kickerFault = shoot_fault;
		send_Status = true;
	}

	if (MCP_Status.kickerReady != shoot_charged) {
		MCP_Status.kickerReady = shoot_charged;
		send_Status = true;
	}

	if (send_Status && MCP_GetFreeToSend(MCP_TOP_BOARD)) {
		MCP_KickerStatusPayload ksp = {0};
		encodeMCP_KickerStatus(&ksp, &MCP_Status);
		MCP_Send_Message(&hcan, &ksp, kickerStatusHeader, MCP_TOP_BOARD);
		send_Status = false;
	}
}