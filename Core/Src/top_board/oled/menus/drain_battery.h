#ifndef INC_DRAIN_BATTERY_H_
#define INC_DRAIN_BATTERY_H_

#include "OLED_driver.h"
#include "robot.h"

extern bool DRAIN_BATTERY;

void drain_battery_initChildren(page_struct *parent);
void drain_battery_run(float target);
void drain_battery_update_screen(page_struct *p);

#endif /* INC_DRAIN_BATTERY_H_ */