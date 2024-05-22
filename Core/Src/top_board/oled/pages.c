#include "pages.h"

///////////////////////////////////////////////////////////// Variables
struct page_struct page_root; 
struct page_struct main_menu;
struct page_struct not_in_test_mode;
struct page_struct error_no_children;
struct page_struct error_menu_has_too_many_children;

///////////////////////////////////////////////////////////// Public functions implementations

void pages_init() {
    //ROOT
    pages_set_default_values(&page_root);
    page_root.id = 0;
    strcpy(page_root.page_name, "Root");
    page_root.parent = NULL;
    
    //MAIN MENU
    pages_set_default_values(&main_menu);
    main_menu.id = 10;
    strcpy(main_menu.page_name, "Main menu");
    main_menu.parent = &page_root;
    main_menu.is_menu = true;
    add_child_to_parent(&main_menu);
    main_menu_initChildren(&main_menu);

    //REDIRECTS
    pages_set_default_values(&not_in_test_mode);
    not_in_test_mode.id = 20;
    strcpy(not_in_test_mode.page_name, "WARNING");
    not_in_test_mode.parent = NULL;
    strcpy(not_in_test_mode.line0, "Robot is not");
    strcpy(not_in_test_mode.line1, "test-mode. Flip");
    strcpy(not_in_test_mode.line2, "switch 7 and");
    strcpy(not_in_test_mode.line3, "reboot the robot");

    pages_set_default_values(&error_no_children);
    error_no_children.id = 30;
    strcpy(error_no_children.page_name, "Error");
    error_no_children.parent = NULL;
}

void pages_set_default_values(page_struct *p) {
    p -> n_of_children = 0;
    p -> is_menu = false;
    p -> is_test = NOT_A_TEST;
    p -> has_variables = false;
}

page_struct* getRootPage() {
    return &page_root;
}

page_struct* getNotInTestMode() {
    return &not_in_test_mode;
}

page_struct* getErrorNoChildren() {
    return &error_no_children;
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
