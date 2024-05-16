#ifndef INC_KICKER_STATUS_H_
#define INC_KICKER_STATUS_H_

#include "OLED_driver.h"
#include "robot.h"

void kicker_status_Init(page_struct *parent);
void kicker_status_Update(page_struct *page);


#endif /* INC_KICKER_STATUS_H_ */