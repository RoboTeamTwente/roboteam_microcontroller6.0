#include "encoder_page.h"

struct page_struct encoder_values;

void encoder_page_init(page_struct *parent) {
    pages_set_default_values(&encoder_values, parent);
    encoder_values.id = 232;
    page_set_page_name("Wheel Encoders", &encoder_values);
    page_put_text_in_line(&encoder_values, "LF: 0", 0);
    page_put_text_in_line(&encoder_values, "RF: 0", 1);
    page_put_text_in_line(&encoder_values, "LB: 0", 2);
    page_put_text_in_line(&encoder_values, "RB: 0", 3);
    encoder_values.has_variables = true;
    add_child_to_parent(&encoder_values);
}

void encoder_page_update(page_struct *page){

    char temp[MAX_STRING_LENGTH];
    sprintf(temp, "LF:%d", encoder_GetCounter(LF));
    page_put_text_in_line(&encoder_values, temp, 0);

    sprintf(temp, "RF:%d", encoder_GetCounter(RF));
    page_put_text_in_line(&encoder_values, temp, 1);

    sprintf(temp, "LB:%d", encoder_GetCounter(LB));
    page_put_text_in_line(&encoder_values, temp, 2);

    sprintf(temp, "RB:%d", encoder_GetCounter(RB));
    page_put_text_in_line(&encoder_values, temp, 3);
}