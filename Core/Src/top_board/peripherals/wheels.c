#include "wheels.h"
#include "tim_util.h"
#include "gpio_util.h"
#include "peripheral_util.h"



static inline uint32_t constrain_uint32(uint32_t value, uint32_t min, uint32_t max) {
    return (value < min) ? min : ((value > max) ? max : value);
}


static void setSlaveSelect(motor_id_t motor, GPIO_PinState state);
static uint16_t Motor_TransmitCommand(motor_id_t motor, uint8_t rwBit, uint8_t address4Bits, uint16_t data11Bits);


/**
  * @brief Start the PWM timers and set the settings on the motor driver
  * @param None
  * @retval None
  */
Motor_StatusTypeDef Motor_Init(){

	HAL_TIM_Base_Start(PWM_RF.TIM);//RF
	HAL_TIM_Base_Start(PWM_RB.TIM);//RB
	HAL_TIM_Base_Start(PWM_LF.TIM);//LF
	HAL_TIM_Base_Start(PWM_LB.TIM);//LB

	HAL_TIM_PWM_Start(PWM_RF.TIM,PWM_RF.Channel);//RF
	HAL_TIM_PWM_Start(PWM_RB.TIM,PWM_RB.Channel);//RB
	HAL_TIM_PWM_Start(PWM_LF.TIM,PWM_LF.Channel);//LF
	HAL_TIM_PWM_Start(PWM_LB.TIM,PWM_LB.Channel);//LB

	uint16_t commands[2] = {0b00001000000, //set the correct settings(1x PWM mode);
							0b01011000011};//set voltage sense to 40V/V
						     //9876543210

	Motor_StatusTypeDef output = MOTOR_OK;
	for (int motor = 3; motor < 4; motor++){
		HAL_Delay(1);
		if(Motor_TransmitCommand(motor, 0, 0x02, commands[0]) != commands[0]) output = MOTOR_NORESPONSE;
		HAL_Delay(1);
		if(Motor_TransmitCommand(motor, 0, 0x06, commands[1]) != commands[1]) output = MOTOR_NORESPONSE;
		Motor_SetPWM(motor, 0);
	}




	Motor_WheelsBrake(0);//brakes are active low, so 0 means brakes are enabled
	return output;
}


/**
  * @brief Returns whether board can communicate with the motor driver
  * @param Motor id
  * @retval Motor status
  */
Motor_StatusTypeDef Motor_DriverPresent(motor_id_t motor){
	uint16_t received = 0;
	received = Motor_TransmitCommand(motor, 1, 0x03, 0);//read mode

	if(received != 0 && received != 0xFFFF) return MOTOR_OK;

	return MOTOR_NORESPONSE;
}

/**
  * @brief Returns whether motor driver has any errors
  * @param Motor id
  * @retval Motor status
  */
Motor_StatusTypeDef Motor_DriverStatus(motor_id_t motor){
	//needs to be implemented
	return MOTOR_OK;
}


/**
  * @brief Sends SPI command to motor
  * @param Motor id
  * @param Read/Write bit (1 = read mode, 0 = write mode)
  * @param Address bits (4 bits)
  * @param Data bits (11 bits)
  * @retval response of the motor driver
  */
static uint16_t Motor_TransmitCommand(motor_id_t motor, uint8_t rwBit, uint8_t address4Bits, uint16_t data11Bits){ //format: 1 R/W, 4 address, 11 data
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
  * @param Motor id
  * @param State of the pin (0 or 1)
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

/**
  * @brief Sets the brakes
  * @param Brake state (0 or 1)
  * @note Brakes are active LOW, so 1 means braking, 0 means no brakes
  * @retval Motor status
  */
Motor_StatusTypeDef Motor_WheelsBrake(bool BrakeStatus){
	HAL_GPIO_WritePin(RB_BRK_GPIO_Port, RB_BRK_Pin, BrakeStatus);
	HAL_GPIO_WritePin(LB_BRK_GPIO_Port, LB_BRK_Pin, BrakeStatus);
	HAL_GPIO_WritePin(RF_BRK_GPIO_Port, RF_BRK_Pin, BrakeStatus);
	HAL_GPIO_WritePin(LF_BRK_GPIO_Port, LF_BRK_Pin, BrakeStatus);
	return MOTOR_OK;
}

/**
  * @brief Turns off encoder timers
  * @param None
  * @retval Motor status
  */
Motor_StatusTypeDef wheels_DeInit(){
	HAL_TIM_PWM_Stop(PWM_RF.TIM,PWM_RF.Channel);//RF
	HAL_TIM_PWM_Stop(PWM_RB.TIM,PWM_RB.Channel);//RB
	HAL_TIM_PWM_Stop(PWM_LF.TIM,PWM_LF.Channel);//LF
	HAL_TIM_PWM_Stop(PWM_LB.TIM,PWM_LB.Channel);//LB
	return MOTOR_OK;
}


/**
  * @brief Sets motor PWM
  * @param Motor id
  * @param PWM value
  * @note PWM value is between -PWM_MAX and +PWM_MAX, positive is CW and negative is CCW
  * @retval response of the motor driver
  */
Motor_StatusTypeDef Motor_SetPWM(motor_id_t id, int32_t Value){


	bool Direction = (Value > 0); // forward if positive, back if neg

	uint32_t PWMValue = MAX_PWM - constrain_uint32(abs(Value), 0,  MAX_PWM); //limit the pwm to MAX_PWM

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
	return MOTOR_OK;
}

/**
  * @brief Sets motor PWM
  * @param Motor id
  * @param float
  * @note value is between -1 and +1, positive is CW and negative is CCW
  * @retval response of the motor driver
  */
Motor_StatusTypeDef Motor_Set(motor_id_t id, float Value){
	if(Value > 1 || Value < -1) return MOTOR_ERROR;
	return Motor_SetPWM(id, Value * MAX_PWM);
}




/**
  * @brief Starts the encoder timers
  * @param None
  * @retval Motor state
  */
Motor_StatusTypeDef Encoder_Init(){
	HAL_TIM_Base_Start(ENC_RF);//RF
	HAL_TIM_Base_Start(ENC_LB);//LB
	HAL_TIM_Base_Start(ENC_RB);//RB
	HAL_TIM_Base_Start(ENC_LF);//LF


	set_Pin(Encoder_Enable_pin, 1);// enable encoder chips, active high
	return MOTOR_OK;
}


/**
  * @brief Returns the counter value from the encoder.
  * @param Motor id
  * @retval Returns an int_16_t
  */
int16_t Encoder_GetCounter(motor_id_t id){
	uint16_t rotationsuint = 0;
	int16_t rotationsint = 0;

	switch(id){
		case RF:
			rotationsuint = __HAL_TIM_GET_COUNTER(ENC_RF);
			break;
		case LB:
			rotationsuint = __HAL_TIM_GET_COUNTER(ENC_LB);
			break;
		case RB:
			rotationsuint = __HAL_TIM_GET_COUNTER(ENC_RB);
			break;
		case LF:
			rotationsuint = __HAL_TIM_GET_COUNTER(ENC_LF);
			break;
	}

	 if (rotationsuint <= 32767) { //convert the uint16_t into signed form
		 rotationsint = (int)rotationsuint;
	} else {
		rotationsint = -1 * (int)(65535 - rotationsuint + 1);
	}

	 return rotationsint;
}


/**
  * @brief Resets the encoder counter to 0
  * @param Motor id
  * @retval Motor state
  */
Motor_StatusTypeDef Encoder_ResetCounter(motor_id_t id){
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
	return MOTOR_OK;
}













