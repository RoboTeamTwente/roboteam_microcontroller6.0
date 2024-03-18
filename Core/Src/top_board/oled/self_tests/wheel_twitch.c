#include "wheel_twitch.h"

struct page_struct wheel_twitch_warning;
struct page_struct wheel_twitch_running;
struct page_struct wheel_twitch_result;

char* number_to_status(int num);

/**
 * @brief initialize all the wheel twitch pages
 * @note id 112x
*/
void wheel_twitch_init(page_struct *parent) {
    pages_set_default_values(&wheel_twitch_warning);
    wheel_twitch_warning.id = 1121;
    strcpy(wheel_twitch_warning.page_name, "Wheel twitch");
    wheel_twitch_warning.parent = parent;
    wheel_twitch_warning.is_test = BLOCKING_TEST;
    strcpy(wheel_twitch_warning.line0, "Make sure that");
    strcpy(wheel_twitch_warning.line1, "wheels are of");
    strcpy(wheel_twitch_warning.line2, "ground. Press");
    strcpy(wheel_twitch_warning.line3, "\"OK\" to run");
    add_child_to_parent(&wheel_twitch_warning);

    pages_set_default_values(&wheel_twitch_running);
    wheel_twitch_running.id = 1122;
    strcpy(wheel_twitch_running.page_name, "Wheel twitch");
    wheel_twitch_running.parent = &wheel_twitch_warning;
    wheel_twitch_running.is_test = BLOCKING_TEST;
    add_child_to_parent(&wheel_twitch_running);

    pages_set_default_values(&wheel_twitch_result);
    wheel_twitch_result.id = 1123;
    strcpy(wheel_twitch_result.page_name, "Wheel twitch");
    wheel_twitch_result.parent = &wheel_twitch_running;
    wheel_twitch_result.is_test = BLOCKING_TEST;
    add_child_to_parent(&wheel_twitch_result);
}

/**
 * @brief let all the wheels turn forward and backwards slightly. After prepare the visualazation for the data
*/
void wheel_twitch_run() {
    start_of_test();
    wheels_Unbrake();
    uint8_t working[4] = {0};
    for(int motor = 0; motor < 4; motor++){//motors
		HAL_Delay(10);
		if(wheels_DriverPresent(motor) != MOTOR_OK) continue; //check if motor driver is connected
		working[motor]++;//increment if passes test

		encoder_ResetCounter(motor);
		wheels_SetSpeed_PWM(motor, 0.1f);

		for(int i = 0; i < 50; i++){ // max 0.5 sec long
			if(encoder_GetCounter(motor) > 100){
				working[motor]++;//increment if passes test
				break;
			}
			HAL_Delay(10);
		}
		wheels_SetSpeed_PWM(motor, 0);

		if(working[motor] != 2) continue;//check if previous test passed

		HAL_Delay(50);

		encoder_ResetCounter(motor);
		wheels_SetSpeed_PWM(motor, -0.1f);

		for(int i = 0; i < 50; i++){ // max .5 sec long
			if(encoder_GetCounter(motor) < -100){
				working[motor]++;//increment if passes test
				break;
			}
			HAL_Delay(10);
		}
		wheels_SetSpeed_PWM(motor, 0);
	}

	wheels_Brake();
    end_of_test();

    char temp[MAX_STRING_LENGTH];
    sprintf(temp, "RF: %s", number_to_status(working[0]));
    strcpy(wheel_twitch_result.line0, temp);
    sprintf(temp, "LF: %s", number_to_status(working[1]));
    strcpy(wheel_twitch_result.line1, temp);
    sprintf(temp, "LB: %s", number_to_status(working[2]));
    strcpy(wheel_twitch_result.line2, temp);
    sprintf(temp, "RB: %s", number_to_status(working[3]));
    strcpy(wheel_twitch_result.line3, temp);
}

/**
 * @brief convert status code to words
*/
char* number_to_status(int status) {
    switch (status) {
        case 0:
            return "No driver present";
        case 1:
            return "Driver present";
        case 2:
            return "One direction";
        case 3:
            return "Working";
    }
    return "";
}