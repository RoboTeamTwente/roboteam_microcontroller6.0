#include "voltage_reading.h"

struct page_struct voltage_meter;

void voltage_reading_init(page_struct *parent) {
    pages_set_default_values(&voltage_meter, parent);
    voltage_meter.id = 231;
    page_set_page_name("Voltages", &voltage_meter);
    voltage_meter.has_variables = true;
    add_child_to_parent(&voltage_meter);
}

void voltage_update_page(page_struct *page){
    char temp[MAX_STRING_LENGTH];
    page_put_text_in_line(&page, "Power board", 0);

    sprintf(temp, "Reading: %f", powerVoltage.voltagePowerBoard);
    page_put_text_in_line(&page, temp, 1);

    page_put_text_in_line(&page, "Kicker Capacitor", 2);

    sprintf(temp, "Reading: %u", kickerCapacitorVoltage.voltage);
    page_put_text_in_line(&page, temp, 3);
}