
#include "stateControl.h"
#include "stateEstimation.h"
#include "logging.h"

///////////////////////////////////////////////////// STRUCTS

static FFparameters feedforwardParameters;

///////////////////////////////////////////////////// VARIABLES
float friction_term;
float damping_term;

bool wheels_initialized = false;
float wheel_speed_fraction[4] = {0.0f, 0.0f, 0.0f, 0.0f};

// The current status of the system.
static PID_states status = off;

// The PID values for u, v, w and yaw.
static PIDvariables stateLocalK[4];

// The global x, y, w and yaw velocities to be achieved [m/s]
static float stateGlobalRef[4] = {0.0f};
static float stateGlobalRefAcceleration[3] = {0.0f};

static float mass = 2.632; // [kg]
static float inertia = 0.0; // not correct, should be changed to correct value if rotational inertia feedforward will also be implemented
static int8_t wheelFBOn = 1;
static int8_t wheelFFOn = 1;
static int8_t massFFOn = 1;

// The wheel velocities to be achieved [rad/s]
static float wheelRef[4] = {0.0f};
static float wheelRefBodyScaled[4] = {0.0f};

// The current global u, v, w and yaw velocities.
static float stateLocal[4] = {0.0f};

// The reference u, v, w reference velocities.
static float stateLocalRef[4] = {0.0f};
static float stateLocalRefBodyScaled[4] = {0.0f};
static float stateLocalRefAcceleration[3] = {0.0f};

// Whether to move to an absolute angle. If true yes, otherwise use angular velocity.
static bool useAbsoluteAngle = true;
static bool previousUseAbsoluteAngle = true;

// The velocity coupling matrix, used to transform local velocities into wheel velocities [4x3]
static float D[12] = {0.0f};

static float wheels_measured_speeds[4] = {0.0f};      // Stores most recent measurement of wheel speeds in rad/s

///////////////////////////////////////////////////// STRUCTURE

static PIDvariables wheelsK[4];

///////////////////////////////////////////////////// PRIVATE FUNCTION DECLARATIONS

static float sineEval(float x,float a,float b,float c);
static float constEval(float x,float b,float c,float d);
static float constsineEval(float x,float a,float b,float c,float d);
static float detailedFitEval(float theta,float b,float c,float param1,float param2,float param3,float param4);
static float feedforwardFriction(float wheelRef, float rho, float theta, float omega, wheel_names wheel);
static float feedforwardMass(float stateLocalRefAcceleration[3], motor_id_t motor);

/**
 * Translates the velocity from a local perspective to wheel speeds.
 * 
 * @param wheelSpeed The speed to be achieved for each wheel [rad/s]
 * @param stateLocal The velocities to be achieved seen from the body perspective {vel_u, vel_v, vel_w} [m/s]
 */
static void body2Wheels(float wheelSpeed[4], float stateLocal[4]);

/**
 * Translates the global coordinate frame to the local coordinate frame.
 * 
 * @param global 	The global coordinates {vel_x, vel_y, vel_w, yaw}
 * @param local 	The local coordinates {vel_u, vel_v, vel_w, yaw}
 * @param yaw_angle 		The current yaw angle (stateLocal[yaw])
 */
static void global2Local(float global[4], float local[4], float yaw_angle, float stateGlobalRefAcceleration[3], float stateLocalRefAcceleration[3]);

/**
 * Determines the desired wheel speeds given the desired velocities
 * 
 * @param stateLocal 		The current u, v, w and yaw speeds seen from the body
 * @param stateGlobalRef 			The instructed global x, y, w and yaw speeds
 * @param velocityWheelRef 	The resulting wheel speeds that should be achieved for each wheel
 */
static void velocityControl(float stateLocal[4], float stateGlobalRef[4], float velocityWheelRef[4]);

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
	// feedforwardParameters.a[0] = 0.0f;
	// feedforwardParameters.a[1] = 0.0f;
	// feedforwardParameters.a[2] = 0.0f;
	// feedforwardParameters.a[3] = 0.0f;

	// feedforwardParameters.d[0] = 1.05f;
	// feedforwardParameters.d[1] = 1.05f;
	// feedforwardParameters.d[2] = 1.05f;
	// feedforwardParameters.d[3] = 1.05f;

	feedforwardParameters.b[0] = (2.0f*M_PI)/360.0f*180.0f/M_PI;
	feedforwardParameters.b[1] = (2.0f*M_PI)/360.0f*180.0f/M_PI;
	feedforwardParameters.b[2] = (2.0f*M_PI)/360.0f*180.0f/M_PI;
	feedforwardParameters.b[3] = (2.0f*M_PI)/360.0f*180.0f/M_PI;

	feedforwardParameters.c[0] = 60.0f*(M_PI/180.0f);
	feedforwardParameters.c[1] = -60.0f*(M_PI/180.0f);
	feedforwardParameters.c[2] = -135.0f*(M_PI/180.0f);
	feedforwardParameters.c[3] = 135.0f*(M_PI/180.0f);

	feedforwardParameters.param1[0] = 0.46;
	feedforwardParameters.param1[1] = 0.46;
	feedforwardParameters.param1[2] = 0.46;
	feedforwardParameters.param1[3] = 0.46;

	feedforwardParameters.param2[0] = 0.0360*180.0f/M_PI;
	feedforwardParameters.param2[1] = 0.0360*180.0f/M_PI;
	feedforwardParameters.param2[2] = 0.0350*180.0f/M_PI;
	feedforwardParameters.param2[3] = 0.0354*180.0f/M_PI;

	feedforwardParameters.param3[0] = -0.764611677882548;
	feedforwardParameters.param3[1] = -2.33703565345706;
	feedforwardParameters.param3[2] = -1.00311434719396;
	feedforwardParameters.param3[3] = 4.16457002728926;

	feedforwardParameters.param4[0] = 1.23;
	feedforwardParameters.param4[1] = 1.23;
	feedforwardParameters.param4[2] = 1.23;
	feedforwardParameters.param4[3] = 1.23;

	feedforwardParameters.rotation_feedforward_value[0] = 0.3f;
	feedforwardParameters.rotation_feedforward_value[1] = 0.3f;
	feedforwardParameters.rotation_feedforward_value[2] = 0.3f;
	feedforwardParameters.rotation_feedforward_value[3] = 0.3f;

	feedforwardParameters.identified_damping = 0.0375f;


	feedforwardParameters.vw_max_round_to_rotational_scaling = 1.0f;

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
	D[2] = rad_robot;
	D[3] = -cosFront;
	D[4] = sinFront;
	D[5] = rad_robot;
	D[6] = -cosBack;
	D[7] = -sinBack;
	D[8] = rad_robot;
	D[9] = cosBack;
	D[10] = -sinBack;
	D[11] = rad_robot;

	return 0;
}

int stateControl_DeInit(){
	status = off;
	HAL_TIM_Base_Stop_IT(TIM_CONTROL);
	return 0;
}

void stateControl_Update(){
	if (status == on){
		stateControl_Update_Body();
		wheels_Update();
	}	
}

void stateControl_Update_Body() {

	velocityControl(stateLocal, stateGlobalRef, wheelRef);

}

////////////// WHEELS CONTROL START

/**
 * @brief Updates the wheels towards the commanded wheel speeds using the encoders and a PID controller.
 * 
 * TODO : check OMEGAtoPWM values for new motor!!!
 * This function is resonsible for getting the wheels to the commanded speeds, as stored in the file-local variable
 * "wheelRef". Wheel speeds, given in rad/s, are converted directly to a PWM value with help of the
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

	body2Wheels(wheelRef, stateLocalRef); //translate velocity to wheel speed
	body2Wheels(wheelRefBodyScaled, stateLocalRefBodyScaled); //translate velocity to wheel speed
	
	float vu = stateLocalRef[vel_u];
	float vv = stateLocalRef[vel_v];
	float rho = sqrt(vu*vu + vv*vv);
	float theta_local = atan2(vv, vu);
	float omega = stateLocalRef[vel_w];

	float wheels_measured_speeds[4] = {0.0f};
	wheels_GetMeasuredSpeeds(wheels_measured_speeds);

	float feed_forward[4] = {0.0f};

	for (motor_id_t motor = RF; motor <= RB; motor++) {

		// Feedforward
			double wheel_speed_threshold = 0.5f;
			if (fabs(wheelRef[motor]) < wheel_speed_threshold) {
				feed_forward[motor] = 0;
				// Or should this be:
				// feed_forward[motor] = feedforwardMass(stateLocalRefAcceleration,motor);
			}
			else {
				feed_forward[motor] = wheelFFOn*(feedforwardParameters.identified_damping*wheelRef[motor] + feedforwardFriction(wheelRef[motor], rho, theta_local, omega, motor)) + massFFOn*feedforwardMass(stateLocalRefAcceleration,motor);
			}

		// Feedback
			// Calculate the velocity error
			float angular_velocity_error = wheelRefBodyScaled[motor] - wheels_measured_speeds[motor];
		
			// If the error is very small, ignore it (why is this here?)
			if (fabs(angular_velocity_error) < 0.1) {
				angular_velocity_error = 0.0f;
				wheelsK[motor].I = 0;
			}

			float feed_back_voltage = wheelFBOn*24.0f*(0.001367311 * (PID(angular_velocity_error, &wheelsK[motor])));
			float max_fb_voltage = 3.0f;
			if (feed_back_voltage > max_fb_voltage) {
				feed_back_voltage = max_fb_voltage;
			}
			else if (feed_back_voltage < -max_fb_voltage) {
				feed_back_voltage = -max_fb_voltage;
			}


		// Set motor PWM fraction/voltage
			float max_voltage = 7.5;
			// Add PID to commanded speed and convert to PWM (range between -1 and 1)
			float wheel_voltage_to_be_applied = feed_forward[motor] + feed_back_voltage;
			if (wheel_voltage_to_be_applied > max_voltage) {
				wheel_voltage_to_be_applied = max_voltage;
			}
			else if (wheel_voltage_to_be_applied < -max_voltage) {
				wheel_voltage_to_be_applied = -max_voltage;
			}
			wheel_speed_fraction[motor] = voltage2PWM(wheel_voltage_to_be_applied);
			wheels_SetSpeed_PWM(motor, wheel_speed_fraction[motor]);
	}
}

float voltage2PWM(float wheelVoltage){
	return wheelVoltage/powerVoltage.voltagePowerBoard;
}

/**
 * @brief Stores the commanded wheel speeds, in rad/s, to be used in the next wheels_Update() call
 * This function is the same as wheels_SetSpeeds from Microcontroller 5.0!!!
 * 
 * @param speeds float[4]{RF, LF, LB, RB} commanded wheels speeds, in rad/s. These values are stored in the file-local
 * variable 'wheelRef'. This variable will later be used in wheels_Update() to control the wheels.
 */
void wheels_set_command_speed(const float speeds[4]) {
	for(motor_id_t wheel = RF; wheel <= RB; wheel++){
		wheelRef[wheel] = speeds[wheel];
	}
}

/**
 * @brief Stops the wheels without deinitializing them 
 */
void wheels_Stop() {
	for (int motor = 0; motor < 4; motor++){
		wheels_SetSpeed_PWM(motor, 0);
		wheelRef[motor] = 0;
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

void wheels_GetPIDGains(float _gains[3]) {
	_gains[0] = wheelsK[0].kP;
	_gains[1] = wheelsK[0].kI;
	_gains[2] = wheelsK[0].kD;
}

///////////// WHEELS CONTROL END

void stateControl_SetRef(float _stateGlobalRef[4], float _stateGlobalRefAcceleration[3]){
	stateGlobalRef[vel_x] = _stateGlobalRef[vel_x];
	stateGlobalRef[vel_y] = _stateGlobalRef[vel_y];
	stateGlobalRef[vel_w] = _stateGlobalRef[vel_w];
	stateGlobalRef[yaw] = _stateGlobalRef[yaw];
	stateGlobalRefAcceleration[vel_x] = _stateGlobalRefAcceleration[vel_x];
	stateGlobalRefAcceleration[vel_y] = _stateGlobalRefAcceleration[vel_y];
	stateGlobalRefAcceleration[vel_w] = _stateGlobalRefAcceleration[vel_w];
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

float stateControl_GetWheelIntegral(wheel_names wheel) {
	return wheelsK[wheel].I;
}

float* stateControl_GetWheelRef() {
	return wheelRef;
}

float stateControl_GetIndividualWheelRef(wheel_names wheel) {
	return wheelRef[wheel];
}

float stateControl_GetBodyGlobalRef(robot_axes direction) {
	return stateGlobalRef[direction];
}

float stateControl_GetBodyControllerOutput(robot_axes direction) {
	return stateLocalRef[direction];
}

float stateControl_GetWheelControllerOutput(wheel_names wheel) {
	return wheel_speed_fraction[wheel];
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
	float threshold_REM_message = 95.0f;
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

		mass = PIDGains->unlabel1;
		inertia = PIDGains->unlabel2;

		// feedforwardParameters.a[0] = PIDGains->unlabel3;
		// feedforwardParameters.a[1] = PIDGains->unlabel3;
		// feedforwardParameters.a[2] = PIDGains->unlabel3;
		// feedforwardParameters.a[3] = PIDGains->unlabel3;

		// feedforwardParameters.d[0] = PIDGains->unlabel4;
		// feedforwardParameters.d[1] = PIDGains->unlabel4;
		// feedforwardParameters.d[2] = PIDGains->unlabel4;
		// feedforwardParameters.d[3] = PIDGains->unlabel4;

		feedforwardParameters.rotation_feedforward_value[0] = PIDGains->unlabel5;
		feedforwardParameters.rotation_feedforward_value[1] = PIDGains->unlabel5;
		feedforwardParameters.rotation_feedforward_value[2] = PIDGains->unlabel5;
		feedforwardParameters.rotation_feedforward_value[3] = PIDGains->unlabel5;

		feedforwardParameters.identified_damping = PIDGains->unlabel6;
		wheelFBOn = (int8_t) PIDGains->boolean1;
		wheelFFOn = (int8_t) PIDGains->boolean2;
		massFFOn = (int8_t) PIDGains->boolean3;
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

static float feedforwardMass(float stateLocalRefAcceleration[3], motor_id_t motor) {	
	float bodyForce[4] = {0.0f};
	float wheelForceDivRw[4] = {0.0f};
	float wheelForce[4] = {0.0f};
	float wheelTorque[4] = {0.0f};
	float motorCurrent[4] = {0.0f};
	float motorVoltage[4] = {0.0f};

	bodyForce[0] = mass*stateLocalRefAcceleration[0];
	bodyForce[1] = mass*stateLocalRefAcceleration[1];
	bodyForce[2] = inertia*stateLocalRefAcceleration[2]; // 0.0 because inertia is set to 0 for now. So no angular acceleration feedforward
	bodyForce[3] = 0.0f; // This is not used, it is just to have four inputs for body2wheels

	body2Wheels(wheelForceDivRw, bodyForce); //translate velocity to wheel speed

	wheelForce[motor] = wheelForceDivRw[motor] * rad_wheel;
	wheelTorque[motor] = wheelForce[motor] * rad_wheel;
	motorCurrent[motor] = wheelTorque[motor] / TORQUE_CONSTANT_MOTOR;
	motorVoltage[motor] = motorCurrent[motor] * RESISTANCE_MOTOR;
	return motorVoltage[motor];
}

static float sineEval(float x,float a,float b,float c) {
	float y = a*sinf(b*x+c);
	return y;
}

static float constEval(float x,float b,float c,float d) {
	float y_sign = sineEval(x,d,b,c);
	float y = 0.0f;
	if (y_sign>0) {
		y = d;
	} else {
		y = -d;
	}
	return y;
}

static float constsineEval(float x,float a,float b,float c,float d) {
	float y = sineEval(x,a,b,c) + constEval(x,b,c,d);
	return y;
}

static float detailedFitEval(float theta,float b,float c,float param1,float param2,float param3,float param4) {
	float y = 0.0f;
    float y_sign = sin(b*theta+c);
	if (y_sign >= 0) {
		y = param1*sin(param2*theta + param3) + param4;
	} else{
		y = -(param1*sin(param2*theta + param3) + param4);
	}
	return y;
}

static float feedforwardFriction(float wheelRef, float rho, float theta, float omega, wheel_names wheel) {
	
	bool detailedFit = true;

	// Calculations
	float vw_max_round_to_rotational = feedforwardParameters.vw_max_round_to_rotational_scaling*(rho/rad_robot);
	float z_rotational = feedforwardParameters.rotation_feedforward_value[wheel];
	
	// Calculate the feedforward voltage needed for purely translating
	float z_translation = 0.0f;
	if (detailedFit) {
		z_translation = detailedFitEval(theta,feedforwardParameters.b[wheel],feedforwardParameters.c[wheel],feedforwardParameters.param1[wheel],feedforwardParameters.param2[wheel],feedforwardParameters.param3[wheel],feedforwardParameters.param4[wheel]);
	}
	else {
		z_translation = constsineEval(theta,feedforwardParameters.a[wheel],feedforwardParameters.b[wheel],feedforwardParameters.c[wheel],feedforwardParameters.d[wheel]);
	}

	// Make sure the feedforward voltage is always applied along the desired rotational direction of the wheel
	int wheel_velocity_larger_than_zero;
	if(wheelRef > 0) {
		wheel_velocity_larger_than_zero = 1;
	}
	else {
		wheel_velocity_larger_than_zero = 0;
	}

	float z_rotational_fixed;
	float z_translation_fixed = z_translation;
	if(wheel_velocity_larger_than_zero == 1) {
		z_rotational_fixed = z_rotational;
		if(z_translation < 0) {
			if (detailedFit == true) {
				z_translation_fixed = feedforwardParameters.param4[wheel];
			}
			else {
				z_translation_fixed = feedforwardParameters.d[wheel];
			}
		}
	}
	else {
		z_rotational_fixed = -1*z_rotational;
		if(z_translation > 0) {
			if (detailedFit == true) {
				z_translation_fixed = -feedforwardParameters.param4[wheel];
			}
			else {
				z_translation_fixed = -feedforwardParameters.d[wheel];
			}
		}
	}

	// Define a smooth transition between translational and rotational feedforward gains.
	float gamma = 0.5-0.5*cos(M_PI * fabs(omega/vw_max_round_to_rotational));
	if (fabs(omega) > vw_max_round_to_rotational) {
		gamma = 1;
	}
	if (gamma > 1) {
		gamma = 1;
	}
	float feedforwardFrictionValue = ((1-gamma)*z_translation_fixed + gamma*z_rotational_fixed);
	return feedforwardFrictionValue;
}

static void body2Wheels(float wheelSpeed[4], float stateLocal[4]){

	// Translate the local u, v, and omega velocities into wheel velocities.
	wheelSpeed[wheels_RF] = stateLocal[vel_u] * D[0] + stateLocal[vel_v] * D[1]  + stateLocal[vel_w] * D[2];
	wheelSpeed[wheels_LF] = stateLocal[vel_u] * D[3] + stateLocal[vel_v] * D[4]  + stateLocal[vel_w] * D[5];
	wheelSpeed[wheels_LB] = stateLocal[vel_u] * D[6] + stateLocal[vel_v] * D[7]  + stateLocal[vel_w] * D[8];
	wheelSpeed[wheels_RB] = stateLocal[vel_u] * D[9] + stateLocal[vel_v] * D[10] + stateLocal[vel_w] * D[11];

	// Translate wheel velocities into angular velocities
	wheelSpeed[wheels_RF] = wheelSpeed[wheels_RF] / rad_wheel;
	wheelSpeed[wheels_LF] = wheelSpeed[wheels_LF] / rad_wheel;
	wheelSpeed[wheels_LB] = wheelSpeed[wheels_LB] / rad_wheel;
	wheelSpeed[wheels_RB] = wheelSpeed[wheels_RB] / rad_wheel;

}

static void global2Local(float global[4], float local[4], float yaw_angle, float stateGlobalRefAcceleration[3], float stateLocalRefAcceleration[3]){
	//trigonometry
	local[vel_u] = cosf(yaw_angle) * global[vel_x] + sinf(yaw_angle) * global[vel_y];
	local[vel_v] = -sinf(yaw_angle) * global[vel_x] + cosf(yaw_angle) * global[vel_y];
    local[vel_w] = global[vel_w];
	local[yaw] = global[yaw];
	stateLocalRefAcceleration[vel_u] = cosf(yaw_angle) * stateGlobalRefAcceleration[vel_x] + sinf(yaw_angle) * stateGlobalRefAcceleration[vel_y];
	stateLocalRefAcceleration[vel_v] = -sinf(yaw_angle) * stateGlobalRefAcceleration[vel_x] + cosf(yaw_angle) * stateGlobalRefAcceleration[vel_y];
	stateLocalRefAcceleration[vel_w] = stateGlobalRefAcceleration[vel_w];
}

static void velocityControl(float stateLocal[4], float stateGlobalRef[4], float velocityWheelRef[4]){
	global2Local(stateGlobalRef, stateLocalRef, stateLocal[yaw], stateGlobalRefAcceleration, stateLocalRefAcceleration); //transfer global to local

	// Local control
	float veluErr = (stateLocalRef[vel_u] - stateLocal[vel_u]);
	float velvErr = (stateLocalRef[vel_v] - stateLocal[vel_v]);
	float velwErr = (stateLocalRef[vel_w] - stateLocal[vel_w]);

	stateLocalRef[vel_u] = stateLocalRef[vel_u]/SLIPPAGE_FACTOR_U;
	stateLocalRef[vel_v] = stateLocalRef[vel_v]/SLIPPAGE_FACTOR_V;
	stateLocalRef[vel_w] = stateLocalRef[vel_w]/SLIPPAGE_FACTOR_W;

	stateLocalRefBodyScaled[vel_u] = stateLocalRef[vel_u] + PID(veluErr, &stateLocalK[vel_u]);
	stateLocalRefBodyScaled[vel_v] = stateLocalRef[vel_v] + PID(velvErr, &stateLocalK[vel_v]);
	stateLocalRefBodyScaled[vel_w] = stateLocalRef[vel_w] + PID(velwErr, &stateLocalK[vel_w]);
	
	// In case absolute angle control is used define the w (omega) differently based on absolute angle controller
	if (useAbsoluteAngle) {
		float angularRef = absoluteAngleControl(stateGlobalRef[yaw], stateLocal[yaw]);
		stateLocalRefBodyScaled[vel_w] = (rad_wheel/rad_robot)*angularRef;
    	stateLocalRef[vel_w] = (rad_wheel/rad_robot)*angularRef;
	}
	
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