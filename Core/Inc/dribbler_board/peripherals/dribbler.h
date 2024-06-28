
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

///////////////////////////////////////////////////// PUBLIC FUNCTION DECLARATIONS

extern uint32_t encoder_value;

#define CURRENT_THRESHOLD 600 // A temporary threshold
#define current_Buffer_Size 10

// Dribbler
#define DRIBBLER_GEAR_RATIO 0.777777778F     // Gear ratio between motor and dribbler
#define DRIBBLER_PULSES_PER_ROTATION 4096.0F // Number of pulses of the encoder per rotation of the motor (see datasheet)
#define DRIBBLER_TIME_DIFF 0.1F              // Given that the dribbler is updated/controlled at 10Hz, delta time is 0.1s
#define DRIBBLER_ENCODER_TO_OMEGA ((2. * M_PI * DRIBBLER_GEAR_RATIO) / (DRIBBLER_TIME_DIFF * DRIBBLER_PULSES_PER_ROTATION)) // Conversion factor from number of encoder pulses to dribbler speed [rad/s]


// Initializes the PIDs / encoders / PWM timers
void dribbler_Init();
// Initializes the motor driver for the PWM
void dribbler_motor_Init();
// The current value we set, limits acceleration
void dribbler_setCurrentLimit(float value);
// Larger current implies we have the ball
uint32_t dribbler_getCurrent();
// If the current is above a certain threshold, it implies we have the ball
bool dribbler_hasBall();
// Denitializes the encoders / PWM timers
void dribbler_DeInit();
// Sets the dribbler speed and makes sure it's within [0,1], if brake is true, the motor will brake if pwm is 0, else it will coast
void dribbler_SetSpeed(float speed, bool brake);
// Returns the latest encoder measurement
uint32_t dribbler_GetEncoderMeasurement();


#endif /* DRIBBLER_DRIBBLER_H_ */
