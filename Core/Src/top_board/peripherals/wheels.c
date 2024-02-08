#include "wheels.h"
#include "tim_util.h"
#include "gpio_util.h"
#include "peripheral_util.h"

///////////////////////////////////////////////////// PRIVATE FUNCTION DECLARATIONS

static inline uint32_t constrain_uint32(uint32_t value, uint32_t min, uint32_t max);
static void setSlaveSelect(motor_id_t motor, GPIO_PinState state);
static uint16_t wheels_TransmitCommand(motor_id_t motor, uint8_t rwBit, uint8_t address4Bits, uint16_t data11Bits);

///////////////////////////////////////////////////// STRUCTS

static PIDvariables wheelsK[4];

///////////////////////////////////////////////////// VARIABLES

static bool wheels_initialized = false;
static bool wheels_braking = true;

static float wheels_measured_speeds[4] = {};      // Stores most recent measurement of wheel speeds in rad/s
static float wheels_commanded_speeds[4] = {};     // Holds most recent commanded wheel speeds in rad/s


///////////////////////////////////////////////////// PUBLIC FUNCTION IMPLEMENTATIONS

/**
  * @brief Start the PWM timers and set the settings on the motor driver
  * @retval Motor status
  */
Motor_StatusTypeDef wheels_Init(){
	wheels_Brake();

	/* Initialize wheel controllers */
	for (motor_id_t motor = RF; motor <= RB; motor++){
		//initPID(&wheelsK[wheel], default_P_gain_wheels, default_I_gain_wheels, default_D_gain_wheels);
		continue;
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
Motor_StatusTypeDef wheels_SetSpeed(motor_id_t id, float value){
	if(value > 1 || value < -1) return MOTOR_ERROR;
	wheels_SetPWM(id, (int32_t) (value * MAX_PWM));
	return MOTOR_OK;
}


/**
 * @brief Stores the commanded wheel speeds, in rad/s, to be used in the next wheels_Update() call
 * 
 * @param speeds float[4]{RF, LF, LB, RB} commanded wheels speeds, in rad/s. These values are stored in the file-local
 * variable 'wheels_commanded_speeds'. This variable will later be used in wheels_Update() to control the wheels.
 */
void wheels_set_command_speed(const float speeds[4]) {
	for(motor_id_t wheel = RF; wheel <= RB; wheel++){
		wheels_commanded_speeds[wheel] = speeds[wheel];
	}
}


/**
 * @brief Updates the wheels towards the commanded wheel speeds using the encoders and a PID controller.
 * 
 * TODO : check OMEGAtoPWM values for new motor!!!
 * This function is resonsible for getting the wheels to the commanded speeds, as stored in the file-local variable
 * "wheels_commanded_speeds". Wheel speeds, given in rad/s, are converted directly to a PWM value with help of the
 * conversion variable OMEGAtoPWM. This variable is based on information from the Maxon Motor datasheet. 
 * 
 * A PID controller is used to handle any error between the commanded and actual wheel speeds. First, the current wheel
 * speeds are measured by reading out the encoders and converting these values to rad/s. The commanded wheel speeds are
 * then subtracted from these measured wheel speeds, giving the error. This error is put through a PID controller, and
 * the resulting PID value is added to the commanded speeds before being converted to a PWM value. 
 * 
 * The resulting PWM values have a range between -1 and 1. Positive values mean clockwise and negative values mean counter-clockwise direction. 
 */
void wheels_Update() {
	/* Don't run the wheels if these are not initialized */
	/* Not that anything would happen anyway, because the PWM timers wouldn't be running, but still .. */
	if(!wheels_initialized){
		wheels_Stop();
		return;
	}

	for (motor_id_t motor = RF; motor <= RB; motor++) {
		int16_t	encoder_value = encoder_GetCounter(motor);
		encoder_ResetCounter(motor);

		// Calculate the velocity error
		float angular_velocity_error = wheels_commanded_speeds[motor] - wheels_measured_speeds[motor]; 		// TODO Convert encoder values to rad/s
	
		// If the error is very small, ignore it (why is this here?)
		if (fabs(angular_velocity_error) < 0.1) {
			angular_velocity_error = 0.0f;
			wheelsK[motor].I = 0;
		}

		float feed_forward = 0.0f;
		float threshold = 0.05f;

		if (fabs(wheels_commanded_speeds[motor]) < threshold) {
    		feed_forward = 0;
		} 
		else if (wheels_commanded_speeds[motor] > 0) {
			feed_forward = wheels_commanded_speeds[motor] + 13;
    	}
		else if (wheels_commanded_speeds[motor] < 0) {
			feed_forward = wheels_commanded_speeds[motor] - 13;
    	}

		// TODO Add PID to commanded speed and convert to [-1, 1] range + ADD FEEDFOWARD !
		int32_t wheel_speed = 0;

		wheels_SetSpeed(motor, wheel_speed);
	}
}

/**
 * @brief Get the last measured wheel speeds in rad/s
 * 
 * @param speeds float[4]{RF, LF, LB, RB} output array in which the measured speeds will be stored
 */
void wheels_GetMeasuredSpeeds(float speeds[4]) {
	// Copy into "speeds", so that the file-local variable "wheels_measured_speeds" doesn't escape
	for (wheel_names wheel = wheels_RF; wheel <= wheels_RB; wheel++) {
		speeds[wheel] = wheels_measured_speeds[wheel];
	}
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
 * @brief Stops the wheels without deinitializing them 
 */
void wheels_Stop() {
	for (int motor = 0; motor < 4; motor++){
		wheels_SetSpeed(motor, 0);
		wheels_commanded_speeds[0] = 0;
	}
}

/**
 * @brief returns whether the wheels are braking
*/
bool wheels_GetWheelsBraking() {
	return wheels_braking;
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
