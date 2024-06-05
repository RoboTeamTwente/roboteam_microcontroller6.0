#ifndef _KICKER_BOARD_H_
#define _KICKER_BOARD_H_

#include "logging.h"
#include "peripheral_util.h"
#include "main.h"
#include <string.h>
#include "shoot.h"
#include "MCP_Driver.h"
#include "MCP_to_kicker.h"
#include "MCP_from_kicker.h"
#include "voltage.h"
#include <math.h>

void init();
void loop();
uint8_t robot_get_ID();
uint8_t robot_get_Channel();

#endif /* _KICKER_BOARD_H_ */