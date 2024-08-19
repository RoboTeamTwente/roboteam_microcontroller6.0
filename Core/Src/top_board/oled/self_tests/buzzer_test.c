#include "buzzer_test.h"

#include "buzzer.h"

struct page_struct buzzer_test;

void buzzer_test_init(page_struct *parent) {
    pages_set_default_values(&buzzer_test, parent);
    buzzer_test.id = 111;
    page_set_page_name("Buzzer test", &buzzer_test);
    buzzer_test.is_test = BLOCKING_TEST;
    page_put_text_in_line(&buzzer_test, "Robot is", 0);
    page_put_text_in_line(&buzzer_test, "Rick Rolling you", 1);
    add_child_to_parent(&buzzer_test);
}

void buzzer_test_run() {
    buzzer_Play_RickRoll();
    HAL_Delay(120000);
    end_of_test();
}