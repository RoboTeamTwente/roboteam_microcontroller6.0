#ifndef INC_TIM_UTIL_FUNCTIONS_H_
#define INC_TIM_UTIL_FUNCTIONS_H_

#include "main.h"

// structs
typedef struct PWM_struct{
    TIM_HandleTypeDef* TIM;
    uint16_t Channel;
} PWM_struct;

inline void start_PWM(PWM_struct PWM){
    HAL_TIM_Base_Start(PWM.TIM);
    HAL_TIM_PWM_Start(PWM.TIM, PWM.Channel);
}

inline void stop_PWM(PWM_struct PWM){
    HAL_TIM_Base_Stop(PWM.TIM);
    HAL_TIM_PWM_Stop(PWM.TIM, PWM.Channel);
}

inline void set_PWM(PWM_struct PWM, uint32_t Value){
    __HAL_TIM_SET_COMPARE(PWM.TIM , PWM.Channel, Value);
}

inline uint32_t get_PWM(PWM_struct PWM){
    return __HAL_TIM_GET_COMPARE(PWM.TIM , PWM.Channel);
}


#endif /* INC_TIM_UTIL_FUNCTIONS_H_ */