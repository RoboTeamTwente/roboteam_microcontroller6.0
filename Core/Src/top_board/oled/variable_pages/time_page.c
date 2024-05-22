#include "time_page.h"
#include "time.h"

struct page_struct time_page;

void time_page_init(page_struct* parent) {
    pages_set_default_values(&time_page);
    time_page.id = 221;
    strcpy(time_page.page_name, "Robot time");
    time_page.parent = parent;
    time_page.has_variables = true;
    add_child_to_parent(&time_page);
}

void time_page_update(page_struct *page) {
    if (TEST_MODE) {
        strcpy(page->line0, "Time not avail-");
        strcpy(page->line1, "able in test-mode.");
        strcpy(page->line2, "Flip switch 7");
        strcpy(page->line3, "and reboot");
        return;
    }

    char temp[MAX_STRING_LENGTH];
    struct tm *tmp;
    uint64_t time_adjusted = unix_timestamp / 1000;
    tmp = localtime(&time_adjusted);
    char clock[6];
    //Day
    strftime(clock, sizeof(clock), "%d/%m", tmp);
    sprintf(temp, "Date-> %s", clock);
    strcpy(page->line0, temp);
    //Hour:Minute
    strftime(clock, sizeof(clock), "%R", tmp);
    sprintf(temp, "H:M -> %s UTC", clock);
    strcpy(page->line1, temp);
    //Seconds
    strftime(clock, sizeof(clock), "%S", tmp);
    sprintf(temp, "Sec -> %s", clock);
    strcpy(page->line2, temp);
    //Millisecond
    sprintf(temp, "ms  -> %d", unix_timestamp - (time_adjusted * 1000));
    strcpy(page->line3, temp);   
}