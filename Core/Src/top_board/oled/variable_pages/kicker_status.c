#include "kicker_status.h"

struct page_struct kicker_status_page;

void kicker_status_Init(page_struct *parent) {
    pages_set_default_values(&kicker_status_page);
    kicker_status_page.id = 24;
    strcpy(kicker_status_page.page_name, "Kicker status");
    kicker_status_page.parent = parent;
    kicker_status_page.has_variables = true;
    add_child_to_parent(&kicker_status_page);
}

void kicker_status_Update(page_struct *page) {
    if (kickerStatus.kickerOn) {
        strcpy(page->line0, "On/Off: On");
    } else {
        strcpy(page->line0, "On/Off: Off");
    }

    if (kickerStatus.kickerReady) {
        strcpy(page->line1, "Ready: Yes");
    } else {
        strcpy(page->line1, "Ready: No");
    }

    if (kickerStatus.kickerFault) {
        strcpy(page->line2, "Fault: Yes");
    } else {
        strcpy(page->line2, "Fault: No");
    }
}
