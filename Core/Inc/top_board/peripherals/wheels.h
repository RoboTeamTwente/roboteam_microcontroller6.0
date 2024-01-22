/*
 * wheels.h
 *
 *  Created on: Dec 26, 2023
 *      Author: Csongor
 */

#ifndef INC_WHEELS_H_
#define INC_WHEELS_H_
#include "main.h"
#include "stm32f7xx_hal.h"
#include <stdlib.h>
#include <stdbool.h>


typedef enum{
	RF,LF,RB,LB
}motor_id_t;

typedef enum{
	MOTOR_OK,
	MOTOR_NORESPONSE,
	MOTOR_ERROR
}Motor_StatusTypeDef;

Motor_StatusTypeDef wheels_Init();
Motor_StatusTypeDef wheels_DriverStatus(motor_id_t motor);
Motor_StatusTypeDef wheels_DriverPresent(motor_id_t motor);
//Enable the brakes
void wheels_Brake();
//Disable the brakes
void wheels_Unbrake();
// Stops the wheels without deinitializing them 
void wheels_Stop();
Motor_StatusTypeDef wheels_DeInit();
Motor_StatusTypeDef wheels_SetPWM(motor_id_t id, int32_t Value);
Motor_StatusTypeDef wheels_Set(motor_id_t id, float Value);


/* Encoders */
Motor_StatusTypeDef encoder_Init();
int16_t encoder_GetCounter(motor_id_t id);
Motor_StatusTypeDef encoder_ResetCounter(motor_id_t id);

#endif /* INC_WHEELS_H_ */
