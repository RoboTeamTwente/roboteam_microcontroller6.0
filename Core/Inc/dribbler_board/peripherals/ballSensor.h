#ifndef _BALLSENSOR_H_
#define _BALLSENSOR_H_

#include "main.h"
#include "gpio_util.h"

#define DMA_bufferSize 1
#define state_bufferSize 10

extern bool ball_state;

void ballsensor_init();

void ballsensor_deinit();

void ballsensor_setIR_on();

void ballsensor_setIR_off();

bool ballsensor_hasBall();

#endif