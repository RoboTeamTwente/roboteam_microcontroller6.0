#include "time_page.h"
#include "time.h"

struct page_struct time_page;

void time_page_init(page_struct* parent) {
    pages_set_default_values(&time_page, parent);
    time_page.id = 221;
    page_set_page_name("Robot time", &time_page);
    time_page.has_variables = true;
    add_child_to_parent(&time_page);
}

void time_page_update(page_struct *page) {
    if (TEST_MODE) {
        page_put_text_in_line(page, "Time not avail-", 0);
        page_put_text_in_line(page, "able in test-mode.", 1);
        page_put_text_in_line(page, "Flip switch 7", 2);
        page_put_text_in_line(page, "and reboot", 3);
        return;
    }

    char temp[MAX_STRING_LENGTH];
    struct tm *tmp;
    uint64_t time_adjusted = unix_timestamp / 1000;
    tmp = localtime(time_adjusted);
    char clock[6];
    //Day
    strftime(clock, sizeof(clock), "%d/%m", tmp);
    sprintf(temp, "Date-> %s", clock);
    page_put_text_in_line(page, temp, 0);
    //Hour:Minute
    strftime(clock, sizeof(clock), "%R", tmp);
    sprintf(temp, "H:M -> %s UTC", clock);
    page_put_text_in_line(page, temp, 1);
    //Seconds
    strftime(clock, sizeof(clock), "%S", tmp);
    sprintf(temp, "Sec -> %s", clock);
    page_put_text_in_line(page, temp, 2);
    //Millisecond
    sprintf(temp, "ms  -> %d", unix_timestamp - (time_adjusted * 1000));
    page_put_text_in_line(page, temp, 3);
}