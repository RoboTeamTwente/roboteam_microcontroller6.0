#include "dribbler_test.h"

struct page_struct drib_on;
struct page_struct drib_off;

void dribbler_test_InitChildren(page_struct *parent){

    pages_set_default_values(&drib_on);
    drib_on.id = 1411;
    strcpy(drib_on.page_name, "Drib on");
    drib_on.parent = parent;
    drib_on.is_test = BLOCKING_TEST;
    drib_on.has_variables = false;
    add_child_to_parent(&drib_on);

    pages_set_default_values(&drib_off);
    drib_off.id = 1412;
    strcpy(drib_off.page_name, "Drib off");
    drib_off.parent = parent;
    drib_off.is_test = BLOCKING_TEST;
    drib_off.has_variables = false;
    add_child_to_parent(&drib_off);
}
void dribbler_test_run(bool state){

    dribbler_speed = state;
    CAN_Send_Message(DRIBBLER_SPEED, DRIBBLER_ID, &hcan1);

    HAL_Delay(500);
    end_of_test();
}
