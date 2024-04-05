
/* Description: State control
 *
 * Instructions:
 * 1) Feedforwards the expected desired wheel stateControl based on the reference stateControl
 * 2) Adds a PID feedback to that signal based on the actual stateControl
 *
 * Extra functions:
 *
 * Notes:
 *
*/

#ifndef DO_stateControl_H_
#define DO_stateControl_H_

#include "control_util.h"
#include "gpio_util.h"
#include "tim_util.h"
#include "REM_RobotSetPIDGains.h"
#include "wheels.h"
#include <math.h>

// Set default PID values
#define default_P_gain_u 0.2f
#define default_I_gain_u 0.0f
#define default_D_gain_u 0.0f

#define default_P_gain_v 0.3f
#define default_I_gain_v 0.0f
#define default_D_gain_v 0.0f

#define default_P_gain_w 0.25f
#define default_I_gain_w 5.0f
#define default_D_gain_w 0.0f

#define default_P_gain_yaw 20.0f
#define default_I_gain_yaw 5.0f
#define default_D_gain_yaw 0.0f

#define default_P_gain_wheels 2.0f
#define default_I_gain_wheels 0.0f
#define default_D_gain_wheels 0.0f

///////////////////////////////////////////////////// STRUCTS
struct FFstruct{
	float a[4]; // Sine amplitude
	float b[4]; // Sine frequency
	float c[4]; // Sine phase
	float d[4]; // Constant offset
	float rotation_feedforward_value[4]; // d equivalent for pure rotation
	float identified_damping;
	float vw_max_round_to_rotational_scaling; // Factor to determine when you switch to rotational ff gains
};

typedef struct FFstruct FFparameters;

///////////////////////////////////////////////////// PUBLIC FUNCTION DECLARATIONS

/**
 * Initializes the PID controllers and the velocity coupling matrix, D
 */
int stateControl_Init();

/**
 * Disable the PID controllers
 */
int stateControl_DeInit();

/**
 * If initialised the wheel reference wheels speeds are determined based on the current and reference state of the robot.
 */
void stateControl_Update();

/**
 * Set the new reference values that the robot should achieve.
 * @param _stateGlobalRef The x [m/s], y [m/s] and w [rad/s] speeds and yaw [rad] as instructed by the RobotCommand.
 */
void stateControl_SetRef(float _stateGlobalRef[4]);

/**
 * Get the referenced wheel speeds.
 * 
 * @return float* An array with the wheel speeds [rad/s].
 */
float* stateControl_GetWheelRef();

/**
 * Get the referenced global body speeds (for yaw - angleControl)
 * 
 * @return float* An array with the global x, y, w and yaw velocities to be achieved [m/s]

 */
float* stateControl_GetBodyGlobalRef();

/**
 * Set the current state as the estimated state as calculated by stateEstimation
 * 
 * @param _stateLocal The u [m/s], v [m/s] and w [rad/s] speeds and yaw [rad] from stateEstimation
 */
void stateControl_SetState(float _stateLocal[4]);

/**
 * Retrieve the latest PID gains for u, v, w and yaw.
 * 
 * @param gainsLocal The struct that will receive the new PID gains.
 */
void stateControl_GetPIDGains(PIDvariables gainsLocal[4]);

/**
 * Retrieves the integral for the provided direction (u,v,w or yaw)
 * 
 * @param direction The direction to be requested
 * @return float    The integral for the requested direction
 */
float stateControl_GetIntegral(robot_axes direction);

/**
 * Switch between angular velocity or absolute angle.
 * 
 * @param angularControl If set to true, we use the absolute angle otherwise we use angular velocity.
 */
void stateControl_useAbsoluteAngle(bool angularControl);

/**
 * Updates the PID gains with new values.
 * 
 * @param pidConfig The kP kI kD values for each direction.
 */
void stateControl_SetPIDGains(REM_RobotSetPIDGains* pidConfig);

/**
 * Reset the integral used for the angle.
 */
void stateControl_ResetAngleI();

/**
 * Resets the entire PID calculation for the angle.
 */
void stateControl_ResetPID();

void wheels_Update();
void wheels_set_command_speed(const float speeds[4]); // Stores the commanded wheel speeds, in rad/s, to be used in the next wheels_Update() call
void wheels_GetMeasuredSpeeds(float speeds[4]); // Get the last measured wheel speeds in rad/s
void wheels_SetPIDGains(REM_RobotSetPIDGains* PIDGains);

#endif /* DO_STATE_CONTROL_H_ */
