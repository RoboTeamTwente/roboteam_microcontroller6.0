#include "ballSensor.h"

uint16_t ADC2_buffer[DMA_bufferSize];

void ballsensor_init(){
    HAL_TIM_Base_Start(&htim6);
    HAL_ADC_Start_DMA(&hadc2, (uint32_t*)ADC2_buffer, DMA_bufferSize);
}

void ballsensor_deinit(){
    HAL_TIM_Base_Stop(&htim6);
}

void ballsensor_setIR_on(){
    set_Pin(IR_LED_pin, true);
}

void ballsensor_setIR_off(){
    set_Pin(IR_LED_pin, false);
}

bool ballsensor_hasBall(){
    return (ADC2_buffer[0] < 1000);
}

