
/* Description: Makes the dribbler spin
 *
 * Instructions:
 * 1) set speed (0(off)-1(max))
 *
 * Extra functions:
 *
 * Notes:
 *
*/

#ifndef DRIBBLER_DRIBBLER_H_
#define DRIBBLER_DRIBBLER_H_

#include "tim_util.h"
#include "AC_DC_util.h"
#include "main.h"
#include <math.h>
#include "control_util.h"

///////////////////////////////////////////////////// PUBLIC FUNCTION DECLARATIONS

extern uint32_t encoder_value;

#define volt_Start 2000
#define CURRENT_THRESHOLD 600
#define current_Buffer_Size 10

// Initializes the PIDs / encoders / PWM timers
void dribbler_Init();
// Initializes the motor driver for the PWM
void dribbler_motor_Init();
// The voltage value we set, limits acceleration
void dribbler_setVoltage(uint16_t value);
// Larger current implies we have the ball
uint32_t dribbler_getCurrent();
// If the current is above a certain threshold, it implies we have the ball
bool dribbler_hasBall();
// Denitializes the encoders / PWM timers
void dribbler_DeInit();
// Sets the dribbler speed and makes sure it's within [0,1]
void dribbler_SetSpeed(float speed);
// Returns the latest encoder measurement
uint32_t dribbler_GetEncoderMeasurement();



// Updates the dribbler towards the commanded dribbler speed using the encoder and a PID controller.
void dribbler_Update();
// Get the last measured dribbler speeds in rad/s
float dribbler_GetMeasuredSpeeds();
// Get the filtered dribbler speeds in rad/s
float dribbler_GetFilteredSpeeds();
// Returns the delayed speed of the moving average filter at the time it got the ball
float dribbler_GetSpeedBeforeGotBall();
// Calculates whether the dribbler has the ball or not
void dribbler_CalculateHasBall();
// Returns true if the dribbler has the ball
bool dribbler_GetHasBall();
// Returns false if we haven't sent the message of the dribbler state
bool dribbler_ChangeInState();
// Sets the value of the message boolean
void dribbler_set_State(bool state);


#endif /* DRIBBLER_DRIBBLER_H_ */
