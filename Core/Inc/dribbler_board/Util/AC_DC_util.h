#ifndef UTILS_AC_DC_UTIL_H
#define UTILS_TIM_UTIL_H_

#include "stm32f3xx_hal.h"
#include "main.h"

// ANALOG TO DIGITAL 
#define CUR_DRIBBLER (&hadc1)
#define BALL_SENSOR_IN (&hadc2)

// DIGITAL TO ANALOG
#define VOLT_DRIBBLER (&hdac1)


#endif //UTILS_AC_DC_UTIL_H
