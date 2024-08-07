#include "pages.h"

///////////////////////////////////////////////////////////// Variables
struct page_struct main_menu;

///////////////////////////////////////////////////////////// Public functions implementations

void pages_init(page_struct *p) {    
    //MAIN MENU
    pages_set_default_values(&main_menu, p);
    main_menu.id = 10;
    strcpy(main_menu.page_name, "Main menu");
    main_menu.is_menu = true;
    add_child_to_parent(&main_menu);
    main_menu_initChildren(&main_menu);
}

void pages_set_default_values(page_struct *page, page_struct *parent) {
    page -> n_of_children = 0;
    page -> is_menu = false;
    page -> is_test = NOT_A_TEST;
    page -> has_variables = false;
    page -> parent = parent;
}

void page_set_page_name(char* name, page_struct *page) {
    if (strlen(name) > MAX_MENU_NAME_LENGTH) {
        pageNameTooLongException(name);
    } else {
        strcpy(page->page_name, name);
    }
}

void page_put_text_in_line(page_struct *page, char* text, int lineNum) {
    if (strlen(text) > MAX_STRING_LENGTH) {
        textTooLongException(page->page_name, lineNum, strlen(text));
    } else {
        switch (lineNum) {
        case 0:
            strcpy(page->line0, text);
            break;
        case 1:
            strcpy(page->line1, text);
            break;
        case 2:
            strcpy(page->line2, text);
            break;
        case 3:
            strcpy(page->line3, text);
            break;
        default:
            unknownLineNumber(page->page_name, lineNum);
            break;
        }
    }
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
