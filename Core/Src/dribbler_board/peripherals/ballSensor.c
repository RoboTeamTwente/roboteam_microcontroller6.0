#include "ballSensor.h"

uint16_t ADC2_buffer[DMA_bufferSize];
uint8_t counter = 0;
bool ballSensor_isWorking = false;
bool IR_State = false;


uint16_t ADC2_Avg_Buffer[AvgBufferSize];
uint32_t ADC2_Avg_counter = 0;
uint32_t ADC2_Avg = 0;

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
    return ADC2_Avg < 200 && IR_State;
}


void ballsensor_DetectBall(){
    
    ADC2_Avg_Buffer[ADC2_Avg_counter % AvgBufferSize] = ADC2_buffer[0]; //ADC2_buffer[0] is the value of the ADC reading

    uint32_t ADC2_Avg_sum = 0;
    for (int i = 0; i < AvgBufferSize; i++){
        ADC2_Avg_sum += ADC2_Avg_Buffer[i];
    }
    ADC2_Avg = ADC2_Avg_sum / AvgBufferSize;

    ADC2_Avg_counter++;
}

