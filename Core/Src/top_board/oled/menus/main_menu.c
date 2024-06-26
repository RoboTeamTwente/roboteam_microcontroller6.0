#include "main_menu.h"

struct page_struct self_test_menu; //DO NOT DELETE THIS ONE
struct page_struct info_menu;
struct page_struct drain_battery_menu;

/**
 * @brief initialize the pages that are the children of main menu
 * @note constraint for children of main menu: 0 < id < 10 
*/
void main_menu_initChildren(page_struct *parent) {
    pages_set_default_values(&self_test_menu, parent);
    self_test_menu.id = 1;
    strcpy(self_test_menu.page_name, "Self Tests");
    self_test_menu.is_menu = true;
    add_child_to_parent(&self_test_menu);
    self_test_menu_initChildren(&self_test_menu);

    pages_set_default_values(&info_menu, parent);
    info_menu.id = 2;
    strcpy(info_menu.page_name, "Info Menu");
    info_menu.is_menu = true;
    add_child_to_parent(&info_menu);
    info_menu_initChildren(&info_menu);

    pages_set_default_values(&drain_battery_menu, parent);
    drain_battery_menu.id = 3;
    strcpy(drain_battery_menu.page_name, "Drain battery");
    drain_battery_menu.is_menu = true;
    add_child_to_parent(&drain_battery_menu);
    drain_battery_initChildren(&drain_battery_menu);
}

int getSelfTestMenuID() {
    return self_test_menu.id;
}