#include "self_test_menu.h"

struct page_struct self_test_top_menu;
struct page_struct self_test_power_menu;
struct page_struct self_test_kicker_menu;
struct page_struct self_test_dribbler_menu;

/**
 * @brief initialize the pages that are the children of self test menu
 * @note constraint for children of self test menu: 10 < id < 20 
*/
void self_test_menu_initChildren(page_struct *parent) {
    self_test_top_menu.id = 11;
    strcpy(self_test_top_menu.page_name, "Top board");
    self_test_top_menu.parent = parent;
    self_test_top_menu.n_of_childeren = 0;
    self_test_top_menu.is_menu = true;
    self_test_top_menu.is_test = false;
    self_test_top_menu.has_variables = false;
    add_child_to_parent(&self_test_top_menu);
    buzzer_test_init(&self_test_top_menu);
    wheel_twitch_init(&self_test_top_menu);

    self_test_power_menu.id = 12;
    strcpy(self_test_power_menu.page_name, "Power board");
    self_test_power_menu.parent = parent;
    self_test_power_menu.n_of_childeren = 0;
    self_test_power_menu.is_menu = true;
    self_test_power_menu.is_test = false;
    self_test_power_menu.has_variables = false;
    add_child_to_parent(&self_test_power_menu);

    self_test_kicker_menu.id = 13;
    strcpy(self_test_kicker_menu.page_name, "Kicker board");
    self_test_kicker_menu.parent = parent;
    self_test_kicker_menu.n_of_childeren = 0;
    self_test_kicker_menu.is_menu = true;
    self_test_kicker_menu.is_test = false;
    self_test_kicker_menu.has_variables = false;
    add_child_to_parent(&self_test_kicker_menu);

    self_test_dribbler_menu.id = 14;
    strcpy(self_test_dribbler_menu.page_name, "Dribbler board");
    self_test_dribbler_menu.parent = parent;
    self_test_dribbler_menu.n_of_childeren = 0;
    self_test_dribbler_menu.is_menu = true;
    self_test_dribbler_menu.is_test = false;
    self_test_dribbler_menu.has_variables = false;
    add_child_to_parent(&self_test_dribbler_menu);

}