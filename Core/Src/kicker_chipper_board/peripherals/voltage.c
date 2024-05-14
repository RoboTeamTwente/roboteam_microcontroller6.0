#include "voltage.h"

uint16_t adc_buffer[NR_OF_SAMPLES];
float voltage;

void voltage_Init() {
    HAL_ADCEx_Calibration_Start(&hadc2, ADC_DIFFERENTIAL_ENDED);
    HAL_TIM_Base_Start_IT(TIM_VOLTAGE);
    HAL_ADC_Start_DMA(&hadc2, (uint32_t*) adc_buffer, NR_OF_SAMPLES);
}

void voltage_Read() {
    voltage = -0.2f * (float) adc_buffer[0] + 417;
}

float voltage_Get() {
    if (voltage >= 0.00f) return voltage;
    return 0.00f;
}