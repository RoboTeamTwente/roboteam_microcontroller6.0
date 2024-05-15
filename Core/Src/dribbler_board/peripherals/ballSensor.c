#include "ballSensor.h"

uint16_t ADC2_buffer[DMA_bufferSize];

void ballsensor_init(){
    HAL_TIM_Base_Start(DMA_TIMER);
    HAL_ADC_Start_DMA(BALL_SENSOR_IN, (uint32_t*)ADC2_buffer, DMA_bufferSize);
    ballsensor_setIR_on();
}

void ballsensor_deinit(){
    HAL_TIM_Base_Stop(DMA_TIMER);
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

