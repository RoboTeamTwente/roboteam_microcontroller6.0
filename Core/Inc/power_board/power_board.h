#ifndef _POWER_BOARD_H_
#define _POWER_BOARD_H_

#include "logging.h"
#include "peripheral_util.h"
#include "CanDriver.h"


/*CAN BUS flags*/
extern uint16_t heartbeat_10000ms;
bool kill_flag;
bool voltage_request;
uint16_t voltage_reading;
uint64_t TxMailbox[0];  // Declaration of an array used in CAN

void init();
void loop();

#endif /* _POEWR_BOARD_H_ */