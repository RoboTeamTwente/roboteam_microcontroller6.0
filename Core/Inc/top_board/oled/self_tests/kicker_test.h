#ifndef INC_KICKER_TEST_H_
#define INC_KICKER_TEST_H_

#include "OLED_driver.h"
#include "robot.h"

void kicker_test_initChildren(page_struct *parent);
void kicker_shoot_run(float speed);
void kicker_discharge();

#endif /* INC_KICKER_TEST_H_ */