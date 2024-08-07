#ifndef INC_OLED_H_
#define INC_OLED_H_

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_CHILDEREN 9
#define MAX_MENU_NAME_LENGTH 15
#define MAX_STRING_LENGTH 23

typedef struct page_struct page_struct;

enum test_type {
    NOT_A_TEST,
    BLOCKING_TEST,
    NON_BLOCKING_TEST,
};

struct page_struct
{
    int id;
    char page_name[MAX_MENU_NAME_LENGTH];
    page_struct *parent;
    page_struct *children[MAX_CHILDEREN]; 
    int n_of_children;
    bool is_menu;
    enum test_type is_test;
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

#include "button.h"
#include "drivers.h"
#include "ssd1306/bitmap.h"
#include "pages.h"
#include "selftest_selector.h"
#include "variable_page_selector.h"
#include "robot.h"
#include "ssd1306/OledDriver.h"
#include "main.h"

extern bool test_is_finished;

void OLED_Init();
void OLED_DeInit();
void OLED_Update(button_id_t button, bool test_mode);
void OLED_set_error_too_many_children(char* page_name);
void start_of_test();
void end_of_test();
enum test_type OLED_get_current_page_test_type();
void end_of_boot_screen(bool MCP_OK);
void display_text();
void pageNameTooLongException(char* name);
void textTooLongException(char* page_name, int line, int length);
void unknownLineNumber(char* page_name, int line);

#endif /* INC_OLED_H_ */ 