#include "kicker_test.h"
#include "robot.h"

struct page_struct one_five_ms;
struct page_struct no_charge;
struct page_struct charge;
struct page_struct three_five_ms;
struct page_struct four_five_ms;
struct page_struct six_five_ms;


void kicker_test_initChildren(page_struct *parent) {

    // pages_set_default_values(&one_five_ms);
    // one_five_ms.id = 1311;
    // strcpy(one_five_ms.page_name, "1.5 m/s");
    // one_five_ms.parent = parent;
    // one_five_ms.is_test = BLOCKING_TEST;
    // one_five_ms.has_variables = false;
    // add_child_to_parent(&one_five_ms);

    pages_set_default_values(&three_five_ms);
    three_five_ms.id = 1312;
    strcpy(three_five_ms.page_name, "3.5 m/s");
    three_five_ms.parent = parent;
    three_five_ms.is_test = BLOCKING_TEST;
    three_five_ms.has_variables = false;
    add_child_to_parent(&three_five_ms);

    pages_set_default_values(&one_five_ms);
    four_five_ms.id = 1313;
    strcpy(four_five_ms.page_name, "4.5 m/s");
    four_five_ms.parent = parent;
    four_five_ms.is_test = BLOCKING_TEST;
    four_five_ms.has_variables = false;
    add_child_to_parent(&four_five_ms);

    pages_set_default_values(&six_five_ms);
    six_five_ms.id = 1314;
    strcpy(six_five_ms.page_name, "6.5 m/s");
    six_five_ms.parent = parent;
    six_five_ms.is_test = BLOCKING_TEST;
    six_five_ms.has_variables = false;
    add_child_to_parent(&six_five_ms);

    pages_set_default_values(&no_charge);
    no_charge.id = 1315;
    strcpy(no_charge.page_name, "No Charging!");
    no_charge.parent = parent;
    no_charge.is_test = BLOCKING_TEST;
    no_charge.has_variables = false;
    add_child_to_parent(&no_charge);

    pages_set_default_values(&charge);
    charge.id = 1316;
    strcpy(charge.page_name, "Charging!");
    charge.parent = parent;
    charge.is_test = BLOCKING_TEST;
    charge.has_variables = false;
    add_child_to_parent(&charge);
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

void kicker_charge() {
    MCP_KickerCharge kc = {0};
    MCP_KickerChargePayload kcp = {0};
    encodeMCP_KickerCharge(&kcp, &kc);
    MCP_Send_Message(&hcan1, &kcp, kickerChargeHeader, MCP_KICKER_BOARD);
    HAL_Delay(500);
    end_of_test();
}

void kicker_stopCharge() {
    MCP_KickerStopCharge ksc = {0};
    MCP_KickerStopChargePayload kscp = {0};
    encodeMCP_KickerStopCharge(&kscp, &ksc);
    MCP_Send_Message(&hcan1, &kscp, kickerStopChargeHeader, MCP_KICKER_BOARD);
    HAL_Delay(500);
    end_of_test();
}
