#ifndef INC_PAGES_H_
#define INC_PAGES_H_

#include "main.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "logging.h"

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

void pages_init();
page_struct* getRootPage();
page_struct* getNotInTestMode();
int getSelfTestMenuID();


#endif /* INC_PAGES_H_ */