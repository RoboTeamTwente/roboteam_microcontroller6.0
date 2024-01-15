/*
 * CanDriver.h
 *
 *  Created on: Dec 21, 2023
 *      Author: Csongor
 */

#ifndef INC_DRIVERS_CANDRIVER_H_
#define INC_DRIVERS_CANDRIVER_H_

#include "main.h"
#include <stdbool.h>

typedef void (*CanRxCallback)(uint8_t RxData[8], uint8_t MessageId, uint8_t MessageLength);
void CAN_SetRxCallback(CanRxCallback callback);

void CAN_Init(CAN_HandleTypeDef *hcan);
void CAN_SendMessage(CAN_HandleTypeDef *hcan, uint32_t MessageId , uint8_t TxData[8], uint32_t Length);

#define MCP_VERSION 0
#define MCP_VERSION_INDEX 0

//ID's
#define TOP_ID 0
#define POWER_ID 7
#define DRIBBLER_ID 1
#define KICK_CHIP_ID 4

//Common Messages and details for all
#define ARE_YOU_ALIVE 128
#define IM_ALIVE 128
#define RECEIVER_ID_LOCATION 7
#define MESSAGE_ID_LOCATION 7 // To get the first 7 bits

//TOP and POWER
	// Message ID for TOP to POWER
	#define KILL_VOLTAGE_MESSAGE 1

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
	#define POWER_SENSOR_STATE_INDEX 1
	#define POWER_SENSOR_WORKING 1
	#define POWER_SENSOR_NOT_WORKING 0

	// void get_kill_voltage_message(uint8_t payload){

	// }

	// void set_kill_voltage_message(CAN_TxHeaderTypeDef TxHeader, uint8_t payload[8]){

	// }

	// void get_voltage_response(uint8_t payload[8]);
	// void set_voltage_message();

// TOP and DRIBBLER

	// Message ID for TOP to DRIBBLER
	#define DRIBBLER_SPEED 1

		//POWER to TOP, this is the index from start to stop
		#define DRIBBLER_SPEED_LENGTH 3;

	// Message ID for DRIBBLER to TOP
	#define DRIBBLER_SEESBALL 2

	// MESSAGE ID for DRIBBLER to TOP
	#define BALLSENSOR_SEES_BALL 1

	// Message ID for DRIBBLER to TOP, response to AREYOUALIVE
	// These are the possible values in the payload
	#define DRIBBLER_STATE_INDEX 1
	#define DRIBBLER_WORKING 1
	#define DRIBBLER_NOT_WORKING 0

	#define BALLSENSOR_STATE_INDEX 2
	#define BALLSENSOR_WORKING 1
	#define BALLSENSOR_NOT_WORKING 0


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
		#define KICK_INDEX 0
		#define DO_CHIP 1
		#define DONT_CHIP 0

	// Common values for both ID 1 and 2
	#define FORCE_INDEX 1
	#define DO_FORCE 1
	#define DONT_FORCE 0

	#define SET_POWER_INDEX 2
	#define SET_POWER_LENGTH 4

	// Message ID for TOP to KICKER
	#define DISCHARGE 3

	// Message ID for TOP to KICKER
	#define REQUEST_CAPACITOR_VOLTAGE 4

	// Message ID for KICKER to TOP
	#define CAPACITOR_VOLTAGE 1

		//KICKER to TOP, this is the length in bits of the capacitor voltage
		#define CAPACITOR_VOLTAGE_START_INDEX 0
		#define CAPACITOR_VOLTAGE_END_INDEX 15
		#define CAPACITOR_VOLTAGE_LENGTH 16

	// Message ID for KICKER to TOP, response to AREYOUALIVE
	// These are the possible values in the payload
	#define CAPACITOR_SENSOR_STATE_INDEX 1
	#define CAPACITOR_SENSOR_WORKING 1
	#define CAPACITOR_SENSOR_NOT_WORKING 0





#endif /* INC_DRIVERS_CANDRIVER_H_ */
