#include "drain_battery.h"

struct page_struct drain_battery_lowest;
struct page_struct drain_battery_23_0;
struct page_struct drain_battery_23_5;
struct page_struct drain_battery_24_0;
struct page_struct drain_battery_24_5;

bool DRAIN_BATTERY = false;

/**
 * @note 30 < ID < 40
*/
void drain_battery_initChildren(page_struct *parent) {
    pages_set_default_values(&drain_battery_lowest);
    drain_battery_lowest.id = 31;
    strcpy(drain_battery_lowest.page_name, "Lowest doable");
    drain_battery_lowest.parent = parent;
    drain_battery_lowest.is_test = NON_BLOCKING_TEST;
    drain_battery_lowest.has_variables = true;
    add_child_to_parent(&drain_battery_lowest);

    pages_set_default_values(&drain_battery_23_0);
    drain_battery_23_0.id = 32;
    strcpy(drain_battery_23_0.page_name, "23.0V");
    drain_battery_23_0.parent = parent;
    drain_battery_23_0.is_test = NON_BLOCKING_TEST;
    drain_battery_23_0.has_variables = true;
    add_child_to_parent(&drain_battery_23_0);    

    pages_set_default_values(&drain_battery_23_5);
    drain_battery_23_5.id = 33;
    strcpy(drain_battery_23_5.page_name, "23.5V");
    drain_battery_23_5.parent = parent;
    drain_battery_23_5.is_test = NON_BLOCKING_TEST;
    drain_battery_23_5.has_variables = true;
    add_child_to_parent(&drain_battery_23_5);    

    pages_set_default_values(&drain_battery_24_0);
    drain_battery_24_0.id = 34;
    strcpy(drain_battery_24_0.page_name, "24.0V");
    drain_battery_24_0.parent = parent;
    drain_battery_24_0.is_test = NON_BLOCKING_TEST;
    drain_battery_24_0.has_variables = true;
    add_child_to_parent(&drain_battery_24_0);    

    pages_set_default_values(&drain_battery_24_5);
    drain_battery_24_5.id = 35;
    strcpy(drain_battery_24_5.page_name, "24.5V");
    drain_battery_24_5.parent = parent;
    drain_battery_24_5.is_test = NON_BLOCKING_TEST;
    drain_battery_24_5.has_variables = true;
    add_child_to_parent(&drain_battery_24_5);  
}

void drain_battery_run(float target) {
    if (!powerBoard_alive && target > 20.0f) {
        SSD1306_Fill(0);
        SSD1306_GotoXY (5,0);
        SSD1306_Puts("ERROR", &Font_11x18, 1);
        SSD1306_GotoXY (5,20);
        SSD1306_Puts("Sensor is", &Font_7x10, 1);
        SSD1306_GotoXY (5,31);
        SSD1306_Puts("not working.", &Font_7x10, 1);
        SSD1306_GotoXY (5,42);
        SSD1306_Puts("Only \"Lowest", &Font_7x10, 1);
        SSD1306_GotoXY (5,53);
        SSD1306_Puts("doable\" works", &Font_7x10, 1);
        SSD1306_UpdateScreen();
        DRAIN_BATTERY = false;
    } else if (target == 18.0f || target > powerboard_voltage) {
        start_of_test();
        DRAIN_BATTERY = true;
    }
}