#include "selftest_selector.h"

void run_test(page_struct *page) {
    switch (page->id) {
        case 111:
            buzzer_test_run();
            break;
        case 1122:
            wheel_twitch_run();
            break;
        default:
            break;
    }   
}