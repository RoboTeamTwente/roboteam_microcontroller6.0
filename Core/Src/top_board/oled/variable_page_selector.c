#include "variable_page_selector.h"

void update_variables(page_struct *page) {
    switch (page->id) {
        case 24:
            kicker_status_Update(page);
            break;
        case 221:
            time_page_update(page);
            break;
        case 222:
            mcp_page_update(page);
            break;
        case 223:
            rem_page_update(page);
            break;
        case 231:
            voltage_update_page(page);
            break;
        case 232:
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
        case 36:
            drain_battery_update_screen(page);
            break;
        default:
            break;
    }
}