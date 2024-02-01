
#ifndef UTILS_CONTROL_UTIL_H_
#define UTILS_CONTROL_UTIL_H_

#include <math.h>
#include <stdbool.h>

///////////////////////////////////////////////////// DEFINITIONS

// System
#define TIME_DIFF 0.01F 		// time difference due to 100Hz frequency
#define WIRELESS_RX_COUNT 4000  // count after which wireless should go to timeout after last packet. Multiply with period base (62.5 us) to get to the time in seconds.

// Robot
#define rad_robot 0.081F	// robot radius (m) (from center to wheel contact point) /////// to check with Chris !
#define rad_wheel 0.028F 	// wheel radius (m) // This has been checked with Chris !!!!!

#define FRONT_ANGLE 45		// angle of front wheels (deg)
#define BACK_ANGLE 45		// angle of back wheels (deg)
#define cosFront cosf(FRONT_ANGLE * M_PI/180)
#define sinFront sinf(FRONT_ANGLE * M_PI/180)
#define cosBack cosf(BACK_ANGLE * M_PI/180)
#define sinBack sinf(BACK_ANGLE * M_PI/180)

// Wheels
///////////// CHECK AGAIN !
#define WHEEL_GEAR_RATIO 1.0F 	// gear ratio between motor and wheel
#define PWM_LIMIT MAX_PWM 		// should be equal to MAX_PWM by default
#define MAX_VOLTAGE_50W 24.0	// [V] see datasheet // NEW MOTOR: ECXFL32L 48V (we use the 24V version)
#define SPEED_CONSTANT_50W 291.0 //[(rpm/V] see datasheet ////// unit is rpm/V -> not rad/s/V /// check again 
#define WHEEL_PULSES_PER_ROTATION (float)4*2048 // number of pulses of the encoder per rotation of the motor. New encoder: ENX 32 MILE // should we delete the multiplication by 4?

/// To check !!!
float OMEGAtoPWM; // conversion factor from wheel speed [rad/s] to required PWM on the motor
#define WHEEL_ENCODER_TO_OMEGA (float)2*M_PI/(TIME_DIFF*WHEEL_GEAR_RATIO*WHEEL_PULSES_PER_ROTATION) // conversion factor from number of encoder pulses to wheel speed [rad/s]

struct PIDstruct{
	float kP;			// The gain of the proportional action 
	float kI;			// The gain of the integrating action
	float kD;			// The gain fo the deriving action
	float I;			// The integral of this PID
	float prev_e;		// The previous error
	float timeDiff;		// The time difference due to 100Hz frequency
	float minOutput;	// Not being used at this moment. The minimal output of this PID
	float maxOutput;	// Not being used at this moment. The maximal output of this PID
	float ramp;			// Not being used at this moment. The maximal change of this PID value
	float prev_PID;		// The previous PID value
} static PIDdefault = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, TIME_DIFF, -1000000, 1000000, 1000000, 0};

typedef struct PIDstruct PIDvariables;

#endif /* UTILS_CONTROL_UTIL_H_ */

