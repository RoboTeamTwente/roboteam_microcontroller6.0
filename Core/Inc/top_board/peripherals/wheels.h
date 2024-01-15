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
	RF,RB,LB,LF
}motor_id_t;

typedef enum{
	MOTOR_OK,
	MOTOR_NORESPONSE,
	MOTOR_ERROR
}Motor_StatusTypeDef;

Motor_StatusTypeDef Motor_Init();
Motor_StatusTypeDef Motor_DriverStatus(motor_id_t motor);
Motor_StatusTypeDef Motor_DriverPresent(motor_id_t motor);
Motor_StatusTypeDef Motor_WheelsBrake(bool BrakeStatus);
Motor_StatusTypeDef wheels_Init();
Motor_StatusTypeDef wheels_DeInit();
Motor_StatusTypeDef Motor_SetPWM(motor_id_t id, int32_t Value);
Motor_StatusTypeDef Motor_Set(motor_id_t id, float Value);


/* Encoders */
Motor_StatusTypeDef Encoder_Init();
int16_t Encoder_GetCounter(motor_id_t id);
Motor_StatusTypeDef Encoder_ResetCounter(motor_id_t id);

#endif /* INC_WHEELS_H_ */
