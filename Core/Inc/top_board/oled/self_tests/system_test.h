#ifndef INC_SYSTEM_TEST_H_
#define INC_SYSTEM_TEST_H_

#include "pages.h"

extern bool system_test_running;

void system_test_init(page_struct *parent);
void system_test_run();
void system_test_finished_reset();

#endif /* INC_SYSTEM_TEST_H_ */