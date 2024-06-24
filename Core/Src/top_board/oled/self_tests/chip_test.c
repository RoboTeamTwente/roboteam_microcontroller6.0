#include "chip_test.h"
#include "robot.h"

struct page_struct chip_two_ms;
struct page_struct chip_three_five_ms;
struct page_struct chip_four_five_ms;
struct page_struct chip_five_five_ms;
struct page_struct chip_six_five_ms;

static uint32_t chip_test_start_time = 0;
static bool start_on;
static bool start_ready;


void chip_test_initChildren(page_struct *parent) {
    pages_set_default_values(&chip_two_ms, parent);
    chip_two_ms.id = 1321;
    strcpy(chip_two_ms.page_name, "2.0 m/s");
    chip_two_ms.is_test = NON_BLOCKING_TEST;
    add_child_to_parent(&chip_two_ms);

    pages_set_default_values(&chip_three_five_ms, parent);
    chip_three_five_ms.id = 1322;
    strcpy(chip_three_five_ms.page_name, "3.5 m/s");
    chip_three_five_ms.is_test = NON_BLOCKING_TEST;
    add_child_to_parent(&chip_three_five_ms);

    pages_set_default_values(&chip_four_five_ms, parent);
    chip_four_five_ms.id = 1323;
    strcpy(chip_four_five_ms.page_name, "4.5 m/s");
    chip_four_five_ms.is_test = NON_BLOCKING_TEST;
    add_child_to_parent(&chip_four_five_ms);

    pages_set_default_values(&chip_five_five_ms, parent);
    chip_five_five_ms.id = 1324;
    strcpy(chip_five_five_ms.page_name, "5.5 m/s");
    chip_five_five_ms.is_test = NON_BLOCKING_TEST;
    add_child_to_parent(&chip_five_five_ms);

    pages_set_default_values(&chip_six_five_ms, parent);
    chip_six_five_ms.id = 1325;
    strcpy(chip_six_five_ms.page_name, "6.5 m/s");
    chip_six_five_ms.is_test = NON_BLOCKING_TEST;
    add_child_to_parent(&chip_six_five_ms);
}

void chip_shoot_run(float speed, page_struct *page){
    uint32_t current_time = HAL_GetTick();
    if (chip_test_start_time + 1000 < current_time) {
        start_of_test(); // Display that we are running a test
        start_on = kickerStatus.kickerOn;
        start_ready = kickerStatus.kickerReady;
        MCP_Chip chip = {0};
        MCP_ChipPayload payload = {0};
        chip.shootPower = speed;
        encodeMCP_Chip(&payload, &chip);
        MCP_Send_Message(&hcan1, &payload, chipHeader, MCP_KICKER_BOARD);
        chip_test_start_time = current_time;
    } else if (chip_test_start_time + 100 < current_time) {
    
        bool after_on = kickerStatus.kickerOn;
        bool after_ready = kickerStatus.kickerReady;
        end_of_test();

        // clear previously put text but keep displaying page name
        SSD1306_Fill(0);
        SSD1306_GotoXY (5,0);
        SSD1306_Puts(page->page_name, &Font_11x18, 1);
        strcpy(page->line0, "");
        strcpy(page->line1, "");
        strcpy(page->line2, "");
        strcpy(page->line3, "");

        /* Display what happend according to robot */
        if (start_ready && !after_ready) {
            strcpy(page->line0, "CHIP SUCCES!");
        } else {
            strcpy(page->line0, "CHIP FAILED:");
            //reasoning why it failed
            if (start_on && !start_ready) {
                strcpy(page->line1, "CHARGING");
            } else if (!start_on) {
                strcpy(page->line1, "SHOOT_OFF");
            } else if (start_ready && after_ready) {
                strcpy(page->line1, "MCP DOWN?");
            } else {
                strcpy(page->line1, "REASON UNKNOWN");
            }
        }
        
        if (kickerStatus.kickerFault) {
            strcpy(page->line3, "FAULT!!");
        }
        display_text();
        SSD1306_UpdateScreen(); // update screen
    }    

}
