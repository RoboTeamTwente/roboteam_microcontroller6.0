#include "info_menu.h"

struct page_struct general_info;

/**
 * @brief initialize the pages that are the children of info menu
 * @note constraint for children of info menu: 20 < id < 30 
*/
void info_menu_initChildren(page_struct *parent) {
    general_info.id = 21;
    strcpy(general_info.page_name, "General");
    general_info.parent = parent;
    general_info.n_of_childeren = 0;
    general_info.is_menu = false;
    general_info.is_test = false;
    general_info.has_variables = false;
    add_child_to_parent(&general_info);
    general_info_init(&general_info);
}