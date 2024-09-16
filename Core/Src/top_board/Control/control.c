#include "control.h"
#include "stateEstimation.h"
#include "stateControl.h"


void control_init() {
    control_util_Init();
    stateControl_Init();
    stateEstimation_Init();
}

void control_step(ControlOutput* const output, const StateInfo* const inputs) {
    // Run state estimation
    float state[4];
    stateEstimation_Update(inputs);
    stateEstimation_GetState(state);

    // Run state control
    stateControl_SetState(state);
    stateControl_Update(output);
}
