#include "pages.h"

///////////////////////////////////////////////////////////// Variables
struct page_struct page_root;
struct page_struct main_menu;
struct page_struct self_test_menu;
struct page_struct info_menu;
struct page_struct self_test_top_menu;
struct page_struct self_test_power_menu;
struct page_struct self_test_kicker_menu;
struct page_struct self_test_dribbler_menu;
struct page_struct buzzer_test;
struct page_struct not_in_test_mode;
struct page_struct error_no_children;

///////////////////////////////////////////////////////////// Private functions declarations

void add_child_to_parent(page_struct *current);

///////////////////////////////////////////////////////////// Public functions implementations

void pages_init() {
    //ROOT
    page_root.id = 0;
    strcpy(page_root.page_name, "Root");
    page_root.n_of_childeren = 0;
    page_root.parent = NULL;
    page_root.is_menu = false;
    page_root.is_test = false;
    page_root.has_variables = false;
    
    //MAIN MENU
    main_menu.id = 10;
    strcpy(main_menu.page_name, "Main menu");
    main_menu.n_of_childeren = 0;
    main_menu.parent = &page_root;
    main_menu.is_menu = true;
    main_menu.is_test = false;
    main_menu.has_variables = false;
    add_child_to_parent(&main_menu);

    //REDIRECTS
    not_in_test_mode.id = 20;
    strcpy(not_in_test_mode.page_name, "WARNING");
    not_in_test_mode.n_of_childeren = 0;
    not_in_test_mode.parent = NULL;
    not_in_test_mode.is_menu = false;
    not_in_test_mode.is_test = false;
    not_in_test_mode.has_variables = false;
    strcpy(not_in_test_mode.line0, "Robot is not");
    strcpy(not_in_test_mode.line1, "test-mode. Flip");
    strcpy(not_in_test_mode.line2, "switch 7 and");
    strcpy(not_in_test_mode.line3, "reboot the robot");

    error_no_children.id = 30;
    strcpy(error_no_children.page_name, "Exception");
    error_no_children.n_of_childeren = 0;
    error_no_children.parent = NULL;
    error_no_children.is_menu = false;
    error_no_children.is_test = false;
    error_no_children.has_variables = true;
    
    //LEVEL 1 MENU'S
    //1 < ID < 10
    self_test_menu.id = 1;
    strcpy(self_test_menu.page_name, "Self Tests");
    self_test_menu.parent = &main_menu;   
    self_test_menu.n_of_childeren = 0;
    self_test_menu.is_menu = true;
    self_test_menu.is_test = false;
    self_test_menu.has_variables = false;
    add_child_to_parent(&self_test_menu);

    info_menu.id = 2;
    strcpy(info_menu.page_name, "Info Menu");
    info_menu.parent = &main_menu;
    info_menu.n_of_childeren = 0;
    info_menu.is_menu = true;
    info_menu.is_test = false;
    info_menu.has_variables = false;
    add_child_to_parent(&info_menu);

    //LEVEL 2 MENU'S

    //LEVEL 2 MENU'S FOR SELF TESTS
    self_test_top_menu.id = 11;
    strcpy(self_test_top_menu.page_name, "Top board");
    self_test_top_menu.parent = &self_test_menu;
    self_test_top_menu.n_of_childeren = 0;
    self_test_top_menu.is_menu = true;
    self_test_top_menu.is_test = false;
    self_test_top_menu.has_variables = false;
    add_child_to_parent(&self_test_top_menu);

    self_test_power_menu.id = 12;
    strcpy(self_test_power_menu.page_name, "Power board");
    self_test_power_menu.parent = &self_test_menu;
    self_test_power_menu.n_of_childeren = 0;
    self_test_power_menu.is_menu = true;
    self_test_power_menu.is_test = false;
    self_test_power_menu.has_variables = false;
    add_child_to_parent(&self_test_power_menu);

    self_test_kicker_menu.id = 13;
    strcpy(self_test_kicker_menu.page_name, "Kicker board");
    self_test_kicker_menu.parent = &self_test_menu;
    self_test_kicker_menu.n_of_childeren = 0;
    self_test_kicker_menu.is_menu = true;
    self_test_kicker_menu.is_test = false;
    self_test_kicker_menu.has_variables = false;
    add_child_to_parent(&self_test_kicker_menu);

    self_test_dribbler_menu.id = 14;
    strcpy(self_test_dribbler_menu.page_name, "Dribbler board");
    self_test_dribbler_menu.parent = &self_test_menu;
    self_test_dribbler_menu.n_of_childeren = 0;
    self_test_dribbler_menu.is_menu = true;
    self_test_dribbler_menu.is_test = false;
    self_test_dribbler_menu.has_variables = false;
    add_child_to_parent(&self_test_dribbler_menu);

    //LEVEL 3 MENU'S
    
    //LEVEL 3 MENU'S TOP BOARD SELF TESTS
    
    //BUZZER TEST
    buzzer_test.id = 111;
    strcpy(buzzer_test.page_name, "Buzzer test");
    buzzer_test.parent = &self_test_top_menu;
    buzzer_test.n_of_childeren = 0;
    buzzer_test.is_menu = false;
    buzzer_test.is_test = true;
    buzzer_test.has_variables = false;
    strcpy(buzzer_test.line0, "Robot is");
    strcpy(buzzer_test.line1, "Rick Rolling you");
    strcpy(buzzer_test.line2, "Press any button");
    strcpy(buzzer_test.line3, "to return when done");
    add_child_to_parent(&buzzer_test);

    //MOTOR TEST

}

page_struct* getRootPage() {
    return &page_root;
}

page_struct* getNotInTestMode() {
    return &not_in_test_mode;
}

int getSelfTestMenuID() {
    return self_test_menu.id;
}

page_struct* getErrorNoChildren() {
    return &error_no_children;
}

///////////////////////////////////////////////////////////// Private functions


void add_child_to_parent(page_struct *current) {
    page_struct *parent = current->parent;
    if(parent->n_of_childeren < MAX_CHILDEREN) {
        parent->childeren[parent->n_of_childeren] = current;
        parent->n_of_childeren++;
    } else {
        //TODO some kind of error
    }
}
