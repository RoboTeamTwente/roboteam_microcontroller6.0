/* Description: Top level control interface
 *
 * Instructions:
 * Use the functions in this header to interface with the control code.
 *
*/

#include "stateEstimation.h"
#ifndef CONTROL_CONTROL_H_
#define CONTROL_CONTROL_H_

#include "numtypes.h"

typedef struct ControlRef {
    f32 velRef[2];
    f32 accRef[2];
    f32 yawRef;
    f32 yawRateRef;
    f32 YawAccRef;
} ControlRef;

typedef struct StateInfo {
    f32 visionYaw;					// The yaw for this robot as indicated by vision [rad]
    bool visionAvailable;				// Wether vision data can be used at this point
    f32 xsensAcc[2];					// The acceleration as measured by the IMU in the X and Y directions [m/(s^2)]
    f32 xsensYaw;						// They yaw for this robot as indicated by the IMU [rad]
    f32 rateOfTurn;					// The angular velocity of the robot, according to gyro [rad/s]
    f32 encoders[4];                // The position of each wheel [rad]
    f32 wheelSpeeds[4];				// The speed for each wheel [rad/s]
    f32 dribblerSpeed;				// The measured speed of the dribbler [rad/s]
    f32 dribblerFilteredSpeed;		// The filtered speed of the dribbler [rad/s]
    f32 dribbleSpeedBeforeGotBall;	// The speed of the dribbler before it had a ball [rad/s]
    f32 batteryVoltage;             // The voltage of the battery [V]
} StateInfo;

typedef struct ControlOutput {
    f32 wheel_efforts[4]; // PWM fractions to be applied to the motors
    f32 vel_est[2];
    f32 debug_ports[32];  // Debug poerts for debug purposes
    f32 adaptive_force_limit; // The lowest maximum producable force of all the the motors [N]
} ControlOutput;

/**
 * @brief Initialize the control subsystem.
 *
 */
void control_init();

/**
 * @brief Run the control subsystem for one timestep.
 * @param outputs Motor PWM fractions.
 * @param inputs Sensor values with various degrees of preprocessing applied to them.
 */
void control_step(ControlOutput* const outputs, const StateInfo* const state, const ControlRef* const ref);

/**
 * @brief Runs termination logic for the control subsystem.
 *
 * @note Not currently needed, but will likely be needed in the future.
 */
void control_terminate();

#endif