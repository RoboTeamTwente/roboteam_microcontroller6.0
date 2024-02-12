#include "OLED_driver.h"

///////////////////////////////////////////////////// PRIVATE FUNCTION DECLARATIONS
static void boot_screen();
static void clear_screen();
static void refresh();
static void static_page();
static void scrollable_page();
static void  menu_move_sideways(int direction);
static void display_text();

///////////////////////////////////////////////////// VARIABLES
static bool oled_initialized = false;
static page_struct *current_page;
static int item_selector;
static int id_not_in_test_mode;
static int id_self_test_menu;

///////////////////////////////////////////////////// PUBLIC FUNCTION IMPLEMENTATIONS


void OLED_Init(){
    clear_screen();
    boot_screen();
    current_page = getRootPage();
    item_selector = 0;
    oled_initialized = true;
    id_not_in_test_mode = getNotInTestMode()->id;
    id_self_test_menu = getSelfTestMenuID();
}

void OLED_DeInit(){
    oled_initialized = false;
}

void OLED_Update(button_id_t button, bool test_mode) {
    if(!oled_initialized || button == BUTTON_NONE) {
        return;
    }

    if (current_page->id == 0 || current_page->id == id_not_in_test_mode) {
        current_page = getRootPage()->childeren[0];
        item_selector = 0;
    } else {
        switch(button){
            case BUTTON_UP:
                if (current_page->is_menu) {
                    item_selector -= 1;
                }
                break;
            case BUTTON_DOWN:
                if (current_page->is_menu) {
                    item_selector = (item_selector + 1) % (current_page->n_of_childeren + 1);
                }
                break;
            case BUTTON_LEFT:
                if (current_page->is_menu) {
                    menu_move_sideways(-1);
                    item_selector = 0;
                }
                break;
            case BUTTON_RIGHT:
                if (current_page->is_menu) {
                    menu_move_sideways(1);
                    item_selector = 0;
                }
                break;
            case BUTTON_OK:
                if (current_page->is_menu){
                    if (item_selector < current_page->n_of_childeren) {
                        current_page = current_page->childeren[item_selector];
                    } else {
                        current_page = current_page->parent;
                    }
                    item_selector = 0;
                }
                break;
            default:
                break;
        }
    }
    if (!test_mode && current_page->id == id_self_test_menu) {
        current_page = getNotInTestMode();
    }

    refresh();
    resetButtonState(button);
}


///////////////////////////////////////////////////// PRIVATE FUNCTION IMPLEMENTATIONS

/**
 * @brief clear screen
*/
static void clear_screen(){
    SSD1306_Fill(0);
}

/**
 * @brief draw RoboTeam logo
*/
static void boot_screen(){
	SSD1306_DrawBitmap(0, 0, rtt_logo, 128, 64, 1);
	SSD1306_UpdateScreen(); // update screen
}

/**
 * @brief Put text and/or drawings on screen 
*/
static void refresh(){
    clear_screen();
    if (current_page->id == 0) {
        boot_screen();
    } else {
        //draw page name
        SSD1306_GotoXY (5,0);
	    SSD1306_Puts(current_page->page_name, &Font_11x18, 1);
        if (current_page->is_menu) {
            if (current_page->n_of_childeren <= 3) {
                static_page();
            } else {
                scrollable_page();
            }
        } else if (current_page->is_test) {

        } else if (current_page->has_variables) {

        } else {
            display_text();
        }
    } 
    

    SSD1306_UpdateScreen(); // update screen
}

static void static_page() {
    //fill menu
    SSD1306_GotoXY (5,20);
    SSD1306_Puts(current_page->childeren[0]->page_name, &Font_7x10, 1);
    SSD1306_GotoXY (5,31);
    if (current_page->n_of_childeren >= 2) {
        SSD1306_Puts(current_page->childeren[1]->page_name, &Font_7x10, 1);
        SSD1306_GotoXY (5,42);
        if (current_page->n_of_childeren >= 3) {
            SSD1306_Puts(current_page->childeren[2]->page_name, &Font_7x10, 1);
            SSD1306_GotoXY (5,53);
        }
    } 
    SSD1306_Puts("Back", &Font_7x10, 1);

    //selected item background
    SSD1306_DrawBitmap(0, 18+11*item_selector, bitmap_item_sel_outline_12, 128, 12, 1); 
}

static void scrollable_page() {
    //TODO add scrollbar
    int back_index = current_page->n_of_childeren;
    //first item
    SSD1306_GotoXY (5,20);
    char* line0 = "Back";
    if (item_selector > 0) {
        line0 = current_page->childeren[item_selector-1]->page_name;
    }
    SSD1306_Puts(line0, &Font_7x10, 1);

    //second item
    SSD1306_GotoXY (5,31);
    SSD1306_DrawBitmap(0, 29, bitmap_item_sel_outline_13, 128, 13, 1);
    char* line1 = "Back";
    if (item_selector != back_index) {
        line1 = current_page->childeren[item_selector]->page_name;
    }
    SSD1306_Puts(line1, &Font_7x10, 1);

    //third item
    SSD1306_GotoXY (5,42);
    char* line2 = "Back";
    if (item_selector + 1 != back_index) {
        line2 = current_page->childeren[(item_selector + 1) % back_index]->page_name;
    }
    SSD1306_Puts(line2, &Font_7x10, 1);

    //fourth item
    SSD1306_GotoXY (5,53);
    char* line3 = "Back";
    if (item_selector + 2 != back_index) {
        line3 = current_page->childeren[(item_selector + 2) % back_index]->page_name;
    }
    SSD1306_Puts(line3, &Font_7x10, 1);
}

static void menu_move_sideways(int direction) {
    if (current_page->parent == NULL) {
        return;
    }

    page_struct *parent = current_page->parent;
    if (parent->n_of_childeren == 1) {
        return;
    }

    //find index of current page
    int index = 0;
    for (int counter = 0; counter < parent->n_of_childeren; counter++) {
        if (parent->childeren[counter]->id == current_page->id) {
            index = counter;
            break;
        }
    }

    current_page = parent->childeren[(index + parent->n_of_childeren + direction) % parent->n_of_childeren];
}

static void display_text() {
    SSD1306_GotoXY (5,20);
    SSD1306_Puts(current_page->line0, &Font_7x10, 1);
    SSD1306_GotoXY (5,31);
    SSD1306_Puts(current_page->line1, &Font_7x10, 1);
    SSD1306_GotoXY (5,42);
    SSD1306_Puts(current_page->line2, &Font_7x10, 1);
    SSD1306_GotoXY (5,53);
    SSD1306_Puts(current_page->line3, &Font_7x10, 1);
}

