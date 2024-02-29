#include "main_menu.h"

struct page_struct self_test_menu;
struct page_struct info_menu;

/**
 * @brief initialize the pages that are the children of main menu
 * @note constraint for children of main menu: 0 < id < 10 
*/
void main_menu_initChildren(page_struct *parent) {
    self_test_menu.id = 1;
    strcpy(self_test_menu.page_name, "Self Tests");
    self_test_menu.parent = parent;   
    self_test_menu.n_of_childeren = 0;
    self_test_menu.is_menu = true;
    self_test_menu.is_test = false;
    self_test_menu.has_variables = false;
    add_child_to_parent(&self_test_menu);
    self_test_menu_initChildren(&self_test_menu);

    info_menu.id = 2;
    strcpy(info_menu.page_name, "Info Menu");
    info_menu.parent = parent;
    info_menu.n_of_childeren = 0;
    info_menu.is_menu = true;
    info_menu.is_test = false;
    info_menu.has_variables = false;
    add_child_to_parent(&info_menu);
    info_menu_initChildren(&info_menu);
}

int getSelfTestMenuID() {
    return self_test_menu.id;
}