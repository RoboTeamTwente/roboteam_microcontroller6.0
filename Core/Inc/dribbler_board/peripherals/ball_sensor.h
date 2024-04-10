#ifndef _BALL_SENSOR_H
#define _BALL_SENSOR_H

#include "main.h"
#include "dribbler_board.h"
#include "stdbool.h"
#include "logging.h"
#include "gpio_util.h"

void ballSensor_Init();
void ballSensor_DeInit();
void ballSensor_TestIfWorking();
void ballSensor_IRQ_Handler();
bool ballSensor_seesBall();

#endif /*_BALL_SENSOR_H*/