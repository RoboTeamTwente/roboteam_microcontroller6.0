/* Description: wheel velocity controls
 *
 * Instructions:
 * 1) Initialize the wheels by calling wheels_Init() and encoder_Init()
 * 2) Unbrake the wheels by calling wheels_Unbrake()
 * 3) Set the wheel velocities by calling wheels_SetSpeed() and wheels_set_command_speed
 * 4) Repeatedly call wheels_Update() every 10ms (as dictated by the variable TIME_DIFF) to ensure the wheels reach their speeds
 * ==== instructions below not needed per se. Turning off the robot will do fine ====
 * 5) Stop the robot by calling wheels_Stop()
 * 6) Turn on the brakes by calling wheels_Brake()
 * 7) Deinitialize the wheels by calling wheels_Deinitialize()
 * 
 * Extra functions:
 * 1) encoder_getCounter to get the last measured wheel speeds
 * 2) wheels_DriverStatus returns whether board can communicate with the motor driver
 * 3) wheels_DriverPresent returns whether motor driver has any errors
 * 4) wheels_SetPWM set PWM of the motor, preferably use wheels_SetSpeed()
 * 5) wheels_GetWheelsBraking returns whether the wheels are braking
 * 
 * Notes: 
 *
*/

#ifndef INC_WHEELS_H_
#define INC_WHEELS_H_
#include "main.h"
#include "stm32f7xx_hal.h"
#include <stdlib.h>
#include <stdbool.h>
#include "control_util.h"
#include "REM_RobotSetPIDGains.h"


typedef enum{
	RF,LF,LB,RB
}motor_id_t;

typedef enum{
	MOTOR_OK,
	MOTOR_NORESPONSE,
	MOTOR_ERROR
}Motor_StatusTypeDef;

Motor_StatusTypeDef wheels_Init();
void wheels_DeInit();
void wheels_SetPWM(motor_id_t id, int32_t Value);
Motor_StatusTypeDef wheels_SetSpeed(motor_id_t id, float Value);
void wheels_set_command_speed(const float speeds[4]);
void wheels_Update();
//Enable the brakes
void wheels_Brake();
//Disable the brakes
void wheels_Unbrake();
// Stops the wheels without deinitializing them 
void wheels_Stop();

bool wheels_GetWheelsBraking();

Motor_StatusTypeDef wheels_DriverStatus(motor_id_t motor);
Motor_StatusTypeDef wheels_DriverPresent(motor_id_t motor);

void wheels_SetPIDGains(REM_RobotSetPIDGains* PIDGains);

/* Encoders */
void encoder_Init();
int16_t encoder_GetCounter(motor_id_t id);
void encoder_ResetCounter(motor_id_t id);

#endif /* INC_WHEELS_H_ */
