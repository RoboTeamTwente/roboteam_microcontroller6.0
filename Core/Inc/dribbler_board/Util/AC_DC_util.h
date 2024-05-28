#ifndef UTILS_AC_DC_UTIL_H
#define UTILS_TIM_UTIL_H_

#include "stm32f3xx_hal.h"
#include "main.h"

// ANALOG TO DIGITAL 
#define CURRENT_DRIBBLER (&hadc1)
#define BALL_SENSOR_IN (&hadc2)

// DIGITAL TO ANALOG
#define VOLTAGE_DRIBBLER (&hdac1)


#endif //UTILS_AC_DC_UTIL_H
