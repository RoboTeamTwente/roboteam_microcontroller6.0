#include "send_feedback.h"

/**
 * ID 140 < ID < 150
 */

struct page_struct send_feedback_menu;
struct page_struct send_feedback_on;
struct page_struct send_feedback_off;

void init_sendFeedback(page_struct *parent) {
    pages_set_default_values(&send_feedback_menu, parent);
    page_set_page_name("Send Feedback", &send_feedback_menu);
    send_feedback_menu.id = 141;
    send_feedback_menu.is_menu = true;
    add_child_to_parent(&send_feedback_menu);

    pages_set_default_values(&send_feedback_on, &send_feedback_menu);
    page_set_page_name("On", &send_feedback_on);
    send_feedback_on.id = 142;
    send_feedback_on.is_test = BLOCKING_TEST;
    add_child_to_parent(&send_feedback_on);

    pages_set_default_values(&send_feedback_off, &send_feedback_menu);
    page_set_page_name("Off", &send_feedback_off);
    send_feedback_off.id = 143;
    send_feedback_off.is_test = BLOCKING_TEST;
    add_child_to_parent(&send_feedback_off);
}

void start_sendFeeback() {
    start_of_test();
    send_feedback_passively = true;
    HAL_Delay(500);
    end_of_test();
}

void stop_sendFeedback() {
    start_of_test();
    send_feedback_passively = false;
    HAL_Delay(500);
    end_of_test();
}