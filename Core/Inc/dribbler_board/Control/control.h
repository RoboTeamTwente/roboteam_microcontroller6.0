#ifndef CONTROL_CONTROL_H_
#define CONTROL_CONTROL_H_

#include "numtypes.h"
#include "DribblerController.h"
#include <stdbool.h>


/**
 * @brief Initialize the control subsystem.
 *
 */
void control_init();

/**
 * @brief Run the control subsystem for one timestep.
 * @param output Motor PWM fraction.
 */
void control_step(f32* const output, f32 current, f32 encoder, bool ball_detec);

/**
 * @brief Runs termination logic for the control subsystem.
 *
 * @note Not currently needed, but will likely be needed in the future.
 */
void control_terminate();

#endif /* CONTROL_CONTROL_H_ */
