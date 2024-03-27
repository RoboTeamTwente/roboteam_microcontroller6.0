#include "general_info.h"

void general_info_init(page_struct *page) {
    char temp[MAX_STRING_LENGTH];
    sprintf(temp, "ID: %d", robot_get_ID());
    strcpy(page->line0, temp);
    if (robot_get_Channel()) {
        strcpy(page->line1, "Team: Blue");
    } else {
        strcpy(page->line1, "Team: Yellow");
    }
    sprintf(temp, "REM version: %d", REM_LOCAL_VERSION);
    strcpy(page->line2, temp);
}