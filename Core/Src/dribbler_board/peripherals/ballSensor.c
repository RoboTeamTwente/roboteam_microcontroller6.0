#include "ballSensor.h"

uint16_t ADC2_buffer[DMA_bufferSize];
uint8_t counter = 0;
bool ballSensor_isWorking = false;
bool IR_State = false;

void ballsensor_init(){
    HAL_TIM_Base_Start_IT(ADC_TIMER);
    HAL_ADC_Start_DMA(BALL_SENSOR_IN, (uint32_t*)ADC2_buffer, DMA_bufferSize);
    ballsensor_test();
}

void ballsensor_deinit(){
    HAL_TIM_Base_Stop(ADC_TIMER);
}

void ballsensor_test(){
    
    ballsensor_setIR_on();
    HAL_Delay(100);
    if(ballsensor_hasBall()){ // if we have a reading that is below the threshold when the IR is on then it means the sensor is not working
        ballSensor_isWorking = false;
        ballsensor_setIR_off();
        return;
    }
    ballSensor_isWorking = true;
}

void ballsensor_setIR_on(){
    IR_State = true;
    set_Pin(IR_LED_pin, true);
}

void ballsensor_setIR_off(){
    IR_State = false;
    set_Pin(IR_LED_pin, false);
}

bool ballsensor_hasBall(){
    return ADC2_buffer[0] < 200 && IR_State;
}

