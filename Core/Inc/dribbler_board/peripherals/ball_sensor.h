#ifndef _BALL_SENSOR_H
#define _BALL_SENSOR_H

#include "main.h"
#include "stdbool.h"
#include "logging.h"

void ballSensor_Init();
void ballSensor_DeInit();
void ballSensor_IRQ_Handler();
bool ballSensor_seesBall();

#endif /*_BALL_SENSOR_H*/