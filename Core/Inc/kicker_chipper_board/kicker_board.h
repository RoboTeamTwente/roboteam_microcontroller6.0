#ifndef _KICKER_BOARD_H_
#define _KICKER_BOARD_H_

#include "logging.h"
#include "peripheral_util.h"
#include "CanDriver.h"
#include <string.h>
#include "shoot.h"

void init();
void loop();
uint8_t robot_get_ID();
uint8_t robot_get_Channel();

#endif /* _KICKER_BOARD_H_ */