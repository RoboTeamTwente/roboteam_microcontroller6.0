#include "OLED.h"

///////////////////////////////////////////////////// PRIVATE FUNCTION DECLARATIONS
static void boot_screen();
static void clear_screen();


///////////////////////////////////////////////////// VARIABLES
static bool oled_initialized = false;

///////////////////////////////////////////////////// PUBLIC FUNCTION IMPLEMENTATIONS


void OLED_Init(){
    clear_screen();
    boot_screen();
    oled_initialized = true;
}

void OLED_Init(){
    oled_initialized = false;
}

void OLED_Update(button_id_t button) {
    if(!oled_initialized) {
        return;
    }

    switch(button){
        case BUTTON_UP:
            break;
        case BUTTON_DOWN:
            break;
        case BUTTON_LEFT:
            break;
        case BUTTON_RIGHT:
            break;
        default:
            break;
    }
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