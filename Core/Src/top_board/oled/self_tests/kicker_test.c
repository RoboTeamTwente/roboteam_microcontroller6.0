#include "kicker_test.h"
#include "robot.h"

struct page_struct kick_three_five_ms;
struct page_struct kick_four_five_ms;
struct page_struct kick_five_five_ms;
struct page_struct kick_six_five_ms;


void kicker_test_initChildren(page_struct *parent) {
    pages_set_default_values(&kick_three_five_ms, parent);
    kick_three_five_ms.id = 1311;
    strcpy(kick_three_five_ms.page_name, "3.5 m/s");
    kick_three_five_ms.is_test = BLOCKING_TEST;
    kick_three_five_ms.has_variables = false;
    add_child_to_parent(&kick_three_five_ms);

    pages_set_default_values(&kick_four_five_ms, parent);
    kick_four_five_ms.id = 1312;
    strcpy(kick_four_five_ms.page_name, "4.5 m/s");
    kick_four_five_ms.is_test = BLOCKING_TEST;
    kick_four_five_ms.has_variables = false;
    add_child_to_parent(&kick_four_five_ms);

    pages_set_default_values(&kick_five_five_ms, parent);
    kick_five_five_ms.id = 1313;
    strcpy(kick_five_five_ms.page_name, "5.5 m/s");
    kick_five_five_ms.is_test = BLOCKING_TEST;
    kick_five_five_ms.has_variables = false;
    add_child_to_parent(&kick_five_five_ms);

    pages_set_default_values(&kick_six_five_ms, parent);
    kick_six_five_ms.id = 1314;
    strcpy(kick_six_five_ms.page_name, "6.5 m/s");
    kick_six_five_ms.is_test = BLOCKING_TEST;
    kick_six_five_ms.has_variables = false;
    add_child_to_parent(&kick_six_five_ms);
}

void kicker_shoot_run(float speed){
    start_of_test(); // Display that we are running a test
    MCP_Kick kick = {0};
    MCP_KickPayload payload = {0};
    kick.shootPower = speed;
    encodeMCP_Kick(&payload, &kick);
    MCP_Send_Message(&hcan1, &payload, kickHeader, MCP_KICKER_BOARD);
    HAL_Delay(500);
    end_of_test();

}

