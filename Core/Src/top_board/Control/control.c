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
    // Register the control interrupt
    HAL_TIM_Base_Start_IT(TIM_CONTROL);
}

void old_control_step(ControlOutput* const output, const StateInfo* const inputs) {
    // Run state estimation
    float state[4];
    stateEstimation_Update(inputs);
    stateEstimation_GetState(state);

    // Run state control
    stateControl_SetState(state);
    stateControl_Update(output);
    output->wheel_efforts[0] = 0.05f;
}

void control_step(ControlOutput* const output, const StateInfo* const state, const ControlRef* const ref) {
    // Pass the arguments on to the generated step function
    Controller_step(state->wheelSpeeds,
        state->rateOfTurn,
        state->xsensYaw,
        ref->velRef,
        ref->yawRef,
        ref->accRef,
        ref->yawRateRef,
        ref->YawAccRef,
        state->xsensAcc,
        output
    );
}

void control_terminate() {
    // De-register the control interrupt
    HAL_TIM_Base_Stop_IT(TIM_CONTROL);
}
