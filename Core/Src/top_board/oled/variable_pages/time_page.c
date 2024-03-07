#include "time_page.h"
#include "time.h"

void time_page_update(page_struct *page) {
    char temp[MAX_STRING_LENGTH];
    struct tm *tmp;
    uint64_t time_adjusted = unix_timestamp / 100;
    tmp = localtime(&time_adjusted);
    char clock[6];
    //Day
    strftime(clock, sizeof(clock), "%d/%m", tmp);
    sprintf(temp, "Date -> %s", clock);
    strcpy(page->line0, temp);
    //Hour:Minute
    strftime(clock, sizeof(clock), "%R", tmp);
    sprintf(temp, "H:M  -> %s", clock);
    strcpy(page->line1, temp);
    //Seconds
    strftime(clock, sizeof(clock), "%S", tmp);
    sprintf(temp, "Sec  -> %s", clock);
    strcpy(page->line2, temp);
    //Millisecond
    sprintf(temp, "ms   -> %d", (unix_timestamp * 10) - (time_adjusted * 1000));
    strcpy(page->line3, temp);
    
}