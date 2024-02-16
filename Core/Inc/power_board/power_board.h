#ifndef _POWER_BOARD_H_
#define _POWER_BOARD_H_

#include "logging.h"
#include "peripheral_util.h"
#include "CanDriver.h"
#include <string.h>

/*CAN BUS flags*/
extern uint16_t heartbeat_10000ms;

void init();
void loop();

#endif /* _POEWR_BOARD_H_ */