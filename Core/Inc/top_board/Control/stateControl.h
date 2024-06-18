
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
#define default_P_gain_u 0.0f
#define default_I_gain_u 0.0f
#define default_D_gain_u 0.0f

#define default_P_gain_v 0.0f
#define default_I_gain_v 0.0f
#define default_D_gain_v 0.0f

#define default_P_gain_w 0.0f
#define default_I_gain_w 0.0f
#define default_D_gain_w 0.0f

#define default_P_gain_yaw 26.0f
#define default_I_gain_yaw 5.0f
#define default_D_gain_yaw 0.0f

#define default_P_gain_wheels 2.0f
#define default_I_gain_wheels 0.0f
#define default_D_gain_wheels 0.0f

///////////////////////////////////////////////////// STRUCTS
struct FFstruct{
	// float a[4]; // Sine amplitude
	float b[4]; // Sine frequency
	float c[4]; // Sine phase
	// float d[4]; // Constant offset
	float param1[4];
	float param2[4];
	float param3[4];
	float param4[4];
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
 * If initialised the wheel reference speeds are determined based on the current and reference state of the robot.
 */
void stateControl_Update_Body();

/**
 * Set the new reference values that the robot should achieve.
 * @param _stateGlobalRef The x [m/s], y [m/s] and w [rad/s] speeds and yaw [rad] as instructed by the RobotCommand.
 */
void stateControl_SetRef(float _stateGlobalRef[4], float _stateGlobalRefAcceleration[3]);

/**
 * Get the referenced wheel speeds.
 * 
 * @return float Wheel speed of wheels [rad/s].
 */
float* stateControl_GetWheelRef();

/**
 * Get the referenced wheel speeds.
 * 
 * @return float Wheel speed of a wheel [rad/s].
 */
float stateControl_GetIndividualWheelRef(wheel_names wheel);

/**
 * Get the referenced global body speeds (for yaw - angleControl)
 * 
 * @return float An a global velocity (x, y, w and yaw velocities) to be achieved [m/s]/[rad/s]/[rad]

 */
float stateControl_GetBodyGlobalRef(robot_axes direction);

/**
 * Get the body controller output
 * 
 * @return float The respective body controller output

 */
float stateControl_GetBodyControllerOutput(robot_axes direction);

/**
 * Get the wheel controller output
 * 
 * @return float The respective wheel controller output

 */
float stateControl_GetWheelControllerOutput(wheel_names wheel);

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
 * Retrieves the integral for the provided wheel (1,2,3,4)
 * 
 * @param direction The wheel to be requested
 * @return float    The integral for the requested wheel
 */
float stateControl_GetWheelIntegral(wheel_names wheel);

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
void wheels_SetPIDGains(REM_RobotSetPIDGains* PIDGains);
float voltage2PWM(float wheelVoltage);
void wheels_GetPIDGains(float _gains[3]);

#endif /* DO_STATE_CONTROL_H_ */
