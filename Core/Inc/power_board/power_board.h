#ifndef _POWER_BOARD_H_
#define _POWER_BOARD_H_

#include "logging.h"
#include "peripheral_util.h"
#include "CanDriver.h"
#include <string.h>

void init();
void loop();
uint8_t robot_get_ID();
uint8_t robot_get_Channel();

#endif /* _POWER_BOARD_H_ */