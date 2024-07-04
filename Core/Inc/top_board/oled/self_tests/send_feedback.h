#ifndef SEND_FEEDBACK_H_
#define SEND_FEEDBACK_H_

#include "OLED_driver.h"
#include "robot.h"

void init_sendFeedback(page_struct *parent);
void start_sendFeeback();
void stop_sendFeedback();

#endif /* SEND_FEEDBACK_H_ */