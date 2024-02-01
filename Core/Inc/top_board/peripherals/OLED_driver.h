#ifndef INC_OLED_H_
#define INC_OLED_H_

#include "ssd1306/OledDriver.h"
#include "button.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ssd1306/bitmap.h"
#include "pages.h"
#include "selftests.h"

void OLED_Init();
void OLED_DeInit();
void OLED_Update(button_id_t button);

#endif /* INC_OLED_H_ */