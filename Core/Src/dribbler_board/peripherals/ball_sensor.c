#include "ball_sensor.h"

// Static to keep everything local to this file
static volatile bool seesBall = false; // ball sensor sees ball
static bool ballSensorIsWorking = false;

// ================ PRIVATE FUNCTION DECLARATIONS ================ //
void read_gpio();


// ====================== PUBLIC FUNCTIONS ====================== //

void ballSensor_Init() {
	ballSensor_TestIfWorking();
	seesBall = false;
}

void ballSensor_DeInit() {
	set_Pin(IR_LED_pin, 0);
	ballSensorIsWorking = false;
	seesBall = false;
}

/**
 * @brief tests if the ball sensor is working
 * @note LED is on afterwards
*/
void ballSensor_TestIfWorking() {
	//Part 1: disable LED and check signal
	ballSensorIsWorking = true;
	set_Pin(IR_LED_pin, 0);
	read_gpio();
	if (seesBall) {
		ballSensorIsWorking = false;
	}

	//Part 2: enable LED and check signal
	set_Pin(IR_LED_pin, 1);
	read_gpio();
	if (!seesBall) {
		ballSensorIsWorking = false;
	}

}

/*
read from GPIO:
	If high:
		set seesball to false --> we lost the ball
	else low --> ball is present:
		set seesball to true
	write to LOG about current ball state
	set LED to value of seesBall
*/
void ballSensor_IRQ_Handler() {
	read_gpio();
	if (!seesBall){
		LOG("[BALLSENSOR]:: We lost the ball");
	} else{
		LOG("[BALLSENSOR]:: We have the ball");
	}
}

bool ballSensor_seesBall() {
	return seesBall;
}

// ====================== PRIVATE FUNCTIONS ====================== //
void read_gpio() {
	/*
		Call readPin, will return GPIO_PIN_SET --> that value is high
					  otherwise will return GPIO_PIN_RESET
		If GPIO_PIN_SET then set return to false, otherwise true
	*/
	GPIO_PinState portState = HAL_GPIO_ReadPin(BS_GPIO_Port, BS_Pin);
	seesBall = portState == GPIO_PIN_RESET;
}
