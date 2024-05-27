#ifndef INC_REM_PAGE_H_
#define INC_REM_PAGE_H_

#include "pages.h"
#include "robot.h"
#include <stdio.h>
#include <stdlib.h>

void rem_page_init(page_struct *parent);
void rem_page_update(page_struct *page);
void rem_page_add_timestamp(uint64_t recieved_time);

#endif /* INC_REM_PAGE_H_ */