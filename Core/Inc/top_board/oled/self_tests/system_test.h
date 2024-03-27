#ifndef INC_SYSTEM_TEST_H_
#define INC_SYSTEM_TEST_H_

#include "OLED_driver.h"

extern bool system_test_running;

void system_test_init(page_struct *parent);
void system_test_run();
uint32_t get_system_test_time_started();
bool get_system_test_running();

#endif /* INC_SYSTEM_TEST_H_ */