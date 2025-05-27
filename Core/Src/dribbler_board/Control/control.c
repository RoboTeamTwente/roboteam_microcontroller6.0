#include "control.h"


void control_init() {
    DribblerController_initialize();
}

void control_step(f32* const output, f32 current, f32 encoder, bool ball_detec) {
    DribblerController_step(encoder, ball_detec, current, 1, output);
}

void control_terminate() {
    DribblerController_terminate();
}