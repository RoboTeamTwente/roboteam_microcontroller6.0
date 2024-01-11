#include "main.h"
#include "robot.h"

#include "control_util.h"
#include "gpio_util.h"
#include "tim_util.h"
#include "peripheral_util.h"
#include "wheels.h"
#include "dribbler.h"
#include "stateControl.h"
#include "stateEstimation.h"
#include "dribbler.h"
#include "sdcard.h"
#include "shoot.h"
#include "Wireless.h"
#include "buzzer.h"
#include "speaker.h"
#include "MTi.h"
#include "yawCalibration.h"
#include "iwdg.h"
#include "ballsensor.h"
#include "testFunctions.h"
#include "logging.h"
#include "SX1280_Constants.h"
#include "AssuredPacketManager.h"

#include "rem.h"

#include "REM_Packet.h"
#include "REM_RobotCommand.h"
#include "REM_RobotFeedback.h"
#include "REM_RobotBuzzer.h"
#include "REM_RobotStateInfo.h"
#include "REM_RobotGetPIDGains.h"
#include "REM_RobotSetPIDGains.h"
#include "REM_RobotPIDGains.h"
#include "REM_SX1280Filler.h"
#include "REM_RobotMusicCommand.h"
#include "REM_Log.h"
#include "REM_RobotKillCommand.h"

#include <time.h>
#include <unistd.h>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

uint8_t ROBOT_ID;
WIRELESS_CHANNEL ROBOT_CHANNEL;

/* How often should the IMU try to calibrate before the robot gives up? */
uint16_t MTi_MAX_INIT_ATTEMPTS = 5;

/* Whether the robot should accept an uart connection from the PC */
volatile bool ENABLE_UART_PC = true;

volatile bool IS_RUNNING_TEST = false;
volatile bool ROBOT_INITIALIZED = false;
volatile bool DRAIN_BATTERY = false;

MTi_data* MTi;

// Incoming packets
REM_RobotCommandPayload robotCommandPayload = {0};
REM_RobotBuzzerPayload robotBuzzerPayload = {0};
REM_RobotMusicCommand RobotMusicCommand = {0};
volatile bool RobotMusicCommand_received_flag = false;
// Outgoing packets
REM_RobotFeedback robotFeedback = {0};
REM_RobotFeedbackPayload robotFeedbackPayload = {0};
REM_RobotStateInfo robotStateInfo = {0};
REM_RobotStateInfoPayload robotStateInfoPayload = {0};
REM_RobotPIDGains robotPIDGains = {0};
REM_RobotSetPIDGains robotSetPIDGains = {0};
REM_Log robotLog = {0};
REM_LogPayload robotLogPayload = {0};

REM_RobotCommand activeRobotCommand = {0};
float activeStateReference[3];

StateInfo stateInfo = {0.0f, false, {0.0}, 0.0f, 0.0f, {0.0}};
bool halt = true;
bool xsens_CalibrationDone = false;
bool xsens_CalibrationDoneFirst = true;
volatile bool REM_last_packet_had_correct_version = true;
IWDG_Handle* iwdg;

volatile uint32_t counter_loop = 0;
volatile uint32_t counter_htim6 = 0;
volatile uint32_t counter_TIM_CONTROL = 0;
volatile uint32_t counter_TIM_BUZZER = 0;
volatile uint32_t counter_TIM_SHOOT = 0;
volatile uint32_t counter_RobotCommand = 0;
volatile uint32_t counter_RobotBuzzer = 0;
uint32_t timestamp_initialized = 0;
uint64_t unix_timestamp = 0;
bool unix_initalized = false;

bool flag_send_PID_gains = false;
bool flag_sdcard_write_feedback = false;
bool flag_sdcard_write_command = false;
bool is_connected_serial = false;
bool is_connected_wireless = false;
bool is_connected_xsens = false;
uint8_t last_valid_RSSI = 0;
uint32_t timestamp_last_packet_serial = 0;
uint32_t timestamp_last_packet_wireless = 0;
uint32_t timestamp_last_packet_xsens = 0;

uint32_t heartbeat_17ms_counter = 0;
uint32_t heartbeat_17ms = 0;
uint32_t heartbeat_100ms = 0;
uint32_t heartbeat_1000ms = 0;

/* SX data */
// TODO: Maybe move all configs to its own file? (basestation_config.c/h???)
extern SX1280_Settings SX1280_DEFAULT_SETTINGS;
static Wireless SX1280 = {0};
static Wireless* SX = &SX1280;
static uint8_t SX_TX_buffer[MAX_PAYLOAD_SIZE + 3] __attribute__((aligned(4))) = {0};
static uint8_t SX_RX_buffer[MAX_PAYLOAD_SIZE + 3] __attribute__((aligned(4))) = {0};

static volatile Wireless_Packet txPacket;
static volatile Wireless_Packet rxPacket;

// The pins cannot be set at this point as they are not "const" enough for the compiler, so set them in the init
SX1280_Interface SX_Interface = {.SPI= COMM_SPI, .TXbuf= SX_TX_buffer, .RXbuf= SX_RX_buffer /*, .logger=LOG_printf*/,};





/* ============================================================ */
/* ==================== WIRELESS CALLBACKS ==================== */
/* ============================================================ */
void Wireless_Writepacket_Cplt(void){
	if(TransmitPacket(SX) != WIRELESS_OK)
		LOG("[Wireless_Writepacket_Cplt] TransmitPacket error!\n");
}
/**
 * @brief This function is called when a packet is read from the SX1280
 * 
 * When this callback function is called, it means that we just received a packet from the SX1280. According to the TDMA protocol that
 * we use, we now have 1 millisecond to send our feedback to the SX1280. Therefore, this function needs to be fast. Don't do 
 * any CPU intense stuff in here like matrix multiplications etc etc. This is also the reason that robotFeedback / robotStateInfo / etc
 * is being filled in the main loop, and not in this function; it saves time.
 */
void Wireless_Readpacket_Cplt(void){
	toggle_Pin(LED6_pin);
	timestamp_last_packet_wireless = HAL_GetTick();
	handlePacket(rxPacket.message, rxPacket.payloadLength);

	txPacket.payloadLength = 0;

	robotFeedback.messageId = activeRobotCommand.messageId;
	encodeREM_RobotFeedback( (REM_RobotFeedbackPayload*) (txPacket.message + txPacket.payloadLength), &robotFeedback);
	txPacket.payloadLength += REM_PACKET_SIZE_REM_ROBOT_FEEDBACK;

	encodeREM_RobotStateInfo( (REM_RobotStateInfoPayload*) (txPacket.message + txPacket.payloadLength), &robotStateInfo);
	txPacket.payloadLength += REM_PACKET_SIZE_REM_ROBOT_STATE_INFO;

	if(flag_send_PID_gains){
		encodeREM_RobotPIDGains( (REM_RobotPIDGainsPayload*) (txPacket.message + txPacket.payloadLength), &robotPIDGains);
		txPacket.payloadLength += REM_PACKET_SIZE_REM_ROBOT_PIDGAINS;
		flag_send_PID_gains = false;
	}

	// TODO insert REM_SX1280Filler packet if total_packet_length < 6. Fine for now since feedback is already more than 6 bytes
	WritePacket_DMA(SX, &txPacket, &Wireless_Writepacket_Cplt);
}

void Wireless_Default(){
	WaitForPacket(SX);
}

void Wireless_RXDone(SX1280_Packet_Status *status){
  /* It is possible that random noise can trigger the syncword.
   * Correct syncword from noise have a very weak signal.
   * Threshold is at -160/2 = -80 dBm. */
  if (status->RSSISync < 160) {
    ReadPacket_DMA(SX, &rxPacket, &Wireless_Readpacket_Cplt);
	last_valid_RSSI = status->RSSISync;
  }else{
	WaitForPacket(SX);
  }
}

Wireless_IRQcallbacks SX_IRQcallbacks = { .rxdone = &Wireless_RXDone, .default_callback = &Wireless_Default };

void executeCommands(REM_RobotCommand* robotCommand){
	stateControl_useAbsoluteAngle(robotCommand->useAbsoluteAngle);
	float stateReference[4];
	stateReference[vel_x] = (robotCommand->rho) * sinf(robotCommand->theta);
	stateReference[vel_y] = (robotCommand->rho) * cosf(robotCommand->theta);
	stateReference[vel_w] = robotCommand->angularVelocity;
	stateReference[yaw] = robotCommand->angle;
	stateControl_SetRef(stateReference);
	dribbler_SetSpeed(robotCommand->dribbler);
	shoot_SetPower(robotCommand->kickChipPower);

	if (robotCommand->doKick) {
		if (ballPosition.canKickBall || robotCommand->doForce){
			shoot_Shoot(shoot_Kick);
		}
	}
	else if (robotCommand->doChip) {
		if (ballPosition.canKickBall || robotCommand->doForce) {
			shoot_Shoot(shoot_Chip);
		}
	}
	else if (robotCommand->kickAtAngle) {
		float localState[4] = {0.0f};
		stateEstimation_GetState(localState);
		if (fabs(localState[yaw] - robotCommand->angle) < 0.025) {
			if (ballPosition.canKickBall || robotCommand->doForce) {
				shoot_Shoot(shoot_Kick);
			}
		}
	}
}

void resetRobotCommand(REM_RobotCommand* robotCommand){
	memset(robotCommand, 0, sizeof(REM_RobotCommand));
}

void initPacketHeader(REM_Packet* packet, uint8_t robot_id, uint8_t channel, uint8_t packet_type){
	packet->header = packet_type;
	packet->toPC = true;
	packet->fromColor = channel;
	packet->remVersion = REM_LOCAL_VERSION;
	packet->fromRobotId = robot_id;
	packet->payloadSize = REM_PACKET_TYPE_TO_SIZE(packet_type);
}


/**
 * @brief Function that fills a REM_RobotCommand with values for easy testing. After one
 * second, the robots starts rotating, dribbling, and kicking. After 10 seconds, the
 * robot stops.
 * 
 * @param rc The REM_RobotCommand to place the test commands into  
 * @param time The time in milliseconds indicating how far into test we are
 * @return true If the test is ongoing
 * @return false If the test is finished
 */
bool updateTestCommand(REM_RobotCommand* rc, uint32_t time){
	// First, empty the entire RobotCommand
	resetRobotCommand(rc);
	// Set the basic required stuff
	rc->header = REM_PACKET_TYPE_REM_ROBOT_COMMAND;
	rc->remVersion = REM_LOCAL_VERSION;
	rc->toRobotId = ROBOT_ID;

	// Don't do anything for the first second
	if(time < 1000) return true;
	// Don't do anything after 11 seconds
	if(11000 < time) return false;
	// These two give a test window of 10 seconds. 
	
	// Normalize time to 0 for easier calculations
	time -= 1000;

	// Split up testing window into blocks of two seconds
	float period_fraction = (time%2000)/2000.;

	// Rotate around, slowly
	rc->angularVelocity = 6 * sin(period_fraction * 2 * M_PI);
	// Turn on dribbler
	rc->dribbler = period_fraction;
	// Kick a little every block
	if(0.95 < period_fraction){
		rc->doKick = true;
		rc->kickChipPower = 1;
		rc->doForce = true;
	}

	return true;
}





/* ======================================================== */
/* ==================== INITIALIZATION ==================== */
/* ======================================================== */
void init(void){

	// Turn off all leds. Use leds to indicate init() progress
	set_Pin(LED0_pin, 0); set_Pin(LED1_pin, 0); set_Pin(LED2_pin, 0); set_Pin(LED3_pin, 0); set_Pin(LED4_pin, 0); set_Pin(LED5_pin, 0); set_Pin(LED6_pin, 0);
	
	// Initialize (and break) the wheels as soon as possible. This prevents wheels from randomly spinning when powering up the robot.
	wheels_Init();

{ // ====== WATCHDOG TIMER, COMMUNICATION BUFFERS ON TOPBOARD, BATTERY, ROBOT SWITCHES, OUTGOING PACKET HEADERS
	/* Enable the watchdog timer and set the threshold at 5 seconds. It should not be needed in the initialization but
	 sometimes for some reason the code keeps hanging when powering up the robot using the power switch. It's not nice
	 but its better than suddenly having non-responding robots in a match */
	IWDG_Init(iwdg, 7500);
		
	// Enable the I2C buffer (on the topboard, parts U500, U503).
	// These two buffers do communication with the ballsensor I2C, and the power monitor I2C + breakout I2C (shared bus)
	set_Pin(INT_EN_pin, 1); // HIGH == Buffers are turned on
	
	// Enable the four GPIO buffers (on the topboard, parts U501, U502, U800, and U801). 
	// These four buffers do communication with power meter GPIO pins, kill/shutdown signal, breakout UART,
	// kicker/chipper, dribbler (encoder + pwm), and ballsensor GPIO pins
	set_Pin(INT_ENneg_pin, 0); // LOW == Buffers are turned on

	// Set power circuit pin to HIGH, meaning on. When pulled again to LOW, it signals the power circuit to turn off, and power is then cut off instantly.
	// This pin must be set HIGH within a few milliseconds after powering on the robot, or it will turn the robot off again
	set_Pin(BAT_KILL_pin, 1);
	
	/* Read robot ID (d), wireless channel (c), and if we're running a test (t), from the switches on the topboard
	* d d d d    x x c t 		<= swtiches
	* 1 2 3 4    1 2 3 4   		<= numbers below the switches
	*/
	ROBOT_ID = get_Id();
	ROBOT_CHANNEL = read_Pin(FT1_pin) == GPIO_PIN_SET ? BLUE_CHANNEL : YELLOW_CHANNEL;
	IS_RUNNING_TEST = read_Pin(FT0_pin);
	ENABLE_UART_PC = read_Pin(FT2_pin);
	DRAIN_BATTERY = read_Pin(FT3_pin);
	
	
	initPacketHeader((REM_Packet*) &activeRobotCommand, ROBOT_ID, ROBOT_CHANNEL, REM_PACKET_TYPE_REM_ROBOT_COMMAND);
	initPacketHeader((REM_Packet*) &robotFeedback, ROBOT_ID, ROBOT_CHANNEL, REM_PACKET_TYPE_REM_ROBOT_FEEDBACK);
	initPacketHeader((REM_Packet*) &robotStateInfo, ROBOT_ID, ROBOT_CHANNEL, REM_PACKET_TYPE_REM_ROBOT_STATE_INFO);
 	initPacketHeader((REM_Packet*) &robotPIDGains, ROBOT_ID, ROBOT_CHANNEL, REM_PACKET_TYPE_REM_ROBOT_PIDGAINS);
	initPacketHeader((REM_Packet*) &robotLog, ROBOT_ID, ROBOT_CHANNEL, REM_PACKET_TYPE_REM_LOG);
	}

	set_Pin(LED0_pin, 1);

{ // ====== USER FEEDBACK (LOGGING, SDCARD, BUZZER, GIT BRANCH)
	LOG_init();
	LOG("[init:"STRINGIZE(__LINE__)"] Last programmed on " __DATE__ "\n");
	LOG("[init:"STRINGIZE(__LINE__)"] GIT: " STRINGIZE(__GIT_STRING__) "\n");
	LOG_printf("[init:"STRINGIZE(__LINE__)"] REM_LOCAL_VERSION: %d\n", REM_LOCAL_VERSION);
	LOG_printf("[init:"STRINGIZE(__LINE__)"] ROBOT_ID: %d\n", ROBOT_ID);
	LOG_sendAll();

	/* Initialize SD card */
	if(SDCard_Init()){
		LOG("[init:"STRINGIZE(__LINE__)"] SD card initialized\n");
	}else{
		LOG("[init:"STRINGIZE(__LINE__)"] SD card failed to initialize\n");
	}

	/* Initialize buzzer */
	buzzer_Init();
	buzzer_Play_QuickBeepUp();
	HAL_Delay(500); // The duration of the sound

	/* Play a warning sound if the robot is not programmed with the development branch */
	#ifdef __GIT_DEVELOPMENT__
	if(!__GIT_DEVELOPMENT__){
		buzzer_Play_WarningGit();
		HAL_Delay(600);
	}
	#endif

	// Sometimes the UART pin for the programmer is floating, causing the robot to not boot. 
	// As a temporary fix one can disable the uart initialization with the FT_2 switch on the robot.
	// TODO: This will need a proper fix later on.
	if (ENABLE_UART_PC) {
		/* === Wired communication with robot; Can now receive RobotCommands (and other REM packets) via UART */
		REM_UARTinit(UART_PC);
	}
}
	
	set_Pin(LED1_pin, 1);

{ // ====== INITIALIZE CONTROL CONSTANTS, STATE CONTROL, STATE ESTIMATION, SHOOTER, DRIBBLER, BALLSENSOR
    // Initialize control constants
    control_util_Init();
    stateControl_Init();
    stateEstimation_Init();
    shoot_Init();
    dribbler_Init();
	// TODO: Currently the ball sensor initialization is just disabled. 
	// Since we will no longer use it anymore this should be fully removed from the code.
    // if(ballSensor_Init()) LOG("[init:"STRINGIZE(__LINE__)"] Ballsensor initialized\n");	
	LOG_sendAll();
}

	set_Pin(LED2_pin, 1);

{ // ====== SX : PINS, CALLBACKS, CHANNEL, SYNCWORDS
	/* Initialize the SX1280 wireless chip */
	SX1280_Settings set = SX1280_DEFAULT_SETTINGS;
	set.periodBaseCount = WIRELESS_RX_COUNT;
	Wireless_Error err;
	SX_Interface.BusyPin = SX_BUSY_pin;
	SX_Interface.CS = SX_NSS_pin;
	SX_Interface.Reset = SX_RST_pin;
	// err |= Wireless_setPrint_Callback(SX, LOG_prinstf);
    err = Wireless_Init(SX, set, &SX_Interface);
    if(err != WIRELESS_OK){ LOG("[init:"STRINGIZE(__LINE__)"] SX1280 error\n"); LOG_sendAll(); while(1); }
	err = Wireless_setIRQ_Callbacks(SX, &SX_IRQcallbacks);
    if(err != WIRELESS_OK){ LOG("[init:"STRINGIZE(__LINE__)"] SX1280 error\n"); LOG_sendAll(); while(1); }
	LOG_sendAll();
	// Use the pins on the topboard to determine the wireless frequency 
	if(ROBOT_CHANNEL == BLUE_CHANNEL){
		Wireless_setChannel(SX, BLUE_CHANNEL);
		LOG("[init:"STRINGIZE(__LINE__)"] BLUE CHANNEL\n");
		buzzer_Play(beep_blue); HAL_Delay(350);
	}else{
		Wireless_setChannel(SX, YELLOW_CHANNEL);
		LOG("[init:"STRINGIZE(__LINE__)"] YELLOW CHANNEL\n");
		buzzer_Play(beep_yellow); HAL_Delay(350);
	}
	LOG_sendAll();
    // SX1280 section 7.3 FLRC : Syncword is 4 bytes at the beginning of each transmission, that ensures that only the right robot / basestation listens to that transmission.
	Wireless_setTXSyncword(SX, robot_syncWord[16]); // TX syncword is set to the basestation its syncword
	uint32_t syncwords[2] = {robot_syncWord[ROBOT_ID],0};
	Wireless_setRXSyncwords(SX, syncwords); // RX syncword is specific for the robot its ID
}

	set_Pin(LED3_pin, 1);

{ // ====== INITIALIZE IMU (XSENS). 1 second calibration time, XFP_VRU_general = no magnetometer */
	LOG("[init:"STRINGIZE(__LINE__)"] Initializing MTi\n");
	MTi = NULL;
	uint16_t MTi_made_init_attempts = 0;

	// Check whether the MTi is already intialized.
	// If the 3rd and 4th bit of the statusword are non-zero, then the initializion hasn't completed yet.
	while ((MTi == NULL || (MTi->statusword & (0x18)) != 0) && MTi_made_init_attempts < MTi_MAX_INIT_ATTEMPTS) {
		MTi = MTi_Init(1, XFP_VRU_general);
		IWDG_Refresh(iwdg);

		if (MTi_made_init_attempts > 0) {
			LOG_printf("[init:"STRINGIZE(__LINE__)"] Failed to initialize MTi in attempt %d out of %d\n", MTi_made_init_attempts, MTi_MAX_INIT_ATTEMPTS);
		}
		MTi_made_init_attempts += 1;
		LOG_sendAll();

		// The MTi is allowed to take 1 second per attempt. Hence we wait a bit more and then check again whether the initialization succeeded.
		HAL_Delay(1100);
	}

	// If after the maximum number of attempts the calibration still failed, play a warning sound... :(
	if (MTi == NULL || (MTi->statusword & (0x18)) != 0) {
		LOG_printf("[init:"STRINGIZE(__LINE__)"] Failed to initialize MTi after %d out of %d attempts\n", MTi_made_init_attempts, MTi_MAX_INIT_ATTEMPTS);
		buzzer_Play_WarningOne();
		HAL_Delay(1500); // The duration of the sound
	}
	LOG_sendAll();
}
	
	set_Pin(LED4_pin, 1);

	LOG("[init:"STRINGIZE(__LINE__)"] Initialized\n");
	
	// Check if we are running a test. If so, sound an alarm
	if(IS_RUNNING_TEST){
		LOG("[init:"STRINGIZE(__LINE__)"] In test-mode! Flip pin FT0 and reboot to disable test-mode\n");
		LOG_sendAll();
		for(uint8_t t = 0; t < 5; t++){
			buzzer_Play(warningRunningTest);
			HAL_Delay(400);
		}
		HAL_Delay(100);
	}

	// Check if we are draining the battery. If so, sound an alarm
	if(DRAIN_BATTERY) {
		LOG("[init:"STRINGIZE(__LINE__)"] In drain mode! Flip pin FT3 and reboot to disable.");
		LOG_sendAll();
		buzzer_Play_BatteryDrainWarning();
		HAL_Delay(1000);
	}

	set_Pin(LED5_pin, 1);

	// Tell the SX to start listening for packets. This is non-blocking. It simply sets the SX into receiver mode.
	// SX1280 section 10.7 Transceiver Circuit Modes Graphical Illustration
	// Ignore packets when we're in test- or battery drain mode by simply never entering this receive-respond loop
	if(!(IS_RUNNING_TEST || DRAIN_BATTERY)) WaitForPacket(SX);

	// Ensure that the speaker is stopped. The speaker keeps going even if the robot is reset
	speaker_Stop();

	// Start timer TIM_1us
	HAL_TIM_Base_Start_IT(TIM_1us);

	/* Reset the watchdog timer and set the threshold at 200ms */
	IWDG_Refresh(iwdg);
	IWDG_Init(iwdg, 1000);

	/* Turn of all leds. Will now be used to indicate robot status */
	set_Pin(LED0_pin, 0); set_Pin(LED1_pin, 0); set_Pin(LED2_pin, 0); set_Pin(LED3_pin, 0); set_Pin(LED4_pin, 0); set_Pin(LED5_pin, 0); set_Pin(LED6_pin, 0);
	buzzer_Play_ID(ROBOT_ID);

	timestamp_initialized = HAL_GetTick();

	/* Set the heartbeat timers */
	heartbeat_17ms   = timestamp_initialized + 17;
	heartbeat_100ms  = timestamp_initialized + 100;
	heartbeat_1000ms = timestamp_initialized + 1000;

	ROBOT_INITIALIZED = true;
}






/* =================================================== */
/* ==================== MAIN LOOP ==================== */
/* =================================================== */
void loop(void){
	uint32_t current_time = HAL_GetTick();
	counter_loop++;

	/* Send anything in the log buffer over UART */
	LOG_send();
	
	// Play a warning if a REM packet with an incorrect version was received
	if(!REM_last_packet_had_correct_version)
		if(!buzzer_IsPlaying())
			buzzer_Play_WarningTwo();

	// Check for connection to serial, wireless, and xsens
	// Cast to int32_t is needed since it might happen that current_time is smaller than time_last_packet_*
	// Not casting to int32 causes an overflow and thus a false negative
	is_connected_serial   = (int32_t)(current_time - timestamp_last_packet_serial)   < 250;
	is_connected_wireless = (int32_t)(current_time - timestamp_last_packet_wireless) < 250;
	is_connected_xsens    = (int32_t)(current_time - timestamp_last_packet_xsens)    < 250;
    
	// Refresh Watchdog timer
    IWDG_Refresh(iwdg);

	/** MUSIC TEST CODE **/
	if(RobotMusicCommand_received_flag){
		RobotMusicCommand_received_flag = false;
		speaker_HandleCommand(&RobotMusicCommand);
	}

	/* === Determine HALT state === */
    xsens_CalibrationDone = (MTi->statusword & (0x18)) == 0; // if bits 3 and 4 of status word are zero, calibration is done
    halt = !xsens_CalibrationDone || !(is_connected_wireless || is_connected_serial) || !REM_last_packet_had_correct_version;
	if(IS_RUNNING_TEST || DRAIN_BATTERY) halt = false;

	if (halt) {
		// LOG_printf("HALT %d %d %d\n", xsens_CalibrationDone, checkWirelessConnection(), isSerialConnected);
		// toggle_Pin(LED5_pin);
        stateControl_ResetAngleI();
        resetRobotCommand(&activeRobotCommand);
		initPacketHeader((REM_Packet*) &activeRobotCommand, ROBOT_ID, ROBOT_CHANNEL, REM_PACKET_TYPE_REM_ROBOT_COMMAND);
		// Quick fix to also stop the dribbler from rotating when the command is reset
		// TODO: maybe move executeCommand to TIMER_7?
		dribbler_SetSpeed(0);

		REM_last_packet_had_correct_version = true;
    }

    // Unbrake wheels when Xsens calibration is done
    if (xsens_CalibrationDoneFirst && xsens_CalibrationDone) {
        xsens_CalibrationDoneFirst = false;
        wheels_Unbrake();
    }

    // Update test (if active)
    // test_Update();
    
    // Go through all commands if robot is not in HALT state
    if (!halt) {
        executeCommands(&activeRobotCommand);
    }

	if(flag_sdcard_write_feedback){
		flag_sdcard_write_feedback = false;
		encodeREM_RobotFeedback( &robotFeedbackPayload, &robotFeedback );
		encodeREM_RobotStateInfo( &robotStateInfoPayload, &robotStateInfo);

		// Write to SD card
		SDCard_Write(robotFeedbackPayload.payload, REM_PACKET_SIZE_REM_ROBOT_FEEDBACK, true);
		SDCard_Write(robotStateInfoPayload.payload, REM_PACKET_SIZE_REM_ROBOT_STATE_INFO, false);
	}
	if(flag_sdcard_write_command){
		flag_sdcard_write_command = false;
		encodeREM_RobotCommand( &robotCommandPayload, &activeRobotCommand );
		SDCard_Write(robotCommandPayload.payload, REM_PACKET_SIZE_REM_ROBOT_COMMAND, false);
	}

    // Heartbeat every 17ms	
	if(heartbeat_17ms < current_time){
		while (heartbeat_17ms < current_time) heartbeat_17ms += 17;

		if(IS_RUNNING_TEST){
			IS_RUNNING_TEST = updateTestCommand(&activeRobotCommand, current_time - timestamp_initialized);
			flag_sdcard_write_command = true;
		}
	}	

    // Heartbeat every 100ms	
	if(heartbeat_100ms < current_time){
		while (heartbeat_100ms < current_time) heartbeat_100ms += 100;

		// Plays a sounds when the robot detects that it has a ball.
		static uint32_t played_dribbler_igotit = 0;
		if(dribbler_GetHasBall() && played_dribbler_igotit < current_time){
			played_dribbler_igotit = current_time + 10000;
			speaker_Setvolume(30);
			HAL_Delay(10);
			speaker_PlayIndex(11);
		}

		// Plays the id of the robot after boot-up.
		static bool played_id = false;
		if(!played_id && current_time > 500) {
			played_id = true;

			// Currently there are sounds for ids 1 up and till 11.
			if (ROBOT_ID > 0 && ROBOT_ID < 12) {
				speaker_Setvolume(30);
				HAL_Delay(10);
				speaker_SelectSong(0,ROBOT_ID);
			}
		}

		if(is_connected_serial){
			encodeREM_RobotFeedback( &robotFeedbackPayload, &robotFeedback );
			HAL_UART_Transmit(UART_PC, robotFeedbackPayload.payload, REM_PACKET_SIZE_REM_ROBOT_FEEDBACK, 10);

			encodeREM_RobotStateInfo( &robotStateInfoPayload, &robotStateInfo);
			HAL_UART_Transmit(UART_PC, robotStateInfoPayload.payload, REM_PACKET_SIZE_REM_ROBOT_STATE_INFO, 10);
		}
	}

	// Heartbeat every 1000ms
	if(heartbeat_1000ms < current_time){
		while (heartbeat_1000ms < current_time) heartbeat_1000ms += 1000;

		// If the XSens isn't connected anymore, play a warning sound
		if(!is_connected_xsens){
			buzzer_Play_QuickBeepUp();
		}

        // Toggle liveliness LED
        toggle_Pin(LED0_pin);

		// if (!isPlaying && 3000 < current_time){
		// 	isPlaying = true;
		// 	// Set volume to max (30)                 vv
		// 	uint8_t musicbuf1[5] = {0x7E, 0x03, 0x31, 30, 0xEF};
		// 	HAL_UART_Transmit(UART_BACK, musicbuf1, 5, 10);
		// 	HAL_Delay(50);
		// 	// Play song 10 (noo-noo)                       vv
		// 	uint8_t musicbuf2[6] = {0x7e, 0x04, 0x42, 0x01, 10, 0xef};
		// 	HAL_UART_Transmit(UART_BACK, musicbuf2, 6, 10);
		// }

    }

    /* LEDs for debugging */
    // LED0 : toggled every second while alive
    set_Pin(LED1_pin, !xsens_CalibrationDone);		// On while xsens startup calibration is not finished
    set_Pin(LED2_pin, wheels_GetWheelsBraking());   // On when braking 
    set_Pin(LED3_pin, halt);						// On when halting
    set_Pin(LED4_pin, dribbler_GetHasBall());       // On when the dribbler detects the ball
	set_Pin(LED5_pin, SDCard_Initialized());		// On when SD card is initialized
    // LED6 Wireless_Readpacket_Cplt : toggled when a packet is received
}

uint8_t robot_get_ID(){
	return ROBOT_ID;
}

uint8_t robot_get_Channel(){
	return ROBOT_CHANNEL == YELLOW_CHANNEL ? 0 : 1;
}





/* ========================================================= */
/* ==================== PACKET HANDLERS ==================== */
/* ========================================================= */

void handleRobotCommand(uint8_t* packet_buffer){
	memcpy(robotCommandPayload.payload, packet_buffer, REM_PACKET_SIZE_REM_ROBOT_COMMAND);
	REM_last_packet_had_correct_version &= REM_RobotCommand_get_remVersion(&robotCommandPayload) == REM_LOCAL_VERSION;
	decodeREM_RobotCommand(&activeRobotCommand,&robotCommandPayload);
	flag_sdcard_write_command = true;
}

void handleRobotBuzzer(uint8_t* packet_buffer){
	REM_RobotBuzzerPayload* rbp = (REM_RobotBuzzerPayload*) (packet_buffer);
	REM_last_packet_had_correct_version &= REM_RobotBuzzer_get_remVersion(rbp) == REM_LOCAL_VERSION;
	uint16_t period = REM_RobotBuzzer_get_period(rbp);
	float duration = REM_RobotBuzzer_get_duration(rbp);
	buzzer_Play_note(period, duration);
}

void handleRobotGetPIDGains(uint8_t* packet_buffer){
	REM_RobotGetPIDGainsPayload* rgpidgp = (REM_RobotGetPIDGainsPayload*) (packet_buffer);
	REM_last_packet_had_correct_version &= REM_RobotGetPIDGains_get_remVersion(rgpidgp) == REM_LOCAL_VERSION;
	flag_send_PID_gains = true;
}

void handleRobotSetPIDGains(uint8_t* packet_buffer){
	REM_RobotSetPIDGainsPayload* rspidgp = (REM_RobotSetPIDGainsPayload*) (packet_buffer);
	REM_last_packet_had_correct_version &= REM_RobotSetPIDGains_get_remVersion(rspidgp) == REM_LOCAL_VERSION;
	decodeREM_RobotSetPIDGains(&robotSetPIDGains, rspidgp);
	stateControl_SetPIDGains(&robotSetPIDGains);
	wheels_SetPIDGains(&robotSetPIDGains);
}

void handleRobotMusicCommand(uint8_t* packet_buffer){
	REM_RobotMusicCommandPayload* rmcp = (REM_RobotMusicCommandPayload*) (packet_buffer);
	REM_last_packet_had_correct_version &= REM_RobotMusicCommand_get_remVersion(rmcp) == REM_LOCAL_VERSION;
	robot_setRobotMusicCommandPayload(rmcp);
}

void handleRobotKillCommand(){
	set_Pin(BAT_KILL_pin, 0);
}

void robot_setRobotCommandPayload(REM_RobotCommandPayload* rcp){
	decodeREM_RobotCommand(&activeRobotCommand, rcp);
	timestamp_last_packet_serial = HAL_GetTick();
	flag_sdcard_write_command = true;
}

void robot_setRobotMusicCommandPayload(REM_RobotMusicCommandPayload* mcp){
	decodeREM_RobotMusicCommand(&RobotMusicCommand, mcp);
	RobotMusicCommand_received_flag = true;
}

bool handlePacket(uint8_t* packet_buffer, uint8_t packet_length){
	uint8_t total_bytes_processed = 0;
	uint8_t packet_header;

	while(total_bytes_processed < packet_length){

		packet_header = packet_buffer[total_bytes_processed];
		
		switch(packet_header){

			case REM_PACKET_TYPE_REM_ROBOT_COMMAND:
				handleRobotCommand(packet_buffer + total_bytes_processed);
				total_bytes_processed += REM_PACKET_SIZE_REM_ROBOT_COMMAND;
				break;

			case REM_PACKET_TYPE_REM_ROBOT_BUZZER: 
				handleRobotBuzzer(packet_buffer + total_bytes_processed);
				total_bytes_processed += REM_PACKET_SIZE_REM_ROBOT_BUZZER;
				break;
			
			case REM_PACKET_TYPE_REM_ROBOT_GET_PIDGAINS:
				handleRobotGetPIDGains(packet_buffer + total_bytes_processed);
				total_bytes_processed += REM_PACKET_SIZE_REM_ROBOT_GET_PIDGAINS;
				break;
			
			case REM_PACKET_TYPE_REM_ROBOT_SET_PIDGAINS:
				handleRobotSetPIDGains(packet_buffer + total_bytes_processed);
				total_bytes_processed += REM_PACKET_SIZE_REM_ROBOT_SET_PIDGAINS;
				break;

			case REM_PACKET_TYPE_REM_ROBOT_MUSIC_COMMAND:
				handleRobotMusicCommand(packet_buffer + total_bytes_processed);
				total_bytes_processed += REM_PACKET_SIZE_REM_ROBOT_MUSIC_COMMAND;
				break;

			case REM_PACKET_TYPE_REM_SX1280FILLER:
				total_bytes_processed += REM_PACKET_SIZE_REM_SX1280FILLER;
				break;

			case REM_PACKET_TYPE_REM_ROBOT_KILL_COMMAND:
				handleRobotKillCommand();
				total_bytes_processed += REM_PACKET_TYPE_REM_ROBOT_KILL_COMMAND;
				break;


			default:
				LOG_printf("[SPI_TxRxCplt] Error! At %d of %d bytes. [@] = %d\n", total_bytes_processed, packet_length, packet_header);
				return false;
		}
	}

	return true;
}





/* ============================================================ */
/* ===================== STM HAL CALLBACKS ==================== */
/* ============================================================ */
/* HAL_SPI_TxRxCpltCallback = Callback for either SPI Transmit or Receive complete */
/* This function is triggered after calling HAL_SPI_TransmitReceive_IT */
/* Since we transmit everything using blocking mode, this function should only be called when we receive something */
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef* hspi){

	// If we received data from the SX1280
	if(hspi->Instance == SX->Interface->SPI->Instance) {
		Wireless_DMA_Handler(SX);
	}

	// If we received data from the XSens
	else if(/*MTi != NULL &&*/ hspi->Instance == MTi->SPI->Instance){
		timestamp_last_packet_xsens = HAL_GetTick();
		MTi_SPI_RxCpltCallback(MTi);
	}
}

/* Callback for when bytes have been received via the UART */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == UART_PC->Instance){
		REM_UARTCallback(huart);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == SX_IRQ_pin.PIN) {
		Wireless_IRQ_Handler(SX);
	}else if(GPIO_Pin == MTi_IRQ_pin.PIN){
		MTi_IRQ_Handler(MTi);
	}else if (GPIO_Pin == BS_IRQ_pin.PIN){
		ballSensor_IRQ_Handler();
	}
}

// Handles the interrupts of the different timers.
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	uint32_t current_time = HAL_GetTick();

	if(htim->Instance == TIM_CONTROL->Instance) {
		if(!ROBOT_INITIALIZED) return;

		if (!unix_initalized && activeRobotCommand.timestamp != 0){
			unix_timestamp = activeRobotCommand.timestamp;
			unix_initalized = true;
		}

		counter_TIM_CONTROL++;

		// Update the dribbler at 10Hz
		if(counter_TIM_CONTROL % 10	== 0) {
			dribbler_Update();
			dribbler_CalculateHasBall();
		}

		/* Enable this code to make the robot turn slowly */
		// float speeds[4] = {8., 8., 8., 8.};
		// wheels_Unbrake();
		// wheels_SetSpeeds(speeds);
		// wheels_Update();
		// return;

		// State estimation		
		stateInfo.visionAvailable = activeRobotCommand.useCameraAngle;
		stateInfo.visionYaw = activeRobotCommand.cameraAngle; // TODO check if this is scaled properly with the new REM messages
		
		wheels_GetMeasuredSpeeds(stateInfo.wheelSpeeds);
		stateInfo.xsensAcc[vel_x] = MTi->acc[vel_x];
		stateInfo.xsensAcc[vel_y] = MTi->acc[vel_y];
		stateInfo.xsensYaw = (MTi->angles[2]*M_PI/180); //Gradients to Radians
		stateInfo.rateOfTurn = MTi->gyr[2];
		stateEstimation_Update(&stateInfo);

		if(test_isTestRunning(wheels) || test_isTestRunning(normal)) {
            wheels_Update();
            return;
        }

		if( halt && !test_isTestRunning(square)){
			wheels_Stop();
			return;
		}

		// State control
		float stateLocal[4] = {0.0f};
		stateEstimation_GetState(stateLocal);
		stateControl_SetState(stateLocal);
		stateControl_Update();

		wheels_SetSpeeds( stateControl_GetWheelRef() );

		// In order to drain the battery as fast as possible we instruct the wheels to go their maximum possible speeds.
		// However, for the sake of safety we make sure that if the robot actually turns it immediately stops doing this, since you
		// only want to execute this on a roll of tape.
		//
		// TODO: Once the battery meter has been implemented in software, it would perhaps be nice to stop the drainaige at programmable level.
		//       Currently you are stuck on the automated shutdown value that is controlled by the powerboard.
		if(DRAIN_BATTERY){

			// Instruct each wheel to go 30 rad/s
			float wheel_speeds[4] = {30.0f * M_PI, 30.0f * M_PI, 30.0f * M_PI, 30.0f * M_PI};
			wheels_SetSpeeds(wheel_speeds);

			// If the gyroscope detects some rotational movement, we stop the drainage program.
			if (fabs(MTi->gyr[2]) > 0.3f) {
				DRAIN_BATTERY = false;
			}
		}
		wheels_Update();

		/* == Fill robotFeedback packet == */ {
			robotFeedback.timestamp = unix_timestamp;
			robotFeedback.XsensCalibrated = xsens_CalibrationDone;
			// robotFeedback.batteryLevel = (batCounter > 1000);
			robotFeedback.ballSensorWorking = ballSensor_isInitialized();
			robotFeedback.ballSensorSeesBall = ballPosition.canKickBall;
			robotFeedback.ballPos = ballSensor_isInitialized() ? (-.5 + ballPosition.x / 700.) : 0;

			float localState[4] = {0.0f};
			stateEstimation_GetState(localState);
			float vu = localState[vel_u];
			float vv = localState[vel_v];
			robotFeedback.rho = sqrt(vu*vu + vv*vv);
			robotFeedback.angle = localState[yaw];
			robotFeedback.theta = atan2(vu, vv);
			robotFeedback.wheelBraking = wheels_GetWheelsBraking(); // TODO Locked feedback has to be changed to brake feedback in PC code
			robotFeedback.rssi = last_valid_RSSI; // Should be divided by two to get dBm but RSSI is 8 bits so just send all 8 bits back
			robotFeedback.dribblerSeesBall = dribbler_GetHasBall();
		}
		
		/* == Fill robotStateInfo packet == */ {	
			robotStateInfo.timestamp = unix_timestamp;
			robotStateInfo.xsensAcc1 = stateInfo.xsensAcc[0];
			robotStateInfo.xsensAcc2 = stateInfo.xsensAcc[1];
			robotStateInfo.xsensYaw = yaw_GetCalibratedYaw();
			robotStateInfo.rateOfTurn = stateEstimation_GetFilteredRoT();
			robotStateInfo.wheelSpeed1 = stateInfo.wheelSpeeds[0];
			robotStateInfo.wheelSpeed2 = stateInfo.wheelSpeeds[1];
			robotStateInfo.wheelSpeed3 = stateInfo.wheelSpeeds[2];
			robotStateInfo.wheelSpeed4 = stateInfo.wheelSpeeds[3];
			robotStateInfo.dribbleSpeed = dribbler_GetMeasuredSpeeds();
			robotStateInfo.filteredDribbleSpeed = dribbler_GetFilteredSpeeds();
			robotStateInfo.dribblespeedBeforeGotBall = dribbler_GetSpeedBeforeGotBall();
			robotStateInfo.bodyXIntegral = stateControl_GetIntegral(vel_x);
			robotStateInfo.bodyYIntegral = stateControl_GetIntegral(vel_y);
			robotStateInfo.bodyWIntegral = stateControl_GetIntegral(vel_w);
			robotStateInfo.bodyYawIntegral = stateControl_GetIntegral(yaw);
		}

		flag_sdcard_write_feedback = true;

	}
	else if (htim->Instance == TIM_BUZZER->Instance) {
		counter_TIM_BUZZER++;
		buzzer_Callback();
	}

	else if (htim->Instance == TIM_SHOOT->Instance) {
		counter_TIM_SHOOT++;
		shoot_Callback();
	}

	unix_timestamp += 1	;
}
