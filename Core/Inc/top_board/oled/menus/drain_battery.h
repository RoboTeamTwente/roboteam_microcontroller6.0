#ifndef INC_DRAIN_BATTERY_H_
#define INC_DRAIN_BATTERY_H_

#include "OLED_driver.h"

extern bool DRAIN_BATTERY;

void drain_battery_initChildren(page_struct *parent);
void drain_battery_run(float target);

#endif /* INC_DRAIN_BATTERY_H_ */