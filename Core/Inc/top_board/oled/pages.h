#ifndef INC_PAGES_H_
#define INC_PAGES_H_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CHILDEREN 9
#define MAX_VAR_NAME_LENGTH 9
#define MAX_MENU_NAME_LENGTH 15
#define MAX_SUBMENU_NAME_LENGTH 23
#define MAX_STRING_LENGTH 23

typedef struct page_struct page_struct;

struct page_struct
{
    int id;
    char page_name[MAX_MENU_NAME_LENGTH];
    page_struct *parent;
    page_struct *childeren[MAX_CHILDEREN]; 
    int n_of_childeren;
    bool is_menu;
    bool is_test;
    bool has_variables;
    char line0[MAX_STRING_LENGTH];
    char line1[MAX_STRING_LENGTH];
    char line2[MAX_STRING_LENGTH];
    char line3[MAX_STRING_LENGTH];
};

/*
 * NOTE: these includes need to underneath the declaration of the struct 
 * to not break uses of the page_struct in other files
*/
#include "main.h"
#include "logging.h"
#include "main_menu.h"

/* Public functions */
void pages_init();
page_struct* getRootPage();
page_struct* getNotInTestMode();
page_struct* getErrorNoChildren();
void add_child_to_parent(page_struct *current);


#endif /* INC_PAGES_H_ */