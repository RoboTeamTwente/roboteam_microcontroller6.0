#include "info_menu.h"

struct page_struct general_info;
struct page_struct time_page;

/**
 * @brief initialize the pages that are the children of info menu
 * @note constraint for children of info menu: 20 < id < 30 
*/
void info_menu_initChildren(page_struct *parent) {
    pages_set_default_values(&general_info);
    general_info.id = 21;
    strcpy(general_info.page_name, "General");
    general_info.parent = parent;
    add_child_to_parent(&general_info);
    general_info_init(&general_info);

    pages_set_default_values(&time_page);
    time_page.id = 22;
    strcpy(time_page.page_name, "Robot time");
    time_page.parent = parent;
    time_page.has_variables = true;
    add_child_to_parent(&time_page);
}