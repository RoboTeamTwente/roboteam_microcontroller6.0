/*
 * CanDriver.h
 */

#ifndef INC_DRIVERS_CANDRIVER_H_
#define INC_DRIVERS_CANDRIVER_H_

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

void CAN_SendMessage(CAN_HandleTypeDef *hcan, uint32_t MessageId , uint8_t *TxData[8], uint32_t Length);

// The call back function for processing a message, AFTER it has passed the filter
bool extract_command(uint8_t RxData[], CAN_RxHeaderTypeDef *Header);

uint8_t bit_shiftMask(uint8_t offset, uint8_t n);

void CAN_error_LOG(CAN_TxHeaderTypeDef *Header);

#define MCP_VERSION 1
#define MCP_VERSION_LENGTH 4
#define MCP_VERSION_INDEX 0

//ID's
#define TOP_ID 0
#define POWER_ID 7
#define DRIBBLER_ID 1
#define KICK_CHIP_ID 4

//Common Messages and details for all
#define ARE_YOU_ALIVE 127
#define IM_ALIVE_VOLTAGE 126
#define IM_ALIVE_KICKER 125
#define IM_ALIVE_DRIBBLER 124
#define ACK 28

#define RECEIVER_ID_LOCATION 7
#define MESSAGE_ID_LOCATION 7 // To get the first 7 bits

	uint8_t set_mcp_version();

	void set_MCP_version(uint8_t payload[8]);

	uint8_t get_MCP_version(uint8_t payload[8]);

	void set_are_you_alive_message_header(CAN_TxHeaderTypeDef *TxHeader, uint8_t reciever_ID);

	void send_ACK();
//TOP and POWER

	// Message ID for TOP to POWER
	#define KILL_REQUEST_VOLTAGE_MESSAGE 1
		// TOP to POWER, these are the possible values in the payload for boolean
		#define KILL_STATE_INDEX 0
		#define KILL_BATTERY 1
		#define DONT_KILL_BATTERY 0

		#define REQUEST_POWER_INDEX 1
		#define REQUEST_POWER_VOLTAGE 1
		#define DONT_REQUEST_POWER_VOLTAGE 0

	// Message ID for POWER to TOP
	#define VOLTAGE_RESPONSE 1

		//POWER to TOP, this is the length in bits of the voltage
		#define VOLTAGE_LENGTH 16

	// Message ID for POWER to TOP, response to AREYOUALIVE
	// These are the possible values in the payload
	#define POWER_SENSOR_STATE_INDEX 6
	#define POWER_SENSOR_WORKING 1
	#define POWER_SENSOR_NOT_WORKING 0

	bool get_kill_state(uint8_t payload);

	bool get_request_power_state(uint8_t payload);

	void set_kill_voltage_message_header(CAN_TxHeaderTypeDef *TxHeader);

	void set_kill_state(uint8_t payload[8], bool kill_State);

	void set_request_power_state(uint8_t payload[8], bool request_State);

	void set_voltage_response_header(CAN_TxHeaderTypeDef *TxHeader);

	float get_voltage_response(uint8_t payload[8]);

	void set_voltage_response(float voltage_reading, uint8_t payload[]);

	void set_powerBoard_im_alive_header(CAN_TxHeaderTypeDef *TxHeader);

	void set_powerBoard_sensor_state(uint8_t payload[8], bool sensor_state);

	bool get_powerBoard_sensor_state(uint8_t payload[8]);

// TOP and DRIBBLER

	// Message ID for TOP to DRIBBLER
	#define DRIBBLER_SPEED 1

		//POWER to TOP, this is the index from start to stop
		#define DRIBBLER_SPEED_LENGTH 3;

	// Message ID for DRIBBLER to TOP
	#define DRIBBLER_SEESBALL_MESSAGE 2

	// MESSAGE ID for DRIBBLER to TOP
	#define BALLSENSOR_MESSAGE 3

	#define BALLSENSOR_SEES_BALL 1
	#define BALLSENSOR_NOT_SEES_BALL 0

	// Message ID for DRIBBLER to TOP, response to AREYOUALIVE
	// These are the possible values in the payload
	#define DRIBBLER_STATE_INDEX 6
	#define DRIBBLER_WORKING 1
	#define DRIBBLER_NOT_WORKING 0

	#define BALLSENSOR_STATE_INDEX 7
	#define BALLSENSOR_WORKING 1
	#define BALLSENSOR_NOT_WORKING 0

	void set_request_dribbler_speed_header(CAN_TxHeaderTypeDef *TxHeader);

	void set_response_dribbler_speed_header(CAN_TxHeaderTypeDef *TxHeader);

	void set_dribbler_speed(uint8_t payload[8], uint32_t dribbler_speed);

	uint32_t get_dribbler_speed(uint8_t payload[8]);

	void set_dribbler_sees_ball_header(CAN_TxHeaderTypeDef *TxHeader);

	void set_dribbler_sees_ball(uint8_t payload[8], bool dribbler_state);

	bool get_dribbler_sees_ball(uint8_t payload[8]);

	void set_ballsensor_sees_ball_header(CAN_TxHeaderTypeDef *TxHeader);

	void set_ball_sensor_sees_ball(uint8_t payload[8], bool ball_sensor_state);

	bool get_sensor_sees_ball(uint8_t payload[8]);

	void set_dribbler_im_alive(CAN_TxHeaderTypeDef *TxHeader);

	void set_dribbler_state(uint8_t payload[8], bool dribbler_state);

	bool get_dribbler_state(uint8_t payload[8]);

	void set_ballsensor_state(uint8_t payload[8], bool ballsensor_state);

	bool get_ball_sensor_state(uint8_t payload[8]);

// TOP and KICKER

	// Message ID for TOP to KICKER
	#define KICK_MESSAGE 1

		// TOP to KICKER, these are the possible values in the payload
		#define KICK_INDEX 0
		#define DO_KICK 1
		#define DONT_KICK 0

	// Message ID for KICKER to TOP
	#define CHIP_MESSAGE 2

		// TOP to KICKER, these are the possible values in the payload
		#define CHIP_INDEX 0
		#define DO_CHIP 1
		#define DONT_CHIP 0

	// Common values for both ID 1 and 2
	#define FORCE_INDEX 1
	#define DO_FORCE 1
	#define DONT_FORCE 0

	#define SHOOT_POWER_INDEX 2
	#define SHOOT_POWER_LENGTH 4

	// Message ID for TOP to KICKER
	#define DISCHARGE_MESSAGE 3

	// Message ID for TOP to KICKER
	#define REQUEST_CAPACITOR_VOLTAGE_MESSAGE 4

	// Message ID for KICKER to TOP
	#define CAPACITOR_VOLTAGE_MESSAGE 4

		//KICKER to TOP, this is the length in bits of the capacitor voltage
		#define CAPACITOR_VOLTAGE_START_INDEX 0
		#define CAPACITOR_VOLTAGE_END_INDEX 15
		#define CAPACITOR_VOLTAGE_LENGTH 16

	// Message ID for KICKER to TOP, response to AREYOUALIVE
	// These are the possible values in the payload
	#define CAPACITOR_SENSOR_STATE_INDEX 6
	#define CAPACITOR_SENSOR_WORKING 1
	#define CAPACITOR_SENSOR_NOT_WORKING 0

	#define CAPACITOR_CHARGING_INDEX 7
	#define CAPACITOR_CHARGING 1
	#define CAPACITOR_NOT_CHARGING 0

	void set_header_kick(CAN_TxHeaderTypeDef *TxHeader);

	void set_kick_state(uint8_t payload[8], bool kick_state);

	bool get_kick_state(uint8_t payload[8]);

	void set_do_Force(uint8_t payload[8], bool doForce_state);

	bool get_do_Force(uint8_t payload[8]);

	void set_shoot_power(uint8_t payload[8], uint16_t power);

	uint16_t get_shoot_power(uint8_t payload[8]);

	void set_header_chip(CAN_TxHeaderTypeDef *TxHeader);

	void set_chip_state(uint8_t payload[8], bool chip_state);

	bool get_chip_state(uint8_t payload[8]);


	void set_header_discharge(CAN_TxHeaderTypeDef *TxHeader);


	void set_request_capacitor_voltage_header(CAN_TxHeaderTypeDef *TxHeader);


	void set_response_capacitor_voltage_header(CAN_TxHeaderTypeDef *TxHeader);

	void set_capacitor_voltage_response(uint8_t payload[8], uint16_t voltage_reading);

	uint16_t get_capacitor_voltage_response(uint8_t payload[8]);

	void set_kicker_im_alive(CAN_TxHeaderTypeDef *TxHeader);

	void set_capacitor_sensor_state(uint8_t payload[8], bool sensor_state);

	bool get_capacitor_sensor_state(uint8_t payload[8]);

	void set_capacitor_charging_state(uint8_t payload[8], bool charging_state);

	bool get_capacitor_charging_state(uint8_t payload[8]);

	CAN_TxHeaderTypeDef CAN_Initalize_Header();

	void CAN_Process_Message(mailbox_buffer *to_Process);
	void CAN_Send_Message(uint8_t sending_message_ID, uint8_t reciever_ID ,CAN_HandleTypeDef *hcan);


#endif /* INC_DRIVERS_CANDRIVER_H_ */