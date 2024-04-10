
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

#include "main.h"
#include "tim_util.h"
#include <math.h>
#include "control_util.h"
#include "logging.h"

///////////////////////////////////////////////////// PUBLIC FUNCTION DECLARATIONS

uint32_t set_speed;

// Initializes the PIDs / encoders / PWM timers
void dribbler_Init();
// Denitializes the encoders / PWM timers
void dribbler_DeInit();
// Sets the dribbler speed and makes sure it's within [0,1]
void dribbler_SetSpeed(float speed);
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
// Returns the latest encoder measurement
uint32_t dribbler_GetEncoderMeasurement();

#endif /* DRIBBLER_DRIBBLER_H_ */