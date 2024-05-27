#ifndef INC_KICK_SELF_TEST_H_
#define INC_KICK_SELF_TEST_H_

#include "OLED_driver.h"
#include "kicker_test.h"
#include "chip_test.h"

void kicker_self_test_menu_initChildren(page_struct *parent);
void kicker_charge();
void kicker_stopCharge();


#endif /* INC_KICK_SELF_TEST_H_ */