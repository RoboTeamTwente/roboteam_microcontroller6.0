#include "pages.h"

///////////////////////////////////////////////////////////// Variables
struct page_struct page_root;
struct page_struct main_menu;
struct page_struct not_in_test_mode;
struct page_struct error_no_children;

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
    main_menu_initChildren(&main_menu);

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
    if(parent->n_of_childeren < MAX_CHILDEREN) {
        parent->childeren[parent->n_of_childeren] = current;
        parent->n_of_childeren++;
    } else {
        //TODO some kind of error
    }
}
