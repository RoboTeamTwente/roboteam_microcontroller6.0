#ifndef _BALLSENSOR_H_
#define _BALLSENSOR_H_

#include "main.h"
#include "gpio_util.h"

#define DMA_bufferSize 1
#define AvgBufferSize 10

extern bool ballSensor_isWorking;

void ballsensor_init();

void ballsensor_deinit();

void ballsensor_test();

void ballsensor_setIR_on();

void ballsensor_setIR_off();

bool ballsensor_hasBall();

bool ballsesnor_previousState();

bool ballsesnor_changeState();

void ballsensor_DetectBall();

#endif