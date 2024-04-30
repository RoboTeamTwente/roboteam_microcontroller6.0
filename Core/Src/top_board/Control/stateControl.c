
#include "stateControl.h"
#include "stateEstimation.h"
#include "logging.h"

///////////////////////////////////////////////////// STRUCTS

static FFparameters feedforwardParameters;

///////////////////////////////////////////////////// VARIABLES
float friction_term;
float damping_term;

 bool wheels_initialized = false;

// The current status of the system.
static PID_states status = off;

// The PID values for u, v, w and yaw.
static PIDvariables stateLocalK[4];

// The global x, y, w and yaw velocities to be achieved [m/s]
static float stateGlobalRef[4] = {0.0f}; 

// The wheel velocities to be achieved [rad/s]
static float wheelRef[4] = {0.0f};

// The current global u, v, w and yaw velocities.
static float stateLocal[4] = {0.0f};

// Whether to move to an absolute angle. If true yes, otherwise use angular velocity.
static bool useAbsoluteAngle = true;
static bool previousUseAbsoluteAngle = true;

// The velocity coupling matrix, used to transform local velocities into wheel velocities [4x3]
static float D[12] = {0.0f};

static float wheels_measured_speeds[4] = {0.0f};      // Stores most recent measurement of wheel speeds in rad/s
static float wheels_commanded_speeds[4] = {0.0f};     // Holds most recent commanded wheel speeds in rad/s

///////////////////////////////////////////////////// STRUCTURE

static PIDvariables wheelsK[4];

///////////////////////////////////////////////////// PRIVATE FUNCTION DECLARATIONS

/**
 * Translates the velocity from a local perspective to wheel speeds.
 * 
 * @param wheelSpeed The speed to be achieved for each wheel [rad/s]
 * @param stateLocal The velocities to be achieved seen from the body perspective {vel_u, vel_v, vel_w} [m/s]
 */
static void body2Wheels(float wheelSpeed[4], float stateLocal[3]);

/**
 * Translates the global coordinate frame to the local coordinate frame.
 * 
 * @param global 	The global coordinates {vel_x, vel_y, vel_w, yaw}
 * @param local 	The local coordinates {vel_u, vel_v, vel_w, yaw}
 */
static void global2Local(float global[4], float local[4]);

/**
 * Determines the desired wheel speeds given the desired velocities
 * 
 * @param stateLocal 		The current u, v, w and yaw speeds seen from the body
 * @param stateGlobalRef 			The instructed global x, y, w and yaw speeds
 * @param velocityWheelRef 	The resulting wheel speeds that should be achieved for each wheel
 */
static void velocityControl(float stateLocal[3], float stateGlobalRef[4], float velocityWheelRef[4]);

/**
 * Determine the speed that the wheels should achieve in order to move towards a desired angle.
 * 
 * @param angleRef The angle to be achieved.
 * @param angle    The current angle.
 * @return float   The PID value to achieve the set angle.
 */
static float absoluteAngleControl(float angleRef, float angle);

///////////////////////////////////////////////////// PUBLIC FUNCTION IMPLEMENTATIONS

int stateControl_Init(){
	damping_term = 0.00145f;
	// damping_term = 0.0f;
	friction_term = 0.02f;

	status = on;
	initPID(&stateLocalK[vel_u], default_P_gain_u, default_I_gain_u, default_D_gain_u);
	initPID(&stateLocalK[vel_v], default_P_gain_v, default_I_gain_v, default_D_gain_v);
	initPID(&stateLocalK[vel_w], default_P_gain_w, default_I_gain_w, default_D_gain_w); 
	initPID(&stateLocalK[yaw], default_P_gain_yaw, default_I_gain_yaw, default_D_gain_yaw);
	/* Initialize wheel controllers */
	for (motor_id_t motor = RF; motor <= RB; motor++){
		initPID(&wheelsK[motor], default_P_gain_wheels, default_I_gain_wheels, default_D_gain_wheels);
	}
	HAL_TIM_Base_Start_IT(TIM_CONTROL);

	// Initialize the velocity coupling matrix.
	D[0] = cosFront;
	D[1] = sinFront; 
	D[2] = 1;
	D[3] = -cosFront;
	D[4] = sinFront;
	D[5] = 1;
	D[6] = -cosBack;
	D[7] = -sinBack;
	D[8] = 1;
	D[9] = cosBack;
	D[10] = -sinBack;
	D[11] = 1;

	return 0;
}

int stateControl_DeInit(){
	status = off;
	HAL_TIM_Base_Stop_IT(TIM_CONTROL);
	return 0;
}

void stateControl_Update(){
	if (status == on){
		float velocityWheelRef[4] = {0.0f};
		velocityControl(stateLocal, stateGlobalRef, velocityWheelRef);

		float angularRef = useAbsoluteAngle ? absoluteAngleControl(stateGlobalRef[yaw], stateLocal[yaw]) : 0.0f;

		for (wheel_names wheel=wheels_RF; wheel<=wheels_RB; wheel++){
			wheelRef[wheel] = velocityWheelRef[wheel] + angularRef;
		}
	}
}

////////////// WHEELS CONTROL START

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
		wheels_measured_speeds[motor] =  WHEEL_ENCODER_TO_OMEGA * encoder_value; // if it doesn't work, get out the calculation of the measured speeds of the if loop.

		// Calculate the velocity error
		float angular_velocity_error = wheels_commanded_speeds[motor] - wheels_measured_speeds[motor]; 		
	
		// If the error is very small, ignore it (why is this here?)
		if (fabs(angular_velocity_error) < 0.1) {
			angular_velocity_error = 0.0f;
			wheelsK[motor].I = 0;
		}

		// FEEDFOWARD of robot 5.0
		float feed_forward = 0.0f;
		float threshold = 0.05f;

		if (fabs(wheels_commanded_speeds[motor]) < threshold) {
    		feed_forward = 0;
		} 
		else if (wheels_commanded_speeds[motor] > 0) {
			feed_forward = damping_term*wheels_commanded_speeds[motor] + friction_term;
    	}
		else if (wheels_commanded_speeds[motor] < 0) {
			feed_forward = damping_term*wheels_commanded_speeds[motor] - friction_term;
    	}

		// Add PID to commanded speed and convert to PWM (range between -1 and 1)
		// float voltage_list = 0*feed_forward + 0.3987 * (PID(angular_velocity_error, &wheelsK[motor]));
		float wheel_speed_percentage = feed_forward + 0.001367311 * (PID(angular_velocity_error, &wheelsK[motor]));
		// 0.04f * 22.2f

		// float batteryVoltage = 1.0f;

		// float wheel_speed_percentage = (voltage_list*(1.0f/batteryVoltage));

		wheels_SetSpeed_PWM(motor, wheel_speed_percentage);
	}
}

/**
 * @brief Stores the commanded wheel speeds, in rad/s, to be used in the next wheels_Update() call
 * This function is the same as wheels_SetSpeeds from Microcontroller 5.0!!!
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
 * @brief Stops the wheels without deinitializing them 
 */
void wheels_Stop() {
	for (int motor = 0; motor < 4; motor++){
		wheels_SetSpeed_PWM(motor, 0);
		wheels_commanded_speeds[motor] = 0;
	}
}

void wheels_SetPIDGains(REM_RobotSetPIDGains* PIDGains){
	for(wheel_names wheel = wheels_RF; wheel <= wheels_RB; wheel++){
		float threshold_REM_message = 2.0f;
		float threshold_compare_value = PIDGains->DbodyYaw;
		if (threshold_compare_value > threshold_REM_message) {
			float akndosad = 0;
		}
		else {
			wheelsK[wheel].kP = PIDGains->Pwheels;
			wheelsK[wheel].kI = PIDGains->Iwheels;
			wheelsK[wheel].kD = PIDGains->Dwheels;
		}
		
	}
}

///////////// WHEELS CONTROL END

void stateControl_SetRef(float _stateGlobalRef[4]){
	stateGlobalRef[vel_x] = _stateGlobalRef[vel_x];
	stateGlobalRef[vel_y] = _stateGlobalRef[vel_y];
	stateGlobalRef[vel_w] = _stateGlobalRef[vel_w];
	stateGlobalRef[yaw] = _stateGlobalRef[yaw];
}

void stateControl_SetState(float _stateLocal[4]){
	stateLocal[vel_u] = _stateLocal[vel_u];
	stateLocal[vel_v] = _stateLocal[vel_v];
	stateLocal[vel_w] = _stateLocal[vel_w];
	stateLocal[yaw] = _stateLocal[yaw];
}

void stateControl_GetPIDGains(PIDvariables gainsLocal[4]){
	gainsLocal[vel_u].kP = stateLocalK[vel_u].kP;
	gainsLocal[vel_u].kI = stateLocalK[vel_u].kI;
	gainsLocal[vel_u].kD = stateLocalK[vel_u].kD;

	gainsLocal[vel_v].kP = stateLocalK[vel_v].kP;
	gainsLocal[vel_v].kI = stateLocalK[vel_v].kI;
	gainsLocal[vel_v].kD = stateLocalK[vel_v].kD;

	gainsLocal[vel_w].kP = stateLocalK[vel_w].kP;
	gainsLocal[vel_w].kI = stateLocalK[vel_w].kI;
	gainsLocal[vel_w].kD = stateLocalK[vel_w].kD;

	gainsLocal[yaw].kP = stateLocalK[yaw].kP;
	gainsLocal[yaw].kI = stateLocalK[yaw].kI;
	gainsLocal[yaw].kD = stateLocalK[yaw].kD;
}

float stateControl_GetIntegral(robot_axes direction) {
	return stateLocalK[direction].I;
}

float* stateControl_GetWheelRef() {
	return wheelRef;
}

float* stateControl_GetBodyGlobalRef() {
	return stateGlobalRef;
}

void stateControl_useAbsoluteAngle(bool angularControl){
	if (angularControl != previousUseAbsoluteAngle){
		stateControl_ResetAngleI();
		stateControl_ResetPID();
	}
	previousUseAbsoluteAngle = angularControl;
    useAbsoluteAngle = angularControl;
}

void stateControl_SetPIDGains(REM_RobotSetPIDGains* PIDGains){
	float threshold_REM_message = 2.0f;
	float threshold_compare_value = PIDGains->DbodyYaw;
	if (threshold_compare_value > threshold_REM_message) {

		float a = PIDGains->PbodyX;
		damping_term = a/100.0f;
		float d = PIDGains->IbodyX;
		friction_term = d/100.0f;

	}
	else {
		stateLocalK[vel_u].kP = PIDGains->PbodyX;
		stateLocalK[vel_u].kI = PIDGains->IbodyX;
		stateLocalK[vel_u].kD = PIDGains->DbodyX;

		stateLocalK[vel_v].kP = PIDGains->PbodyY;
		stateLocalK[vel_v].kI = PIDGains->IbodyY;
		stateLocalK[vel_v].kD = PIDGains->DbodyY;

		stateLocalK[vel_w].kP = PIDGains->PbodyW;
		stateLocalK[vel_w].kI = PIDGains->IbodyW;
		stateLocalK[vel_w].kD = PIDGains->DbodyW;

		stateLocalK[yaw].kP = PIDGains->PbodyYaw;
		stateLocalK[yaw].kI = PIDGains->IbodyYaw;
		stateLocalK[yaw].kD = PIDGains->DbodyYaw;
	}
}

void stateControl_ResetAngleI(){
	stateLocalK[yaw].I = 0;
	stateLocalK[vel_w].I = 0;
}

void stateControl_ResetPID(){
	stateLocalK[yaw].prev_e = 0;
	stateLocalK[yaw].prev_PID = 0;
	stateLocalK[vel_w].prev_e = 0;
	stateLocalK[vel_w].prev_PID = 0;
}

///////////////////////////////////////////////////// PRIVATE FUNCTION IMPLEMENTATIONS

static void body2Wheels(float wheelSpeed[4], float stateLocal[3]){

	// Translate the local u, v, and omega velocities into wheel velocities.
	wheelSpeed[wheels_RF] = stateLocal[vel_u] * D[0] + stateLocal[vel_v] * D[1];
	wheelSpeed[wheels_LF] = stateLocal[vel_u] * D[3] + stateLocal[vel_v] * D[4];
	wheelSpeed[wheels_LB] = stateLocal[vel_u] * D[6] + stateLocal[vel_v] * D[7];
	wheelSpeed[wheels_RB] = stateLocal[vel_u] * D[9] + stateLocal[vel_v] * D[10];

	// Translate wheel velocities into angular velocities
	for (wheel_names wheel=wheels_RF; wheel <= wheels_RB; wheel++) {
		wheelSpeed[wheel] = wheelSpeed[wheel] / rad_wheel;
	}

	// If we do not use angular velocities (w), remove these.
	if (!useAbsoluteAngle) {
        for (wheel_names wheel=wheels_RF; wheel<=wheels_RB; wheel++){
            wheelSpeed[wheel] += stateLocal[vel_w] * rad_robot / rad_wheel;
        }
	}
}

static void global2Local(float global[4], float local[4]){
	//trigonometry
	local[vel_u] = cosf(global[yaw]) * global[vel_x] + sinf(global[yaw]) * global[vel_y];
	local[vel_v] = -sinf(global[yaw]) * global[vel_x] + cosf(global[yaw]) * global[vel_y];
    local[vel_w] = global[vel_w];
	local[yaw] = global[yaw];
}

static void velocityControl(float stateLocal[4], float stateGlobalRef[4], float velocityWheelRef[4]){
	float stateLocalRef[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	float stateLocalRef_PID[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	global2Local(stateGlobalRef, stateLocalRef); //transfer global to local

	// Local control
	float veluErr = (stateLocalRef[vel_u] - stateLocal[vel_u]);
	float velvErr = (stateLocalRef[vel_v] - stateLocal[vel_v]);
	float velwErr = (stateLocalRef[vel_w] - stateLocal[vel_w]);

	stateLocalRef_PID[vel_u] = stateLocalRef[vel_u]/SLIPPAGE_FACTOR_U + PID(veluErr, &stateLocalK[vel_u]);
	stateLocalRef_PID[vel_v] = stateLocalRef[vel_v]/SLIPPAGE_FACTOR_V + PID(velvErr, &stateLocalK[vel_v]);
	stateLocalRef_PID[vel_w] = stateLocalRef[vel_w]/SLIPPAGE_FACTOR_W + PID(velwErr, &stateLocalK[vel_w]);
	
	body2Wheels(velocityWheelRef, stateLocalRef_PID); //translate velocity to wheel speed
}

static float absoluteAngleControl(float angleRef, float angle){
	static float prevangleErr = 0;
	float angleErr = constrainAngle(angleRef - angle);//constrain it to one circle turn
	if (angleErr == 0){
		angleErr = 0.000001*prevangleErr;
	}
	if (fabs(angleErr) < YAW_MARGIN || prevangleErr/angleErr < 0) {
		stateLocalK[yaw].I = 0;
	}
	prevangleErr = angleErr;
	return PID(angleErr, &stateLocalK[yaw]);// PID control from control_util.h
}