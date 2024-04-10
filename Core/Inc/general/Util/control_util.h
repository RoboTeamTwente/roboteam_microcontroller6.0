
#ifndef UTILS_CONTROL_UTIL_H_
#define UTILS_CONTROL_UTIL_H_

#include <math.h>
#include <stdbool.h>

///////////////////////////////////////////////////// DEFINITIONS

// System
#define TIME_DIFF 0.01F 		// time difference due to 100Hz frequency
#define WIRELESS_RX_COUNT 4000  // count after which wireless should go to timeout after last packet. Multiply with period base (62.5 us) to get to the time in seconds.

// Robot
#define rad_robot 0.0804F	// robot radius (m) (from center to wheel contact point)
#define rad_wheel 0.0274F 	// wheel radius (m)

#define FRONT_ANGLE 30.0F		// angle of front wheels (deg)
#define BACK_ANGLE 45.0F		// angle of back wheels (deg)
#define cosFront cosf(FRONT_ANGLE * M_PI/180)
#define sinFront sinf(FRONT_ANGLE * M_PI/180)
#define cosBack cosf(BACK_ANGLE * M_PI/180)
#define sinBack sinf(BACK_ANGLE * M_PI/180)

// Wheels
#define PWM_CUTOFF 200.0F 		// arbitrary threshold to avoid motor shutdown /// where does that number come from?
#define WHEEL_GEAR_RATIO 1.0F 	// gear ratio between motor and wheel
#define MAX_PWM_MOTOR_DRIVER 1.0F // MAX_PWM is 6000 but the new PWM range sent to the motor driver is between -1 and 1. 
#define MAX_VOLTAGE 24.0F	// [V] see datasheet // NEW MOTOR: ECXFL32L 48V (we use the 24V version)
float SPEED_CONSTANT; 	
#define SPEED_CONSTANT_MOTOR 291.0F //[(rpm/V] see datasheet // translation from rpm/V to rad/s/V is done later.
#define WHEEL_PULSES_PER_ROTATION (float)4*2048 // number of pulses of the encoder per rotation of the motor. New encoder: ENX 32 MILE // Multiplication by 4 is unsure but datahseet from Maxon is dfferent than some sources.

float OMEGAtoPWM; // conversion factor from wheel speed [rad/s] to required PWM on the motor
#define WHEEL_ENCODER_TO_OMEGA (float)2*M_PI/(TIME_DIFF*WHEEL_GEAR_RATIO*WHEEL_PULSES_PER_ROTATION) // conversion factor from number of encoder pulses to wheel speed [rad/s]

// Dribbler
#define DRIBBLER_GEAR_RATIO 0.777777778F     // Gear ratio between motor and dribbler
#define DRIBBLER_PULSES_PER_ROTATION 4096.0F // Number of pulses of the encoder per rotation of the motor (see datasheet)
#define DRIBBLER_TIME_DIFF 0.1F              // Given that the dribbler is updated/controlled at 10Hz, delta time is 0.1s
#define DRIBBLER_ENCODER_TO_OMEGA ((2. * M_PI * DRIBBLER_GEAR_RATIO) / (DRIBBLER_TIME_DIFF * DRIBBLER_PULSES_PER_ROTATION)) // Conversion factor from number of encoder pulses to dribbler speed [rad/s]

// Control 
// To check !!!
#define YAW_MARGIN (0.5F/180.0F)*(float)M_PI 	// margin at which the I-value of the PID is reset to 0
float WHEEL_REF_LIMIT; 							// [rad/s] Limit the maximum wheel reference to leave room for the wheels PID
#define WHEEL_REF_LIMIT_PWM 2200 				// [pwm] /// where does that come from??

///////////////////////////////////////////////////// STRUCTS

/*
* @brief The axis on which a robot is being controlled.
* 
* @note The x, y and u, v velocities can technically be used interchangeably. 
*	However, in order to stick to the conventions one should use x and y when
*   they refer to the global frame and u and v for the local frame.
*/
typedef enum {
	vel_x = 0,		// The global velocity in the sideways direction
	vel_y = 1,		// The global velocity in the forward/backward direction
	vel_w = 2,		// The angular velocity
	vel_u = 0,      // The local velocity in the sideways direction
	vel_v = 1,      // The local velocity in the forward/backward direction
	yaw = 3,		// The angle
}robot_axes;

typedef enum {
	wheels_RF,	// The right front wheel
	wheels_LF,	// The left front wheel
	wheels_LB,	// The left back wheel
	wheels_RB,	// The right back wheel
}wheel_names;

typedef enum {
	off,		// The PID controller is inactive
	setup,		// Not used at this moment
	on,			// The PID controller is active
	turning,	// Not used at this moment
	idle		// Not used at this moment
}PID_states;// keeps track of the state of the system

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

///////////////////////////////////////////////////// FUNCTIONS
/**
 * Initializes motor wattage dependent constants
 */
void control_util_Init();

/**
 * Initializes the PID values.
 * 
 * Loads the constants into the struct and sets up the default PID parameters.
 */
void initPID(PIDvariables* PID, float kP, float kI, float kD);

//clamps the input
//static float clamp(float input, float min, float max){
//	if (input<min){
//		return min;
//	} else if (input>max) {
//		return max;
//	} else {
//		return input;
//	}
//}

//limits the change in PID value
//static float ramp(float new_PID, float ramp, float prev_PID){
//	if (new_PID-prev_PID>ramp){
//		return (prev_PID+ramp);
//	} else if (new_PID-prev_PID<-ramp){
//		return (prev_PID-ramp);
//	} else {
//		return new_PID;
//	}
//}

//PID control, inline to not have multiple implementation error
float PID(float err, PIDvariables* K);

//Scales the angle to the range Pi to -Pi in radians
float constrainAngle(float x);

#endif /* UTILS_CONTROL_UTIL_H_ */