#ifndef _DRIBBLER_BOARD_H_
#define _DRIBBLER_BOARD_H_

#include "main.h"
#include "CanDriver.h"
#include "ball_sensor.h"
#include "dribbler.h"
#include "logging.h"

#include "control_util.h"
#include "gpio_util.h"
#include "tim_util.h"
#include "peripheral_util.h"
#include <string.h>

bool dribbler_state;
bool ballsensor_state;

void init();
void loop();
void CAN_Send_Message(uint8_t sending_message_ID, uint8_t reciever_ID ,CAN_HandleTypeDef *hcan);
void dribbler_CALLBACK_FUNCTION();

#endif /* _DRIBBLER_BOARD_H_ */