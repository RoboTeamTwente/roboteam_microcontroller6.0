#include "voltage_reading.h"

struct page_struct voltage_meter;

void voltage_reading_init(page_struct *parent) {
    pages_set_default_values(&voltage_meter, parent);
    voltage_meter.id = 231;
    strcpy(voltage_meter.page_name, "Voltages");
    voltage_meter.has_variables = true;
    add_child_to_parent(&voltage_meter);
}

void voltage_update_page(page_struct *page){
    char temp[MAX_STRING_LENGTH];
    strcpy(voltage_meter.line0,"Power board");
    sprintf(temp, "Reading: %f", powerVoltage.voltagePowerBoard);
    strcpy(page->line1, temp);
    strcpy(voltage_meter.line2,"Kicker Capacitor");
    sprintf(temp, "Reading: %u", kickerCapacitorVoltage.voltage);
    strcpy(page->line3, temp);
}