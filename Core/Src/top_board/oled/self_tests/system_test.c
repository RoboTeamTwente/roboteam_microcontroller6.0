#include "system_test.h"

bool system_test_running = false;
static uint32_t time_started = 0;
struct page_struct system_test_running_page;

void system_test_init(page_struct *parent) {
    pages_set_default_values(&system_test_running_page);
    system_test_running_page.id = 1511;
    strcpy(system_test_running_page.page_name, "System test");
    strcpy(system_test_running_page.line0,"Robot is off");
    strcpy(system_test_running_page.line1,"the ground");
    strcpy(system_test_running_page.line3,"Kicker!!");
    system_test_running_page.parent = parent;
    system_test_running_page.is_test = NON_BLOCKING_TEST;
    add_child_to_parent(&system_test_running_page);
}
void system_test_run() {
    //test has not started yet
    uint32_t current_time = HAL_GetTick();
    if (!system_test_running && !test_is_finished) {
        start_of_test();
        wheels_Unbrake();
        time_started = current_time;
        system_test_running = true;
    } else if (system_test_running) {
        //let the test run for 10 seconds
        if (current_time > time_started + 10000) {
            wheels_Brake();
            end_of_test();
            system_test_running = false;
        }
    }
    HAL_Delay(1500);
    CAN_Send_Message(KICK_MESSAGE, KICK_CHIP_ID, &hcan1);
}

uint32_t get_system_test_time_started() {
    return time_started;
}

bool get_system_test_running() {
    return system_test_running;
}


