#ifndef _POWER_BOARD_H_
#define _POWER_BOARD_H_

#include "VPC_Sensor.h"
#include "peripheral_util.h"
#include "MCP_to_power.h"
#include "MCP_from_power.h"
#include "MCP_BaseTypes.h"
#include "MCP_Driver.h"
#include <string.h>
#include "iwdg.h"

void init();
void loop();
uint8_t robot_get_ID();
uint8_t robot_get_Channel();

#endif /* _POWER_BOARD_H_ */