#ifndef INC_PAGES_H_
#define INC_PAGES_H_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"
#include "logging.h"
#include "main_menu.h"
#include "OLED_driver.h"

/* Public functions */
void pages_init(page_struct *p);
void pages_set_default_values(page_struct *page, page_struct *parent);
void add_child_to_parent(page_struct *current);


#endif /* INC_PAGES_H_ */