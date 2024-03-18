#include "buzzer_test.h"

#include "buzzer.h"

struct page_struct buzzer_test;

void buzzer_test_init(page_struct *parent) {
    pages_set_default_values(&buzzer_test);
    buzzer_test.id = 111;
    strcpy(buzzer_test.page_name, "Buzzer test");
    buzzer_test.parent = parent;
    buzzer_test.is_test = BLOCKING_TEST;
    strcpy(buzzer_test.line0, "Robot is");
    strcpy(buzzer_test.line1, "Rick Rolling you");
    strcpy(buzzer_test.line2, "Press any button");
    strcpy(buzzer_test.line3, "to return when done");
    add_child_to_parent(&buzzer_test);
}

void buzzer_test_run() {
    buzzer_Play_RickRoll();
    HAL_Delay(120000);
}