/* Description: Top level control interface
 *
 * Instructions:
 * Use the functions in this header to interface with the control code.
 *
*/

#include "stateEstimation.h"
#ifndef CONTROL_CONTROL_H_
#define CONTROL_CONTROL_H_


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
void control_step(ControlOutput* const outputs, const StateInfo* const inputs);

#endif