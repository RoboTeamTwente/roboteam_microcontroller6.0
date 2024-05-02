#include "voltage_reading.h"

struct page_struct voltage_meter;

void voltage_reading_init(page_struct *parent) {
    pages_set_default_values(&voltage_meter);
    voltage_meter.id = 231;
    strcpy(voltage_meter.page_name, "PB Voltage");
    strcpy(voltage_meter.line0,"Reading:0");
    voltage_meter.parent = parent;
    voltage_meter.has_variables = true;
    add_child_to_parent(&voltage_meter);
}

void voltage_update_page(page_struct *page){
    char temp[MAX_STRING_LENGTH];
    sprintf(temp, "Reading:%f", powerboard_voltage);
    strcpy(page->line0, temp);
}