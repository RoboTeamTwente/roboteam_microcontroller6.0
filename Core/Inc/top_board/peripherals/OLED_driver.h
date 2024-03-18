#ifndef INC_OLED_H_
#define INC_OLED_H_

#include "ssd1306/OledDriver.h"
#include "button.h"
#include "drivers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ssd1306/bitmap.h"
#include "pages.h"
#include "selftest_selector.h"
#include "variable_page_selector.h"
#include "robot.h"

extern bool test_is_finished;

void OLED_Init();
void OLED_DeInit();
void OLED_Update(button_id_t button, bool test_mode);
void OLED_set_error_too_many_children(char* page_name);
void start_of_test();
void end_of_test();
enum test_type OLED_get_current_page_test_type();

#endif /* INC_OLED_H_ */ 