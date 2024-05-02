#ifndef INC_VOLTAGE_READING_H_
#define INC_VOLTAGE_READING_H_

#include "pages.h"
#include "robot.h"

void voltage_reading_init(page_struct *parent);
void voltage_update_page(page_struct *page);

#endif
