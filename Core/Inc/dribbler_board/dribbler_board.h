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

void init();
void loop();

#endif /* _DRIBBLER_BOARD_H_ */