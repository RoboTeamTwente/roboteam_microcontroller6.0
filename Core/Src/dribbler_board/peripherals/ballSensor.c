#include "ballSensor.h"

uint16_t ADC2_buffer[DMA_bufferSize];
uint8_t counter = 0;
bool ballSensor_isWorking = false;

void ballsensor_init(){
    HAL_TIM_Base_Start_IT(ADC_TIMER);
    HAL_ADC_Start_DMA(BALL_SENSOR_IN, (uint32_t*)ADC2_buffer, DMA_bufferSize);

    HAL_TIM_PWM_Start(PWM_IR_PIN.TIM, PWM_IR_PIN.Channel); // Start PWM for the IR
    set_PWM(&PWM_IR_PIN, 500); // Set it to a duty cycle of 50%, such that it's blinking every other 1khz (0.001s)

    ballsensor_test();
}

void ballsensor_deinit(){
    HAL_TIM_Base_Stop(ADC_TIMER);
    set_PWM(&PWM_IR_PIN, 0);
    HAL_TIM_PWM_Stop(PWM_IR_PIN.TIM, PWM_IR_PIN.Channel);
}

void ballsensor_test(){
    HAL_Delay(100);
    if(ballsensor_hasBall()){ // if we have a reading that is below the threshold when the IR is on then it means the sensor is not working
        ballSensor_isWorking = false;
        ballsensor_deinit();
        return;
    }
    ballSensor_isWorking = true;
}

bool ballsensor_hasBall(){
    return ADC2_buffer[0] < 200;
}

