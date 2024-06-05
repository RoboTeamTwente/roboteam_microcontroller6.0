#include "kicker_self_test_menu.h"

struct page_struct kick_menu;
struct page_struct chip_menu;
struct page_struct charge;
struct page_struct no_charge;

/**
 * @note 130 < ID < 140
*/
void kicker_self_test_menu_initChildren(page_struct *parent) {
    pages_set_default_values(&kick_menu, parent);
    kick_menu.id = 131;
    strcpy(kick_menu.page_name, "Test Kick");
    kick_menu.is_menu = true;
    add_child_to_parent(&kick_menu);
    kicker_test_initChildren(&kick_menu);

    pages_set_default_values(&chip_menu, parent);
    chip_menu.id = 132;
    strcpy(chip_menu.page_name, "Test Chip");
    chip_menu.is_menu = true;
    add_child_to_parent(&chip_menu);
    chip_test_initChildren(&chip_menu);

    pages_set_default_values(&no_charge, parent);
    no_charge.id = 133;
    strcpy(no_charge.page_name, "No Charging!");
    no_charge.is_test = BLOCKING_TEST;
    add_child_to_parent(&no_charge);

    pages_set_default_values(&charge, parent);
    charge.id = 134;
    strcpy(charge.page_name, "Charging!");
    charge.is_test = BLOCKING_TEST;
    add_child_to_parent(&charge);
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
