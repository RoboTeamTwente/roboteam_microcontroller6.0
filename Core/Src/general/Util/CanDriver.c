/*
 * CanDriver.c
 */
#include "CanDriver.h"

mailbox_buffer MailBox_one	 = {true, {0, 0, 0, 0, 0, 0, 0, 0}, 0};
mailbox_buffer MailBox_two 	 = {true, {0, 0, 0, 0, 0, 0, 0, 0}, 0};;
mailbox_buffer MailBox_three  = {true, {0, 0, 0, 0, 0, 0, 0, 0}, 0};
char str[75];
bool CAN_to_process = false;

void CAN_Init(CAN_HandleTypeDef *hcan){

	CAN_FilterTypeDef canfilterconfig;

	canfilterconfig.FilterActivation = CAN_FILTER_ENABLE;
	canfilterconfig.FilterBank = 10;  // anything between 0 to SlaveStartFilterBank
	canfilterconfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	canfilterconfig.FilterIdHigh = 0x000<<5;
	canfilterconfig.FilterIdLow = 0x0000;
	canfilterconfig.FilterMaskIdHigh = TOP_ID << 9; // change the ID to that of the name of the board
	canfilterconfig.FilterMaskIdLow = 0x0000;
	canfilterconfig.FilterMode = CAN_FILTERMODE_IDMASK;
	canfilterconfig.FilterScale = CAN_FILTERSCALE_32BIT;
	canfilterconfig.SlaveStartFilterBank = 0;  // 13 to 27 are assigned to slave CAN (CAN 2) OR 0 to 12 are assigned to CAN1

	HAL_CAN_ConfigFilter(hcan, &canfilterconfig);

	HAL_CAN_Start(hcan);
	HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
}

void CAN_error_LOG(CAN_TxHeaderTypeDef *Header){
	LOG("[CAN] Failed to transmit message\n");
	LOG_send();
}

void send_ACK(){ // each ACK will be different per board

}


void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) // this is defined in the hal_can lib
{
	CAN_RxHeaderTypeDef RxHeader;
	uint8_t RxData[8];
	memset(RxData, 0, sizeof(RxData));
	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData);

	CAN_to_process = extract_command(RxData, &RxHeader);
}

bool extract_command(uint8_t RxData[], CAN_RxHeaderTypeDef *Header){
	uint8_t message_ID = 0x7F & Header->StdId;
	uint8_t data[8];
    memset(data, 0, sizeof(data));


	for (int i=0; i<Header->DLC; i++)
		data[i] = RxData[i];

	if(MailBox_one.empty){
		MailBox_one.empty = false;
		MailBox_one.message_id = message_ID;
		memcpy(MailBox_one.data_Frame, data, sizeof(data));
		return true;
	}else if (MailBox_two.empty){
		MailBox_two.empty = false;
		MailBox_two.message_id = message_ID;
		memcpy(MailBox_two.data_Frame, RxData, sizeof(data));
		return true;
	}else if (MailBox_three.empty){
		MailBox_three.empty = false;
		MailBox_three.message_id = message_ID;
		memcpy(MailBox_three.data_Frame, RxData, sizeof(data));
		return true;
	}
	free(data);
	return false;
}

uint8_t bit_shiftMask(uint8_t offset, uint8_t n){
	return (0b11111111 >> (8-n)) << offset;
}

uint8_t set_mcp_version(){
	return MCP_VERSION;
}

void set_MCP_version(uint8_t payload[8]){
	payload[0] = MCP_VERSION;
}

uint8_t get_MCP_version(uint8_t payload[8]){
	return payload[0] & bit_shiftMask(0, MCP_VERSION_LENGTH);
}

void set_are_you_alive_message_header(CAN_TxHeaderTypeDef *TxHeader, uint8_t reciever_ID){
	TxHeader->StdId = (reciever_ID << RECEIVER_ID_LOCATION) | ARE_YOU_ALIVE;
}

bool get_kill_state(uint8_t payload){
	return (bool) ((payload & bit_shiftMask(0, 1)) >> KILL_STATE_INDEX);
}

bool get_request_power_state(uint8_t payload){
	return (bool) ((payload & bit_shiftMask(1, 1)) >> REQUEST_POWER_INDEX);
}

void set_kill_voltage_message_header(CAN_TxHeaderTypeDef *TxHeader){
	TxHeader->StdId = (POWER_ID << RECEIVER_ID_LOCATION) | KILL_REQUEST_VOLTAGE_MESSAGE;
}

void set_kill_state(uint8_t payload[8], bool kill_State){
	payload[0] = (payload[0] & 0b11111110) | ((kill_State << KILL_STATE_INDEX) & bit_shiftMask(0, 1));
}

void set_request_power_state(uint8_t payload[8], bool request_State){
	payload[0] = (payload[0] & 0b11111101) | ((request_State << REQUEST_POWER_INDEX) & bit_shiftMask(1, 1));
}

void set_voltage_response_header(CAN_TxHeaderTypeDef *TxHeader){
	TxHeader->DLC = 2; // 2 as we are only sending 2 bytes
	TxHeader->StdId = (POWER_ID << RECEIVER_ID_LOCATION) | VOLTAGE_RESPONSE;
}

uint16_t get_voltage_response(uint8_t payload[8]){
	return ( (payload[1] << 8) | payload[0]) & 0xFFFF;
}

void set_voltage_response(uint16_t voltage_reading, uint8_t payload[]){
	payload[0] = voltage_reading;
	payload[1] =  voltage_reading >> 8;
}

void set_powerBoard_im_alive_header(CAN_TxHeaderTypeDef *TxHeader){
	TxHeader->StdId = (TOP_ID << RECEIVER_ID_LOCATION) | IM_ALIVE_VOLTAGE;
}

void set_powerBoard_sensor_state(uint8_t payload[8], bool sensor_state){
	payload[0] = payload[0] | (sensor_state << POWER_SENSOR_STATE_INDEX);
}

bool get_powerBoard_sensor_state(uint8_t payload[8]){
	return (bool) (payload[0] >> POWER_SENSOR_STATE_INDEX);
}

void set_request_dribbler_speed_header(CAN_TxHeaderTypeDef *TxHeader){ 
	TxHeader->StdId = (DRIBBLER_ID << RECEIVER_ID_LOCATION) | DRIBBLER_SPEED;
}

void set_response_dribbler_speed_header(CAN_TxHeaderTypeDef *TxHeader){
	TxHeader->StdId = (TOP_ID << RECEIVER_ID_LOCATION) | DRIBBLER_SPEED;
}

void set_dribbler_speed(uint8_t payload[], float dribbler_speed){
	payload[0] = dribbler_speed;
}

float get_dribbler_speed(uint8_t payload[8]){
	return (payload[0] & 0b11111111) * 0.0039215686274510F;
}

void set_dribbler_sees_ball_header(CAN_TxHeaderTypeDef *TxHeader){
	TxHeader->StdId = (TOP_ID << RECEIVER_ID_LOCATION) | DRIBBLER_SEESBALL_MESSAGE;
}

void set_dribbler_sees_ball(uint8_t payload[], bool dribbler_state){
	payload[0] = dribbler_state & bit_shiftMask(0, 1);
}

bool get_dribbler_sees_ball(uint8_t payload[8]){
	return (bool) (payload[0] & bit_shiftMask(0, 1));
}

void set_ballsensor_header(CAN_TxHeaderTypeDef *TxHeader){
	TxHeader->StdId = (TOP_ID << RECEIVER_ID_LOCATION) | BALLSENSOR_MESSAGE;
}

void set_ball_sensor_sees_ball(uint8_t payload[8], bool ball_sensor_state){
	payload[0] = bit_shiftMask(0, 1) & ball_sensor_state;
}

bool get_sensor_sees_ball(uint8_t payload[8]){
	return (bool) (payload[0] & bit_shiftMask(0,1));
}

void set_dribbler_im_alive(CAN_TxHeaderTypeDef *TxHeader){
	TxHeader->StdId = (TOP_ID << RECEIVER_ID_LOCATION) | IM_ALIVE_DRIBBLER;
}

void set_dribbler_state(uint8_t payload[8], bool dribbler_state){
	payload[0] = payload[0] | (dribbler_state << DRIBBLER_STATE_INDEX);
}

bool get_dribbler_state(uint8_t payload[8]){
	return (bool) ((payload[0] & bit_shiftMask(DRIBBLER_STATE_INDEX, 1)) >> DRIBBLER_STATE_INDEX);
}

void set_ballsensor_state(uint8_t payload[8], bool ballsensor_state){
	payload[0] = payload[0] | (ballsensor_state << BALLSENSOR_STATE_INDEX);
}

bool get_ball_sensor_state(uint8_t payload[8]){
	return (bool) ((payload[0] & bit_shiftMask(BALLSENSOR_STATE_INDEX, 1)) >> BALLSENSOR_STATE_INDEX);
}

void set_header_kick(CAN_TxHeaderTypeDef *TxHeader){
	TxHeader->StdId = (KICK_CHIP_ID << RECEIVER_ID_LOCATION) | KICK_MESSAGE;
}

void set_kick_state(uint8_t payload[8], bool kick_state){
	payload[0] = kick_state << KICK_INDEX;
}

bool get_kick_state(uint8_t payload[8]){
	return (bool) ((payload[0] & bit_shiftMask(KICK_INDEX, 1)) >> KICK_INDEX);
}

void set_do_Force(uint8_t payload[8], bool doForce_state){
	payload[0] = payload[0] | ( doForce_state <<  FORCE_INDEX );
}

bool get_do_Force(uint8_t payload[8]){
	return (bool) ((payload[0] & bit_shiftMask(FORCE_INDEX, 1)) >> FORCE_INDEX) ;
}

void set_shoot_power(uint8_t payload[8], uint8_t power){
	payload[0] = payload[0] | ( power << SHOOT_POWER_INDEX ) ;
}

uint8_t get_shoot_power(uint8_t payload[8]){
	return ( payload[0] & bit_shiftMask(SHOOT_POWER_INDEX, SHOOT_POWER_LENGTH) ) >> SHOOT_POWER_INDEX;
}

void set_header_chip(CAN_TxHeaderTypeDef *TxHeader){// sent by TOP to DRIBBLER
	TxHeader->StdId = (KICK_CHIP_ID << RECEIVER_ID_LOCATION) | CHIP_MESSAGE;
}

void set_chip_state(uint8_t payload[8], bool chip_state){
	payload[0] = chip_state << CHIP_INDEX;
}

bool get_chip_state(uint8_t payload[8]){
	return (bool) ((payload[0] & bit_shiftMask(CHIP_INDEX, 1)) >> CHIP_INDEX);
}


void set_header_discharge(CAN_TxHeaderTypeDef *TxHeader){// sent by TOP to DRIBBLER
	TxHeader->StdId = (KICK_CHIP_ID << RECEIVER_ID_LOCATION) | DISCHARGE_MESSAGE; // no need to set payload here as when this is send it implies we must discharge
}


void set_request_capacitor_voltage_header(CAN_TxHeaderTypeDef *TxHeader){
	TxHeader->StdId = (KICK_CHIP_ID << RECEIVER_ID_LOCATION) | REQUEST_CAPACITOR_VOLTAGE_MESSAGE; // no need to set payload here as when this is send it implies we want the data
}


void set_response_capacitor_voltage_header(CAN_TxHeaderTypeDef *TxHeader){
	TxHeader->DLC = 2;
	TxHeader->StdId = (TOP_ID << RECEIVER_ID_LOCATION) | CAPACITOR_VOLTAGE_MESSAGE; // no need to set payload here as when this is send it implies we want the data
}

void set_capacitor_voltage_response(uint8_t payload[8], uint16_t voltage_reading){
	payload[0] =  voltage_reading >> 8;
	payload[1] =  voltage_reading;
}

uint16_t get_capacitor_voltage_response(uint8_t payload[8]){
	return (payload[0] << 8) | payload[1];
}

void set_kicker_im_alive(CAN_TxHeaderTypeDef *TxHeader){
	TxHeader->StdId = (TOP_ID << RECEIVER_ID_LOCATION) | IM_ALIVE_KICKER; // no need to set payload here as when this is send it implies we want the data
}

void set_capacitor_sensor_state(uint8_t payload[8], bool sensor_state){
	payload[0] = payload[0] | (sensor_state << CAPACITOR_SENSOR_STATE_INDEX);
}

bool get_capacitor_sensor_state(uint8_t payload[8]){
	return (bool) ((payload[0] & bit_shiftMask(CAPACITOR_SENSOR_STATE_INDEX, 1)) >> CAPACITOR_SENSOR_STATE_INDEX);
}

void set_capacitor_charging_state(uint8_t payload[8], bool charging_state){
	payload[0] =   payload[0] | (charging_state << CAPACITOR_CHARGING_INDEX);
}

bool get_capacitor_charging_state(uint8_t payload[8]){
	return (bool) ((payload[0] & bit_shiftMask(CAPACITOR_CHARGING_INDEX, 1)) >> CAPACITOR_CHARGING_INDEX);
}

void kill(){
 //HAL_GPIO_WritePin(Kill_GPIO_Port, Kill_Pin, GPIO_PIN_RESET);
}

// Function to initialize CAN header structure
CAN_TxHeaderTypeDef CAN_Initalize_Header(){

    CAN_TxHeaderTypeDef TxHeader;

    TxHeader.DLC = 1;
    TxHeader.ExtId = 0;
    TxHeader.IDE = CAN_ID_STD;
    TxHeader.RTR = CAN_RTR_DATA;
    TxHeader.TransmitGlobalTime = DISABLE;
    return TxHeader;
}
