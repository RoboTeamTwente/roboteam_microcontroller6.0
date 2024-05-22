#include "pages.h"

///////////////////////////////////////////////////////////// Variables
struct page_struct main_menu;

///////////////////////////////////////////////////////////// Public functions implementations

void pages_init(page_struct *p) {    
    //MAIN MENU
    pages_set_default_values(&main_menu);
    main_menu.id = 10;
    strcpy(main_menu.page_name, "Main menu");
    main_menu.parent = p;
    main_menu.is_menu = true;
    add_child_to_parent(&main_menu);
    main_menu_initChildren(&main_menu);
}

void pages_set_default_values(page_struct *p) {
    p -> n_of_children = 0;
    p -> is_menu = false;
    p -> is_test = NOT_A_TEST;
    p -> has_variables = false;
}

/**
 * @brief add page as child to it's parent
*/
void add_child_to_parent(page_struct *current) {
    page_struct *parent = current->parent;
    if(parent->n_of_children < MAX_CHILDEREN) {
        parent->children[parent->n_of_children] = current;
        parent->n_of_children++;
    } else {
        OLED_set_error_too_many_children(parent->page_name);
    }
}
