#include "ballSensor.h"

uint16_t ADC2_buffer[DMA_bufferSize];
uint8_t counter = 0;
bool ballSensor_isWorking = false;

void ballsensor_init(){
    HAL_TIM_Base_Start_IT(ADC_TIMER);
    HAL_ADC_Start_DMA(BALL_SENSOR_IN, (uint32_t*)ADC2_buffer, DMA_bufferSize);
    ballsensor_setIR_on();
}

void ballsensor_deinit(){
    HAL_TIM_Base_Stop(ADC_TIMER);
}

void ballsensor_setIR_on(){
    set_Pin(IR_LED_pin, true);
}

void ballsensor_setIR_off(){
    set_Pin(IR_LED_pin, false);
}

bool ballsesnor_previousState(){
    return ADC2_buffer[1] < 200;
}

bool ballsensor_hasBall(){
    return ADC2_buffer[0] < 200;
}

bool ballsesnor_changeState(){
    return ballsensor_hasBall() != ballsesnor_changeState();
}

