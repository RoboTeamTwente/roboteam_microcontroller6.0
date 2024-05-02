#ifndef INC_INFO_MENU_H_
#define INC_INFO_MENU_H_

#include "OLED_driver.h"
#include "general_info.h"
#include "encoder_page.h"
#include "mcp_page.h"
#include "time_page.h"
#include "voltage_reading.h"

void info_menu_initChildren(page_struct *parent);

#endif /* INC_INFO_MENU_H_ */