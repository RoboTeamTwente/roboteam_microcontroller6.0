#include "kicker_test.h"
#include "robot.h"

struct page_struct kick_two_ms;
struct page_struct kick_three_five_ms;
struct page_struct kick_four_five_ms;
struct page_struct kick_five_five_ms;
struct page_struct kick_six_five_ms;

static uint32_t kicker_test_start_time = 0;
static bool start_on;
static bool start_ready;

void kicker_test_initChildren(page_struct *parent) {
    pages_set_default_values(&kick_two_ms, parent);
    kick_two_ms.id = 1311;
    strcpy(kick_two_ms.page_name, "2.0 m/s");
    kick_two_ms.is_test = NON_BLOCKING_TEST;
    add_child_to_parent(&kick_two_ms);
    
    pages_set_default_values(&kick_three_five_ms, parent);
    kick_three_five_ms.id = 1312;
    strcpy(kick_three_five_ms.page_name, "3.5 m/s");
    kick_three_five_ms.is_test = NON_BLOCKING_TEST;
    add_child_to_parent(&kick_three_five_ms);

    pages_set_default_values(&kick_four_five_ms, parent);
    kick_four_five_ms.id = 1313;
    strcpy(kick_four_five_ms.page_name, "4.5 m/s");
    kick_four_five_ms.is_test = NON_BLOCKING_TEST;
    add_child_to_parent(&kick_four_five_ms);

    pages_set_default_values(&kick_five_five_ms, parent);
    kick_five_five_ms.id = 1314;
    strcpy(kick_five_five_ms.page_name, "5.5 m/s");
    kick_five_five_ms.is_test = NON_BLOCKING_TEST;
    add_child_to_parent(&kick_five_five_ms);

    pages_set_default_values(&kick_six_five_ms, parent);
    kick_six_five_ms.id = 1315;
    strcpy(kick_six_five_ms.page_name, "6.5 m/s");
    kick_six_five_ms.is_test = NON_BLOCKING_TEST;
    add_child_to_parent(&kick_six_five_ms);
}

void kicker_shoot_run(float speed, page_struct *page){
    uint32_t current_time = HAL_GetTick();
    if (kicker_test_start_time + 1000 < current_time) {
        start_of_test(); // Display that we are running a test
        start_on = kickerStatus.kickerOn;
        start_ready = kickerStatus.kickerReady;
        MCP_Kick kick = {0};
        MCP_KickPayload payload = {0};
        kick.shootPower = speed;
        encodeMCP_Kick(&payload, &kick);
        MCP_Send_Message(&hcan1, &payload, kickHeader, MCP_KICKER_BOARD);
        kicker_test_start_time = current_time;
    } else if (kicker_test_start_time + 100 < current_time) {
    
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
            strcpy(page->line0, "KICK SUCCES!");
        } else {
            strcpy(page->line0, "KICK FAILED:");
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

