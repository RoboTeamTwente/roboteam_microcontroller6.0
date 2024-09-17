#include "control.h"
#include "stateEstimation.h"
#include "stateControl.h"
#include "Controller.h"

void old_control_init() {
    control_util_Init();
    stateControl_Init();
    stateEstimation_Init();
}

void control_init() {
    // Initialize the generated control system
    Controller_initialize();
}

void old_control_step(ControlOutput* const output, const StateInfo* const inputs) {
    // Run state estimation
    float state[4];
    stateEstimation_Update(inputs);
    stateEstimation_GetState(state);

    // Run state control
    stateControl_SetState(state);
    stateControl_Update(output);
}

void control_step(ControlOutput* const output, const StateInfo* const state, const ControlRef* const ref) {
    // Pass the arguments on to the generated step function
    Controller_step(state->wheelSpeeds,
        state->rateOfTurn,
        state->visionYaw,
        ref->velRef,
        ref->yawRef,
        ref->accRef,
        ref->yawRateRef,
        ref->YawAccRef,
        output
    );
}

void control_terminate() {}
