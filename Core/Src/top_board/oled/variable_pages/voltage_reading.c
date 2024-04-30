#include "voltage_reading.h"

void voltage_update_page(page_struct *page){
    char temp[MAX_STRING_LENGTH];
    sprintf(temp, "Reading:%f", powerVoltage.voltagePowerBoard);
    strcpy(page->line0, temp);
}