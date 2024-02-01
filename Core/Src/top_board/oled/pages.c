#include "pages.h"

void add_child_to_parent(page_struct *current);

///////////////////////////////////////////////////////////// Public functions

void pages_init() {
    //ROOT
    struct page_struct page_root;
    page_root.id = 0;
    strcpy(page_root.page_name, "Root");
    page_root.n_of_childeren = 1; //hard coded exception. Should normally be set to 0
    page_root.parent = NULL;
    page_root.is_menu = false;
    page_root.is_test = false;
    
    //MAIN MENU
    struct page_struct main_menu;
    main_menu.id = 1;
    strcpy(main_menu.page_name, "Main menu");
    main_menu.n_of_childeren = 0;
    main_menu.parent = NULL;
    main_menu.is_menu = true;
    main_menu.is_test = false;
    page_root.childeren[0] = &main_menu; //hard coded exception. Use add_child_to_parent for all other pages
    

    //LEVEL 1 MENU'S
    //1 < ID < 10
    struct page_struct self_test_menu;
    self_test_menu.id = 2;
    strcpy(self_test_menu.page_name, "Self Tests");
    self_test_menu.parent = &main_menu;   
    self_test_menu.n_of_childeren = 0;
    self_test_menu.is_menu = true;
    self_test_menu.is_test = false;
    add_child_to_parent(&self_test_menu);

    struct page_struct info_menu;
    info_menu.id = 3;
    strcpy(info_menu.page_name, "Info Menu");
    info_menu.parent = &main_menu;
    info_menu.n_of_childeren = 0;
    info_menu.is_menu = true;
    info_menu.is_test = false;
    add_child_to_parent(&info_menu);

    //LEVEL 2 MENU'S

    //LEVEL 2 MENU'S FOR SELF TESTS
    struct page_struct self_test_top_menu;
    self_test_top_menu.id = 21;
    strcpy(self_test_top_menu.page_name, "Top board");
    self_test_top_menu.parent = &self_test_menu;
    self_test_top_menu.n_of_childeren = 0;
    self_test_top_menu.is_menu = true;
    self_test_top_menu.is_test = false;
    add_child_to_parent(&self_test_top_menu);

    struct page_struct self_test_power_menu;
    self_test_power_menu.id = 22;
    strcpy(self_test_power_menu.page_name, "Power board");
    self_test_power_menu.parent = &self_test_menu;
    self_test_power_menu.n_of_childeren = 0;
    self_test_power_menu.is_menu = true;
    self_test_power_menu.is_test = false;
    add_child_to_parent(&self_test_power_menu);

    //LEVEL 3 MENU'S
    
    //LEVEL 3 MENU'S TOP BOARD SELF TESTS
    
    //BUZZER TEST
    struct page_struct buzzer_test;
    buzzer_test.id = 211;
    strcpy(buzzer_test.page_name, "Buzzer test");
    buzzer_test.parent = &self_test_top_menu;
    buzzer_test.n_of_childeren = 0;
    buzzer_test.is_menu = false;
    buzzer_test.is_test = true;
    strcpy(buzzer_test.line0, "Robot is");
    strcpy(buzzer_test.line1, "Rick Rolling you");
    strcpy(buzzer_test.line2, "Press any button");
    strcpy(buzzer_test.line3, "to return when done");
    add_child_to_parent(&buzzer_test);

    //MOTOR TEST

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
