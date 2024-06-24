#ifndef INC_CHIP_TEST_H_
#define INC_CHIP_TEST_H_

#include "OLED_driver.h"
#include "robot.h"

void chip_test_initChildren(page_struct *parent);
void chip_shoot_run(float speed, page_struct *page);

#endif /* INC_CHIP_TEST_H_ */