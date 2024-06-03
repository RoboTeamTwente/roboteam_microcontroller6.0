#include "encoder_page.h"

struct page_struct encoder_values;

void encoder_page_init(page_struct *parent) {
    pages_set_default_values(&encoder_values, parent);
    encoder_values.id = 232;
    strcpy(encoder_values.page_name, "Encoder");
    strcpy(encoder_values.line0, "LF:0");
    strcpy(encoder_values.line1, "RF:0");
    strcpy(encoder_values.line2, "LB:0");
    strcpy(encoder_values.line3, "RB:0");
    encoder_values.has_variables = true;
    add_child_to_parent(&encoder_values);
}

void encoder_page_update(page_struct *page){

    char temp[MAX_STRING_LENGTH];
    sprintf(temp, "LF:%d", encoder_GetCounter(LF));
    strcpy(page->line0, temp);
    sprintf(temp, "RF:%d", encoder_GetCounter(RF));
    strcpy(page->line1, temp);
    sprintf(temp, "LB:%d", encoder_GetCounter(LB));
    strcpy(page->line2, temp);
    sprintf(temp, "RB:%d", encoder_GetCounter(RB));
    strcpy(page->line3, temp);
    
}