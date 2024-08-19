#include "info_menu.h"

struct page_struct communication_menu;
struct page_struct sensor_menu;

/**
 * @brief initialize the pages that are the children of info menu
 * @note constraint for children of info menu: 20 < id < 30 
*/
void info_menu_initChildren(page_struct *parent) {

    pages_set_default_values(&communication_menu, parent);
    communication_menu.id = 22;
    page_set_page_name("Communication", &communication_menu);
    communication_menu.is_menu = true;
    add_child_to_parent(&communication_menu);
    time_page_init(&communication_menu);
    mcp_page_init(&communication_menu);
    rem_page_init(&communication_menu);

    pages_set_default_values(&sensor_menu, parent);
    sensor_menu.id = 23;
    page_set_page_name("Sensors etc.", &sensor_menu);
    sensor_menu.is_menu = true;
    add_child_to_parent(&sensor_menu);
    encoder_page_init(&sensor_menu);
    voltage_reading_init(&sensor_menu);    

    kicker_status_Init(parent);
}