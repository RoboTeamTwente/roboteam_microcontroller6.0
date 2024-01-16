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

Motor_StatusTypeDef motor_Init();
Motor_StatusTypeDef motor_DriverStatus(motor_id_t motor);
Motor_StatusTypeDef motor_DriverPresent(motor_id_t motor);
Motor_StatusTypeDef motor_WheelsBrake(bool BrakeStatus);
Motor_StatusTypeDef wheels_Init();
Motor_StatusTypeDef wheels_DeInit();
Motor_StatusTypeDef motor_SetPWM(motor_id_t id, int32_t Value);
Motor_StatusTypeDef motor_Set(motor_id_t id, float Value);


/* Encoders */
Motor_StatusTypeDef encoder_Init();
int16_t encoder_GetCounter(motor_id_t id);
Motor_StatusTypeDef encoder_ResetCounter(motor_id_t id);

#endif /* INC_WHEELS_H_ */
