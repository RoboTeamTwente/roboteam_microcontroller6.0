#include "wheels.h"
#include "tim_util.h"
#include "gpio_util.h"
#include "peripheral_util.h"
#include "stateControl.h"

///////////////////////////////////////////////////// PRIVATE FUNCTION DECLARATIONS

static inline uint32_t constrain_uint32(uint32_t value, uint32_t min, uint32_t max);
static void setSlaveSelect(motor_id_t motor, GPIO_PinState state);
static uint16_t wheels_TransmitCommand(motor_id_t motor, uint8_t rwBit, uint8_t address4Bits, uint16_t data11Bits);

///////////////////////////////////////////////////// STRUCTS

static PIDvariables wheelsK[4];

///////////////////////////////////////////////////// VARIABLES

static bool wheels_initialized = false;
static bool wheels_braking = true;

///////////////////////////////////////////////////// PUBLIC FUNCTION IMPLEMENTATIONS

/**
  * @brief Start the PWM timers and set the settings on the motor driver
  * @retval Motor status
  */
Motor_StatusTypeDef wheels_Init(){
	wheels_Brake();

	/* Initialize wheel controllers */
	for (motor_id_t motor = RF; motor <= RB; motor++){
		initPID(&wheelsK[motor], default_P_gain_wheels, default_I_gain_wheels, default_D_gain_wheels);
	}

	/* Start the PWM timers */
	start_PWM(PWM_RF);
	start_PWM(PWM_RB);
	start_PWM(PWM_LB);
	start_PWM(PWM_LF);

	uint16_t commands[2] = {0b00001000000, //set the correct settings(1x PWM mode);
							0b01011000011};//set voltage sense to 40V/V
						     //9876543210

	Motor_StatusTypeDef output = MOTOR_OK;

	for (int motor = 0; motor < 4; motor++){
		HAL_Delay(1);
		if(wheels_TransmitCommand(motor, 0, 0x02, commands[0]) != commands[0]) output = MOTOR_NORESPONSE;
		HAL_Delay(1);
		if(wheels_TransmitCommand(motor, 0, 0x06, commands[1]) != commands[1]) output = MOTOR_NORESPONSE;
		wheels_SetPWM(motor, 0);
	}


	wheels_initialized = true;

	return output;
}

/**
  * @brief Turns off encoder timers
  * @retval Motor status
  */
void wheels_DeInit(){

	wheels_initialized = false;
	
	/* Stop the PWM timers */
	stop_PWM(PWM_RF);
	stop_PWM(PWM_RB);
	stop_PWM(PWM_LB);
	stop_PWM(PWM_LF);

	wheels_Stop();
	wheels_Brake();
}

/**
  * @brief Sets motor PWM
  * @param id Motor id
  * @param value PWM value
  * @note PWM value is between -PWM_MAX and +PWM_MAX, positive is CW and negative is CCW
  */
void wheels_SetPWM(motor_id_t id, int32_t value){


	bool Direction = (value > 0); // forward if positive, back if neg

	uint32_t PWMValue = MAX_PWM - constrain_uint32(abs(value), 0,  MAX_PWM); //limit the pwm to MAX_PWM

	switch(id){
	case RF:
		set_PWM(PWM_RF,PWMValue);
		set_Pin(RF_DIR_pin, Direction);
		break;
	case RB:
		set_PWM(PWM_RB,PWMValue);
		set_Pin(RB_DIR_pin, Direction);
		break;
	case LB:
		set_PWM(PWM_LB,PWMValue);
		set_Pin(LB_DIR_pin, Direction);
		break;
	case LF:
		set_PWM(PWM_LF,PWMValue);
		set_Pin(LF_DIR_pin, Direction);
		break;
	}
}

/**
  * @brief Sets motor PWM
  * @param id Motor id
  * @param value float
  * @note value is between -1 and +1, positive is CW and negative is CCW
  * @retval response of the motor driver
  */
Motor_StatusTypeDef wheels_SetSpeed_PWM(motor_id_t id, float value){
	if(value > 1 || value < -1) return MOTOR_ERROR;
	wheels_SetPWM(id, (int32_t) (value * MAX_PWM));
	return MOTOR_OK;
}

/**
 * @brief Get the current wheel PWMs
 * 
 * @param pwms uint32_t[4]{RF, LF, LB, RB} output array in which the wheel PWMs will be stored
 */
void wheels_GetPWM(uint32_t pwms[4]) {
	pwms[wheels_RF] = get_PWM(PWM_RF);
	pwms[wheels_RB] = get_PWM(PWM_RB);
	pwms[wheels_LB] = get_PWM(PWM_LB);
	pwms[wheels_LF] = get_PWM(PWM_LF);
}

void wheels_SetPIDGains(REM_RobotSetPIDGains* PIDGains){
	for(wheel_names wheel = wheels_RF; wheel <= wheels_RB; wheel++){
		wheelsK[wheel].kP = PIDGains->Pwheels;
		wheelsK[wheel].kI = PIDGains->Iwheels;
    	wheelsK[wheel].kD = PIDGains->Dwheels;
	}
}

/**
 * @brief Enable the brakes
 */
void wheels_Brake() {
	// Set pin to LOW to brake
	set_Pin(RB_Brake_pin, false);
	set_Pin(LB_Brake_pin, false);
	set_Pin(RF_Brake_pin, false);
	set_Pin(LF_Brake_pin, false);

	wheels_braking = true;
}

/**
 * @brief Disable the brakes
 */
void wheels_Unbrake(){
	// Set pin to HIGH to unbrake
	set_Pin(RB_Brake_pin, true);
	set_Pin(LB_Brake_pin, true);
	set_Pin(RF_Brake_pin, true);
	set_Pin(LF_Brake_pin, true);

	wheels_braking = false;
}

/**
 * @brief returns whether the wheels are braking
*/
bool wheels_GetWheelsBraking() {
	return wheels_braking;
}

/**
 * @brief Stops the wheels without deinitializing them 
 */
void wheels_Stop() {
	for (int motor = 0; motor < 4; motor++){
		wheels_SetSpeed_PWM(motor, 0);
		wheels_commanded_speeds[0] = 0;
	}
}

/**
  * @brief Returns whether board can communicate with the motor driver
  * @param motor Motor id
  * @retval Motor status
  */
Motor_StatusTypeDef wheels_DriverPresent(motor_id_t motor){
	uint16_t received = 0;
	received = wheels_TransmitCommand(motor, 1, 0x03, 0);//read mode

	if(received != 0 && received != 0xFFFF) return MOTOR_OK;

	return MOTOR_NORESPONSE;
}

/**
  * @brief Returns whether motor driver has any errors
  * @param Motor id
  * @retval Motor status
  */
Motor_StatusTypeDef wheels_DriverStatus(motor_id_t motor){
	//TODO needs to be implemented
	return MOTOR_OK;
}


/**
  * @brief Starts the encoder timers
  * @retval Motor state
  */
void encoder_Init(){
	HAL_TIM_Base_Start(ENC_RF);//RF
	HAL_TIM_Base_Start(ENC_LB);//LB
	HAL_TIM_Base_Start(ENC_RB);//RB
	HAL_TIM_Base_Start(ENC_LF);//LF


	set_Pin(Encoder_Enable_pin, 1);// enable encoder chips, active high
}


/**
  * @brief Returns the counter value from the encoder.
  * @param id Motor id
  * @retval Returns an int_16_t
  */
int16_t encoder_GetCounter(motor_id_t id){
	int16_t rotationsint = 0;

	switch(id){
		case RF:
			rotationsint = __HAL_TIM_GET_COUNTER(ENC_RF);
			break;
		case LB:
			rotationsint = __HAL_TIM_GET_COUNTER(ENC_LB);
			break;
		case RB:
			rotationsint = __HAL_TIM_GET_COUNTER(ENC_RB);
			break;
		case LF:
			rotationsint = __HAL_TIM_GET_COUNTER(ENC_LF);
			break;
	}

	 return rotationsint;
}


/**
  * @brief Resets the encoder counter to 0
  * @param id Motor id
  * @retval Motor state
  */
void encoder_ResetCounter(motor_id_t id){
	switch(id){
		case RF:
			__HAL_TIM_SET_COUNTER(ENC_RF,0);
			break;
		case LB:
			__HAL_TIM_SET_COUNTER(ENC_LB,0);
			break;
		case RB:
			__HAL_TIM_SET_COUNTER(ENC_RB,0);
			break;
		case LF:
			__HAL_TIM_SET_COUNTER(ENC_LF,0);
			break;
	}
}





///////////////////////////////////////////////////// PRIVATE FUNCTION IMPLEMENTATIONS

static inline uint32_t constrain_uint32(uint32_t value, uint32_t min, uint32_t max) {
    return (value < min) ? min : ((value > max) ? max : value);
}

/**
  * @brief Sends SPI command to motor
  * @param Motor id
  * @param rwBit Read/Write bit (1 = read mode, 0 = write mode)
  * @param address4Bits Address bits (4 bits)
  * @param data11Bits Data bits (11 bits)
  * @retval response of the motor driver
  */
static uint16_t wheels_TransmitCommand(motor_id_t motor, uint8_t rwBit, uint8_t address4Bits, uint16_t data11Bits){ //format: 1 R/W, 4 address, 11 data
	uint16_t command = 0;
	uint16_t received = 0;

	command = ((uint16_t)(rwBit & 0x01)<<15) | ((uint16_t)(address4Bits & 0x0F) << 11) | (data11Bits & 0x7FF);

	setSlaveSelect(motor, 0);
	HAL_SPI_TransmitReceive(MOTOR_SPI, (uint8_t*)&command, (uint8_t*)&received, 1, 100);
	setSlaveSelect(motor, 1);

	return received;
}

/**
  * @brief Sents slave select pin of the specified motor
  * @param motor motor id
  * @param state state of the pin (0 or 1)
  * @retval None
  */
static void setSlaveSelect(motor_id_t motor, GPIO_PinState state){
	switch(motor){
		case RB:
			set_Pin(RB_CS_pin, state);
			break;
		case RF:
			set_Pin(RF_CS_pin, state);
			break;
		case LB:
			set_Pin(LB_CS_pin, state);
			break;
		case LF:
			set_Pin(LF_CS_pin, state);
			break;
	}
}
