#include "OLED_driver.h"

///////////////////////////////////////////////////// PRIVATE FUNCTION DECLARATIONS
static void boot_screen();
static void clear_screen();
static void refresh();

///////////////////////////////////////////////////// VARIABLES
static bool oled_initialized = false;
static page_struct *current_page;
static int item_selector;

///////////////////////////////////////////////////// PUBLIC FUNCTION IMPLEMENTATIONS


void OLED_Init(){
    clear_screen();
    boot_screen();
    current_page = getRootPage();
    item_selector = 0;
    oled_initialized = true;
}

void OLED_DeInit(){
    oled_initialized = false;
}

void OLED_Update(button_id_t button) {
    if(!oled_initialized || button == BUTTON_NONE) {
        return;
    }

    if (current_page->id == 0) {
        current_page = current_page->childeren[0];
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
                    item_selector++;
                }
                break;
            case BUTTON_LEFT:
                break;
            case BUTTON_RIGHT:
                break;
            case BUTTON_OK:
                break;
            default:
                break;
        }
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
    }
    else if (current_page->is_menu) {
        SSD1306_GotoXY (0,0);
	    SSD1306_Puts(current_page->page_name, &Font_11x18, 1);
        int middle_index = item_selector;
        if (middle_index == 0) middle_index = 1;
        if (middle_index > 2 && middle_index == current_page->n_of_childeren - 1) {
            middle_index = current_page->n_of_childeren - 3;
        }
        SSD1306_GotoXY (0,20);
        SSD1306_Puts(current_page->childeren[middle_index-1]->page_name, &Font_7x10, 1);
        if (current_page->n_of_childeren >= 2) {
            SSD1306_GotoXY (0,31);
            SSD1306_Puts(current_page->childeren[middle_index]->page_name, &Font_7x10, 1);
        }
        if (current_page->n_of_childeren >= 3) {
            SSD1306_GotoXY (0,43);
            SSD1306_Puts(current_page->childeren[middle_index + 1]->page_name, &Font_7x10, 1);
        }
    }



    SSD1306_UpdateScreen(); // update screen
}