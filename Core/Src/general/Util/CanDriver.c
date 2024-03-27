/*
 * CanDriver.c
 * This file contains the implementation of a CAN driver for communication between different components of a system.
 */

#include "CanDriver.h"
#include "logging.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Definition of mailbox buffers
mailbox_buffer MailBox_one    = {true, {0, 0, 0, 0, 0, 0, 0, 0}, 0};
mailbox_buffer MailBox_two    = {true, {0, 0, 0, 0, 0, 0, 0, 0}, 0};
mailbox_buffer MailBox_three  = {true, {0, 0, 0, 0, 0, 0, 0, 0}, 0};
char str[75];
bool CAN_to_process = false;

// Function to initialize CAN communication
void CAN_Init(CAN_HandleTypeDef *hcan, uint8_t board_id){

    // Configuration of CAN filter
    CAN_FilterTypeDef canfilterconfig;
    canfilterconfig.FilterActivation = CAN_FILTER_ENABLE;
    canfilterconfig.FilterBank = 10;
    canfilterconfig.FilterFIFOAssignment = CAN_RX_FIFO0;
    canfilterconfig.FilterIdHigh = board_id << 12;
    canfilterconfig.FilterIdLow = 0x0000;
    canfilterconfig.FilterMaskIdHigh = 0xF000;
    canfilterconfig.FilterMaskIdLow = 0x0000;
    canfilterconfig.FilterMode = CAN_FILTERMODE_IDMASK;
    canfilterconfig.FilterScale = CAN_FILTERSCALE_32BIT;
    canfilterconfig.SlaveStartFilterBank = 0;

    // Configure CAN filter
    HAL_CAN_ConfigFilter(hcan, &canfilterconfig);

    // Start CAN communication
    HAL_CAN_Start(hcan);
    HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
}

// Function to handle CAN errors
void CAN_error_LOG(CAN_TxHeaderTypeDef *Header){
    return;  // Placeholder function, not implemented
}

// Function to send an acknowledgment message
void send_ACK(){
    // Placeholder function, not implemented
}

// Callback function for pending CAN messages in FIFO0
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan){
    CAN_RxHeaderTypeDef RxHeader;
    uint8_t RxData[8];
    memset(RxData, 0, sizeof(RxData));
    HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData);

    // Extract and process the received command
    CAN_to_process = extract_command(RxData, &RxHeader);
}

// Function to extract command from received CAN data
bool extract_command(uint8_t RxData[], CAN_RxHeaderTypeDef *Header){
    uint8_t message_ID = 0x7F & Header->StdId;
    uint8_t data[8];
    memset(data, 0, sizeof(data));

    // Copy received data to local array
    for (int i = 0; i < Header->DLC; i++)
        data[i] = RxData[i];

    // Check and store the command in the appropriate mailbox
    if(MailBox_one.empty){
        MailBox_one.empty = false;
        MailBox_one.message_id = message_ID;
        memcpy(MailBox_one.data_Frame, data, sizeof(data));
        return true;
    } else if (MailBox_two.empty){
        MailBox_two.empty = false;
        MailBox_two.message_id = message_ID;
        memcpy(MailBox_two.data_Frame, data, sizeof(data));
        return true;
    } else if (MailBox_three.empty){
        MailBox_three.empty = false;
        MailBox_three.message_id = message_ID;
        memcpy(MailBox_three.data_Frame, data, sizeof(data));
        return true;
    }

    // Free dynamically allocated memory and return false if mailboxes are full
    free(data);
    return false;
}

// Function to create a bitmask for shifting bits
uint8_t bit_shiftMask(uint8_t offset, uint8_t n){
    return (0b11111111 >> (8 - n)) << offset;
}

// Function to retrieve the MCP version
uint8_t set_mcp_version(){
    return MCP_VERSION;
}

// Function to set the MCP version in a payload
void set_MCP_version(uint8_t payload[8]){
    payload[0] = MCP_VERSION;
}

// Function to get the MCP version from a payload
uint8_t get_MCP_version(uint8_t payload[8]){
    return payload[0] & bit_shiftMask(0, MCP_VERSION_LENGTH);
}

// Function to set the header for "Are You Alive" message
void set_are_you_alive_message_header(CAN_TxHeaderTypeDef *TxHeader, uint8_t receiver_ID){
    TxHeader->StdId = (receiver_ID << RECEIVER_ID_LOCATION) | ARE_YOU_ALIVE;
}

// Function to get the kill state from a payload
bool get_kill_state(uint8_t payload){
    return (bool) ((payload & bit_shiftMask(0, 1)) >> KILL_STATE_INDEX);
}

// Function to get the request power state from a payload
bool get_request_power_state(uint8_t payload){
    return (bool) ((payload & bit_shiftMask(1, 1)) >> REQUEST_POWER_INDEX);
}

// Function to set the header for "Kill Voltage" message
void set_kill_voltage_message_header(CAN_TxHeaderTypeDef *TxHeader){
    TxHeader->StdId = (POWER_ID << RECEIVER_ID_LOCATION) | KILL_REQUEST_VOLTAGE_MESSAGE;
}

// Function to set the kill state in a payload
void set_kill_state(uint8_t payload[8], bool kill_State){
    payload[0] = (payload[0] & 0b11111110) | ((kill_State << KILL_STATE_INDEX) & bit_shiftMask(0, 1));
}

// Function to set the request power state in a payload
void set_request_power_state(uint8_t payload[8], bool request_State){
    payload[0] = (payload[0] & 0b11111101) | ((request_State << REQUEST_POWER_INDEX) & bit_shiftMask(1, 1));
}

// Function to set the header for "Voltage Response" message
void set_voltage_response_header(CAN_TxHeaderTypeDef *TxHeader){
    TxHeader->DLC = 2;
    TxHeader->StdId = (TOP_ID << RECEIVER_ID_LOCATION) | VOLTAGE_RESPONSE;
}

// Function to get the voltage response from a payload
uint16_t get_voltage_response(uint8_t payload[8]){
    return ((payload[1] << 8) | payload[0]) & 0xFFFF;
}

// Function to set the voltage response in a payload
void set_voltage_response(uint16_t voltage_reading, uint8_t payload[]){
    payload[0] = voltage_reading;
    payload[1] =  voltage_reading >> 8;
}

// Function to set the header for "PowerBoard I'm Alive" message
void set_powerBoard_im_alive_header(CAN_TxHeaderTypeDef *TxHeader){
    TxHeader->StdId = (TOP_ID << RECEIVER_ID_LOCATION) | IM_ALIVE_VOLTAGE;
}

// Function to set the power board sensor state in a payload
void set_powerBoard_sensor_state(uint8_t payload[8], bool sensor_state){
    payload[0] = payload[0] | (sensor_state << POWER_SENSOR_STATE_INDEX);
}

// Function to get the power board sensor state from a payload
bool get_powerBoard_sensor_state(uint8_t payload[8]){
    return (bool) (payload[0] >> POWER_SENSOR_STATE_INDEX);
}

// Function to set the header for "Request Dribbler Speed" message
void set_request_dribbler_speed_header(CAN_TxHeaderTypeDef *TxHeader){
    TxHeader->StdId = (DRIBBLER_ID << RECEIVER_ID_LOCATION) | DRIBBLER_SPEED;
}

// Function to set the header for "Response Dribbler Speed" message
void set_response_dribbler_speed_header(CAN_TxHeaderTypeDef *TxHeader){
    TxHeader->StdId = (TOP_ID << RECEIVER_ID_LOCATION) | DRIBBLER_SPEED;
}

// Function to set the dribbler speed in a payload
void set_dribbler_speed(uint8_t payload[], float dribbler_speed){
    payload[0] = dribbler_speed;
}

// Function to get the dribbler speed from a payload
float get_dribbler_speed(uint8_t payload[8]){
    return (payload[0] & 0b11111111) * 0.0039215686274510F;
}

// Function to set the header for "Dribbler Sees Ball" message
void set_dribbler_sees_ball_header(CAN_TxHeaderTypeDef *TxHeader){
    TxHeader->StdId = (TOP_ID << RECEIVER_ID_LOCATION) | DRIBBLER_SEESBALL_MESSAGE;
}

// Function to set the dribbler sees ball state in a payload
void set_dribbler_sees_ball(uint8_t payload[], bool dribbler_state){
    payload[0] = dribbler_state & bit_shiftMask(0, 1);
}

// Function to get the dribbler sees ball state from a payload
bool get_dribbler_sees_ball(uint8_t payload[8]){
    return (bool) (payload[0] & bit_shiftMask(0, 1));
}

// Function to set the header for "Ball Sensor" message
void set_ballsensor_header(CAN_TxHeaderTypeDef *TxHeader){
    TxHeader->StdId = (TOP_ID << RECEIVER_ID_LOCATION) | BALLSENSOR_MESSAGE;
}

// Function to set the ball sensor sees ball state in a payload
void set_ball_sensor_sees_ball(uint8_t payload[8], bool ball_sensor_state){
    payload[0] = bit_shiftMask(0, 1) & ball_sensor_state;
}

// Function to get the ball sensor sees ball state from a payload
bool get_sensor_sees_ball(uint8_t payload[8]){
    return (bool) (payload[0] & bit_shiftMask(0,1));
}

// Function to set the header for "Dribbler I'm Alive" message
void set_dribbler_im_alive(CAN_TxHeaderTypeDef *TxHeader){
    TxHeader->StdId = (TOP_ID << RECEIVER_ID_LOCATION) | IM_ALIVE_DRIBBLER;
}

// Function to set the dribbler state in a payload
void set_dribbler_state(uint8_t payload[8], bool dribbler_state){
    payload[0] = payload[0] | (dribbler_state << DRIBBLER_STATE_INDEX);
}

// Function to get the dribbler state from a payload
bool get_dribbler_state(uint8_t payload[8]){
    return (bool) ((payload[0] & bit_shiftMask(DRIBBLER_STATE_INDEX, 1)) >> DRIBBLER_STATE_INDEX);
}

// Function to set the ball sensor state in a payload
void set_ballsensor_state(uint8_t payload[8], bool ballsensor_state){
    payload[0] = payload[0] | (ballsensor_state << BALLSENSOR_STATE_INDEX);
}

// Function to get the ball sensor state from a payload
bool get_ball_sensor_state(uint8_t payload[8]){
    return (bool) ((payload[0] & bit_shiftMask(BALLSENSOR_STATE_INDEX, 1)) >> BALLSENSOR_STATE_INDEX);
}

// Function to set the header for "Kick" message
void set_header_kick(CAN_TxHeaderTypeDef *TxHeader){
    TxHeader->StdId = (KICK_CHIP_ID << RECEIVER_ID_LOCATION) | KICK_MESSAGE;
}

// Function to set the kick state in a payload
void set_kick_state(uint8_t payload[8], bool kick_state){
    payload[0] = kick_state << KICK_INDEX;
}

// Function to get the kick state from a payload
bool get_kick_state(uint8_t payload[8]){
    return (bool) ((payload[0] & bit_shiftMask(KICK_INDEX, 1)) >> KICK_INDEX);
}

// Function to set the do force state in a payload
void set_do_Force(uint8_t payload[8], bool doForce_state){
    payload[0] = payload[0] | ( doForce_state <<  FORCE_INDEX );
}

// Function to get the do force state from a payload
bool get_do_Force(uint8_t payload[8]){
    return (bool) ((payload[0] & bit_shiftMask(FORCE_INDEX, 1)) >> FORCE_INDEX) ;
}

// Function to set the shoot power in a payload
void set_shoot_power(uint8_t payload[8], uint8_t power){
    payload[0] = payload[0] | ( power << SHOOT_POWER_INDEX ) ;
}

// Function to get the shoot power from a payload
uint8_t get_shoot_power(uint8_t payload[8]){
    return ( payload[0] & bit_shiftMask(SHOOT_POWER_INDEX, SHOOT_POWER_LENGTH) ) >> SHOOT_POWER_INDEX;
}

// Function to set the header for "Chip" message
void set_header_chip(CAN_TxHeaderTypeDef *TxHeader){
    TxHeader->StdId = (KICK_CHIP_ID << RECEIVER_ID_LOCATION) | CHIP_MESSAGE;
}

// Function to set the chip state in a payload
void set_chip_state(uint8_t payload[8], bool chip_state){
    payload[0] = chip_state << CHIP_INDEX;
}

// Function to get the chip state from a payload
bool get_chip_state(uint8_t payload[8]){
    return (bool) ((payload[0] & bit_shiftMask(CHIP_INDEX, 1)) >> CHIP_INDEX);
}

// Function to set the header for "Discharge" message
void set_header_discharge(CAN_TxHeaderTypeDef *TxHeader){
    TxHeader->StdId = (KICK_CHIP_ID << RECEIVER_ID_LOCATION) | DISCHARGE_MESSAGE;
    // No need to set payload here as sending this implies discharge
}

// Function to set the header for "Request Capacitor Voltage" message
void set_request_capacitor_voltage_header(CAN_TxHeaderTypeDef *TxHeader){
    TxHeader->StdId = (KICK_CHIP_ID << RECEIVER_ID_LOCATION) | REQUEST_CAPACITOR_VOLTAGE_MESSAGE;
    // No need to set payload here as sending this implies a request for data
}

// Function to set the header for "Response Capacitor Voltage" message
void set_response_capacitor_voltage_header(CAN_TxHeaderTypeDef *TxHeader){
    TxHeader->DLC = 2;
    TxHeader->StdId = (TOP_ID << RECEIVER_ID_LOCATION) | CAPACITOR_VOLTAGE_MESSAGE;
    // No need to set payload here as sending this implies a response with data
}

// Function to set the capacitor voltage response in a payload
void set_capacitor_voltage_response(uint8_t payload[8], uint16_t voltage_reading){
    payload[0] =  voltage_reading >> 8;
    payload[1] =  voltage_reading;
}

// Function to get the capacitor voltage response from a payload
uint16_t get_capacitor_voltage_response(uint8_t payload[8]){
    return (payload[0] << 8) | payload[1];
}

// Function to set the header for "Kicker I'm Alive" message
void set_kicker_im_alive(CAN_TxHeaderTypeDef *TxHeader){
    TxHeader->StdId = (TOP_ID << RECEIVER_ID_LOCATION) | IM_ALIVE_KICKER;
    // No need to set payload here as sending this implies a request for data
}

// Function to set the capacitor sensor state in a payload
void set_capacitor_sensor_state(uint8_t payload[8], bool sensor_state){
    payload[0] = payload[0] | (sensor_state << CAPACITOR_SENSOR_STATE_INDEX);
}

// Function to get the capacitor sensor state from a payload
bool get_capacitor_sensor_state(uint8_t payload[8]){
    return (bool) ((payload[0] & bit_shiftMask(CAPACITOR_SENSOR_STATE_INDEX, 1)) >> CAPACITOR_SENSOR_STATE_INDEX);
}

// Function to set the capacitor charging state in a payload
void set_capacitor_charging_state(uint8_t payload[8], bool charging_state){
    payload[0] =   payload[0] | (charging_state << CAPACITOR_CHARGING_INDEX);
}

// Function to get the capacitor charging state from a payload
bool get_capacitor_charging_state(uint8_t payload[8]){
    return (bool) ((payload[0] & bit_shiftMask(CAPACITOR_CHARGING_INDEX, 1)) >> CAPACITOR_CHARGING_INDEX);
}

// Function to perform a kill operation
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
