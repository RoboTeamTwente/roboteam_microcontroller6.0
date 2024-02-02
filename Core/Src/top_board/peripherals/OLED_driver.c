#include "OLED_driver.h"

///////////////////////////////////////////////////// PRIVATE FUNCTION DECLARATIONS
static void boot_screen();
static void clear_screen();
static void refresh();

///////////////////////////////////////////////////// VARIABLES
static bool oled_initialized = false;
static page_struct *current_page;

///////////////////////////////////////////////////// PUBLIC FUNCTION IMPLEMENTATIONS


void OLED_Init(){
    clear_screen();
    boot_screen();
    current_page = getRootPage();
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
        //current_page = current_page->childeren[0];
    } else {
        switch(button){
            case BUTTON_UP:
                break;
            case BUTTON_DOWN:
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

static void refresh(){
    clear_screen();

    //Set pagename
    char tempString[MAX_STRING_LENGTH];
    sprintf(tempString, "%s", current_page->page_name);
    SSD1306_GotoXY (0,0);
	SSD1306_Puts(tempString, &Font_11x18, 1);

    // if (current_page->is_menu) {
    //     SSD1306_GotoXY (0,20);
    // }



    SSD1306_UpdateScreen(); // update screen
}