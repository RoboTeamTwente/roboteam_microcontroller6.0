#ifndef INC_MAIN_MENU_H_
#define INC_MAIN_MENU_H_

#include "OLED_driver.h"
#include "self_test_menu.h"
#include "info_menu.h"

void main_menu_initChildren(page_struct *parent);
int getSelfTestMenuID();

#endif /* INC_MAIN_MENU_H_ */