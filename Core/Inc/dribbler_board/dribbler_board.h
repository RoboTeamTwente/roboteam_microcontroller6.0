#ifndef _DRIBBLER_BOARD_H_
#define _DRIBBLER_BOARD_H_

#include "main.h"
#include "MCP_Driver.h"
#include "MCP_from_dribbler.h"
#include "MCP_to_dribbler.h"
#include "dribbler.h"
#include "logging.h"
#include "ballSensor.h"

#include "gpio_util.h"
#include "tim_util.h"
#include "peripheral_util.h"
#include <string.h>

extern volatile bool BOARD_INITIALIZED;
extern MCP_DribblerCommand dribblerCommand;

void init();
void loop();
uint8_t robot_get_ID();
uint8_t robot_get_Channel();

#endif /* _DRIBBLER_BOARD_H_ */