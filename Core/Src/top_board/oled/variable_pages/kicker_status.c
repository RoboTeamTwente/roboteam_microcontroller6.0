#include "kicker_status.h"

struct page_struct kicker_status_page;

void kicker_status_Init(page_struct *parent) {
    pages_set_default_values(&kicker_status_page, parent);
    kicker_status_page.id = 24;
    page_set_page_name("Kicker status", &kicker_status_page);
    kicker_status_page.has_variables = true;
    add_child_to_parent(&kicker_status_page);
}

void kicker_status_Update(page_struct *page) {
    if (kickerStatus.kickerOn) {
        page_put_text_in_line(&page, "On/Off: On", 0);
    } else {
        page_put_text_in_line(&page, "On/Off: Off", 0);
    }

    if (kickerStatus.kickerReady) {
        page_put_text_in_line(&page, "Ready: Yes", 1);
    } else {
        page_put_text_in_line(&page, "Ready: No", 1);
    }

    if (kickerStatus.kickerFault) {
        page_put_text_in_line(&page, "Fault: Yes", 2);
    } else {
        page_put_text_in_line(&page, "Fault: No", 2);
    }
}
