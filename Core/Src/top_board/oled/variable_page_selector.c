#include "variable_page_selector.h"

void update_variables(page_struct *page) {
    switch (page->id) {
        case 22:
            time_page_update(page);
            break;
        default:
            break;
    }
}