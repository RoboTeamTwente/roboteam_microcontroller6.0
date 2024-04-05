#include "encoder_page.h"

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