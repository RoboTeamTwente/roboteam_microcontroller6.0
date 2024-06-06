#include "dribbler_test.h"

struct page_struct drib_on;
struct page_struct drib_off;

void dribbler_test_InitChildren(page_struct *parent){

    pages_set_default_values(&drib_on, parent);
    drib_on.id = 1411;
    strcpy(drib_on.page_name, "Drib on");
    drib_on.is_test = BLOCKING_TEST;
    drib_on.has_variables = false;
    add_child_to_parent(&drib_on);

    pages_set_default_values(&drib_off, parent);
    drib_off.id = 1412;
    strcpy(drib_off.page_name, "Drib off");
    drib_off.is_test = BLOCKING_TEST;
    drib_off.has_variables = false;
    add_child_to_parent(&drib_off);
}
void dribbler_test_run(bool state){
    start_of_test();
    MCP_DribblerCommand dribCommand = {0};
    MCP_DribblerCommandPayload dcp = {0};
    dribCommand.dribblerOn = state;
    encodeMCP_DribblerCommand(&dcp, &dribCommand);
    MCP_Send_Message(&hcan1, &dcp, dribblerCommandHeader, MCP_DRIBBLER_BOARD);

    HAL_Delay(500);
    end_of_test();
}
