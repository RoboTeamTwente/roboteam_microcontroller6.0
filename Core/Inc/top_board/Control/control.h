/* Description: Top level control interface
 *
 * Instructions:
 * Use the functions in this header to interface with the control code.
 *
*/

#include "stateEstimation.h"
#ifndef CONTROL_CONTROL_H_
#define CONTROL_CONTROL_H_

typedef struct ControlRef {
    float velRef[2];
    float accRef[2];
    float yawRef;
    float yawRateRef;
    float YawAccRef;
} ControlRef;

typedef struct StateInfo {
    float visionYaw;					// The yaw for this robot as indicated by vision [rad]
    bool visionAvailable;				// Wether vision data can be used at this point
    float xsensAcc[2];					// The acceleration as measured by the IMU in the X and Y directions [m/(s^2)]
    float xsensYaw;						// They yaw for this robot as indicated by the IMU [rad]
    float rateOfTurn;					// The angular velocity of the robot, according to gyro [rad/s]
    float wheelSpeeds[4];				// The speed for each wheel [rad/s]
    float dribblerSpeed;				// The measured speed of the dribbler [rad/s]
    float dribblerFilteredSpeed;		// The filtered speed of the dribbler [rad/s]
    float dribbleSpeedBeforeGotBall;	// The speed of the dribbler before it had a ball [rad/s]
} StateInfo;

typedef struct ControlOutput {
    float wheel_efforts[4]; // PWM fractions to be applied to the motors
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