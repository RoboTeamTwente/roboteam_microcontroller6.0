#include "ball_sensor.h"

bool bs_seesBall = false; // ball sensor sees ball
bool ballSensorIsWorking = false;

// ================ PRIVATE FUNCTION DECLARATIONS ================ //
void read_gpio();

// ====================== PUBLIC FUNCTIONS ====================== //

void ballSensor_Init() {
	ballSensor_TestIfWorking();
	bs_seesBall = false;
}

void ballSensor_DeInit() {
	set_Pin(IR_LED_pin, 0);
	ballSensorIsWorking = false;
	bs_seesBall = false;
}

/**
 * @brief tests if the ball sensor is working
 * @note HAL_Delay is added to give time for the interrupt to be processed
*/
void ballSensor_TestIfWorking() {
	//Setup: put the LED on
	set_Pin(IR_LED_pin, 1);
	HAL_Delay(100);
	ballSensorIsWorking = true;

	//Check 1: check if turning the LED off gives that the robot does see the ball, simulating that the robot got the ball
	set_Pin(IR_LED_pin, 1);
	HAL_Delay(100);
	if (!bs_seesBall) {
		ballSensorIsWorking = false;
		set_Pin(IR_LED_pin, 0);
		return;
	}

	//Check 2: check if turning the LED on gives that the robot doesn't see the ball, simulating that the robot lost the ball
	set_Pin(IR_LED_pin, 0);
	HAL_Delay(100);
	if (bs_seesBall) {
		ballSensorIsWorking = false;
		return;
	}

	set_Pin(IR_LED_pin, 1);
}

/*
read from GPIO:
	If high:
		set seesball to false --> we lost the ball
	else low --> ball is present:
		set seesball to true
	write to LOG about current ball state
	set LED to value of bs_seesBall
*/
void ballSensor_IRQ_Handler() {
	if (!ballSensorIsWorking) return;
	read_gpio();
	if (!bs_seesBall){
		LOG("[BALLSENSOR]:: We lost the ball");
	} else{
		LOG("[BALLSENSOR]:: We have the ball");
	}
	LOG_sendAll();
}

bool ballSensor_seesBall() {
	return bs_seesBall;
}

bool ballSensor_isWorking() {
	return ballSensorIsWorking;
}

// ====================== PRIVATE FUNCTIONS ====================== //
void read_gpio() {
	/*
		Call readPin, will return GPIO_PIN_SET --> that value is high
					  otherwise will return GPIO_PIN_RESET
		If GPIO_PIN_SET then set return to false, otherwise true
	*/
	GPIO_PinState portState = HAL_GPIO_ReadPin(BS_IRQ_GPIO_Port, BS_IRQ_Pin);
	bs_seesBall = portState == GPIO_PIN_RESET;
}
