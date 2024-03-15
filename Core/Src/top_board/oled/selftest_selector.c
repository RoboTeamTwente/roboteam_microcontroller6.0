#include "selftest_selector.h"

void run_test(page_struct *page) {
    if (test_is_finished) {
        return;
    }

    switch (page->id) {
        case 111:
            buzzer_test_run();
            break;
        case 1122:
            wheel_twitch_run();
            break;
        case 1511:
            system_test_run();
            break;
        default:
            break;
    }   
}