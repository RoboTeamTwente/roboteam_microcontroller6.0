#include "info_menu.h"

struct page_struct voltage_meter;

/**
 * @brief initialize the pages that are the children of info menu
 * @note constraint for children of info menu: 20 < id < 30 
*/
void info_menu_initChildren(page_struct *parent) {
    general_info_init(&parent);





    pages_set_default_values(&voltage_meter);
    voltage_meter.id = 25;
    strcpy(voltage_meter.page_name, "PB Voltage");
    strcpy(voltage_meter.line0,"Reading:0");
    voltage_meter.parent = parent;
    voltage_meter.has_variables = true;
    add_child_to_parent(&voltage_meter);
    
}