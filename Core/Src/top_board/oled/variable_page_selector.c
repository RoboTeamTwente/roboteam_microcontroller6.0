#include "variable_page_selector.h"

void update_variables(page_struct *page) {
    switch (page->id) {
        case 22:
            time_page_update(page);
            break;
        case 23:
            mcp_page_update(page);
            break;
        case 24:
            encoder_page_update(page);
            break;
        case 31:
            drain_battery_update_screen(page);
            break;
        case 32:
            drain_battery_update_screen(page);
            break;
        case 33:
            drain_battery_update_screen(page);
            break;
        case 34:
            drain_battery_update_screen(page);
            break;
        case 35:
            drain_battery_update_screen(page);
            break;
        default:
            break;
    }
}