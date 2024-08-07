#include <shoot.h>
#include <REM_BaseTypes.h>

///////////////////////////////////////////////////// STRUCTS

shoot_states shootState = shoot_Off;

///////////////////////////////////////////////////// VARIABLES

bool shoot_charged = false;			// true if the capacitor is fully charged
bool shoot_fault = false;				// true if there is a fault indication by the hardware
static float power = 0; 				// percentage of maximum shooting power [0,6.5]
static bool chargingAllowed = false; 	// true if capacitor is allowed to be charged
static uint32_t lastChangeToReady = 0;	// most recent time shootState changed from charging to ready

///////////////////////////////////////////////////// PRIVATE FUNCTION DECLARATIONS

// Stops and starts the timer for a certain period of time
void resetTimer(int timePeriod); //set timer to timePeriod in us.

int calculateShootingTime(shoot_types type, float speed);

///////////////////////////////////////////////////// PUBLIC FUNCTION IMPLEMENTATIONS

void shoot_Init(){
	shoot_charged = false;
	shoot_fault = false;
	shootState = shoot_Off;
	set_Pin(Kick_pin, 0);		// Kick off
	set_Pin(Chip_pin, 0);		// Chip off
	set_Pin(Charge_pin, 0);		// shoot_Charging on
	shoot_Callback(); 			// go to callback for the first time
}

void shoot_DeInit(){
	shoot_charged = false;
	shootState = shoot_Off;
	set_Pin(Kick_pin, 0);		// Kick off
	set_Pin(Chip_pin, 0);		// Chip off
	set_Pin(Charge_pin, 0);		// shoot_Charging off
	HAL_TIM_Base_Stop(TIM_SHOOT);
}

void shoot_Callback()
{
	int callbackTime = 0;
	float voltage = voltage_Get();
	uint32_t current_time = HAL_GetTick();
	//Fault pin is HIGH by default
	if (!read_Pin(Fault_pin)) {
		shoot_fault = true;
		//shoot_DeInit();
	}

	switch(shootState){
	case shoot_Ready:
		/*
		Start Charging again if:
		1. Charging is allowed
		2. Of of these two conditions is satisfied
			2a. Voltage sensor works and MIN_VOLT_SHOOT <= voltage <= START_REGHARGE_VOLT
			2b. Voltage sensor doesn't work and shootState changed to ready more than 15sec ago
		*/
		if ((voltage_sensor_working && voltage >= MIN_VOLT_SHOOT && voltage <= START_REGHARGE_VOLT) ||
			(!voltage_sensor_working && current_time >= lastChangeToReady + 15000)) {
			shootState = shoot_Charging;
			shoot_charged = false;
		}
		callbackTime = TIMER_FREQ/READY_CALLBACK_FREQ;
		break;
	case shoot_Charging:
		/**
		 * Charge_done_pin true means not done
		 * Charge_done_pin false means done
		*/
		if (!read_Pin(Charge_done_pin)) {
			shootState = shoot_Ready;
			shoot_charged = true;
			lastChangeToReady = HAL_GetTick();
			set_Pin(Charge_pin, 0);
		} else {
			set_Pin(Charge_pin, 1);
		}
		callbackTime = TIMER_FREQ/CHARGING_CALLBACK_FREQ;
		break;
	case shoot_Shooting:
		// Done with shooting, start charging again
		set_Pin(Kick_pin, 0);		// Kick off
		set_Pin(Chip_pin, 0);		// Chip off
		if (chargingAllowed) {
			shootState = shoot_Charging;
			shoot_charged = false;
		} else {
			shootState = shoot_Off;
			shoot_charged = voltage_sensor_working && voltage >= MIN_VOLT_SHOOT;
		}
		callbackTime = TIMER_FREQ/SHOOTING_CALLBACK_FREQ;
		break;
	case shoot_Off:
		set_Pin(Kick_pin, 0);		// Kick off
		set_Pin(Chip_pin, 0);		// Chip off
		set_Pin(Charge_pin, 0);		// kick_Charging off
		callbackTime = TIMER_FREQ/OFF_CALLBACK_FREQ;
		break;
	}
	resetTimer(callbackTime);
}

shoot_states shoot_GetState(){
	return shootState;
}

void shoot_StartCharging() {
	shootState = shoot_Charging;
	chargingAllowed = true;
}

void shoot_DisableCharging() {
	chargingAllowed = false;
	if (shootState == shoot_Charging) shootState = shoot_Ready;
}


void shoot_Shoot(shoot_types type, float speed)
{
	if(shootState == shoot_Ready || shootState == shoot_Off){
		shootState = shoot_Shooting;
		set_Pin(Charge_pin, 0); 									// Disable shoot_Charging
		set_Pin(type == shoot_Kick ? Kick_pin : Chip_pin, 1); 		// Kick/Chip on
		resetTimer(calculateShootingTime(type,speed));
	}
}

///////////////////////////////////////////////////// PRIVATE FUNCTION IMPLEMENTATIONS

void resetTimer(int timePeriod)
{
	HAL_TIM_Base_Stop(TIM_SHOOT);							// Stop timer
	__HAL_TIM_CLEAR_IT(TIM_SHOOT, TIM_IT_UPDATE);			// Clear timer
	__HAL_TIM_SET_COUNTER(TIM_SHOOT, 0);      				// Reset timer
	__HAL_TIM_SET_AUTORELOAD(TIM_SHOOT, timePeriod);		// Set callback time to defined value
	HAL_TIM_Base_Start_IT(TIM_SHOOT);						// Start timer
}

int calculateShootingTime(shoot_types type, float speed) {

	if(speed < MIN_BALL_SPEED) speed = MIN_BALL_SPEED;
    if(MAX_BALL_SPEED < speed) speed = MAX_BALL_SPEED;

	if (type == shoot_Kick) {
		int kickTime = (int)(speed * speed * 67.5f + 340.4f * speed + 1075.9f); //transfer function to convert m/s to time in us
		return kickTime;

	} else if (type == shoot_Chip) {
		int chipTime = (int)(speed * speed * 67.5f + 340.4f * speed + 1075.9f);
		return chipTime;
	}
	return 0;
}