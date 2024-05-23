#include "general_info.h"

struct page_struct general_info;

void general_info_init(page_struct *parent) {
    pages_set_default_values(&general_info, parent);
    general_info.id = 21;
    strcpy(general_info.page_name, "General");
    add_child_to_parent(&general_info);

    char temp[MAX_STRING_LENGTH];
    sprintf(temp, "ID: %d", robot_get_ID());
    strcpy(general_info.line0, temp);
    if (robot_get_Channel()) {
        strcpy(general_info.line1, "Team: Blue");
    } else {
        strcpy(general_info.line1, "Team: Yellow");
    }
    sprintf(temp, "REM version: %d", REM_LOCAL_VERSION);
    strcpy(general_info.line2, temp);
}