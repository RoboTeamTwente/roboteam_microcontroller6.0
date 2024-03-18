#include "system_test.h"

bool system_test_running = false;
static uint32_t time_started = 0;
struct page_struct running_page;
struct page_struct finish_page;

void system_test_init(page_struct *parent) {
    running_page.id = 1511;
    strcpy(running_page.page_name, "System test");
    running_page.parent = parent;
    running_page.n_of_childeren = 0;
    running_page.is_menu = false;
    running_page.is_test = true;
    running_page.has_variables = false;
    add_child_to_parent(&running_page);
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
}

uint32_t get_system_test_time_started() {
    return time_started;
}

bool get_system_test_running() {
    return system_test_running;
}


