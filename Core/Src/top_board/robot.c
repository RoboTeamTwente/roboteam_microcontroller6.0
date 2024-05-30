#include "robot.h"

/* ============================================================ */
/* ======================= VARIABLES ========================== */
/* ============================================================ */

/* Robot identity & mode */
uint8_t ROBOT_ID;
WIRELESS_CHANNEL ROBOT_CHANNEL;
volatile bool ROBOT_INITIALIZED = false;
bool TEST_MODE = false;
bool DISABLE_BUZZER = false;
bool unix_initalized = false;

/* IMU */

// How often should the IMU try to calibrate before the robot gives up? 
uint16_t MTi_MAX_INIT_ATTEMPTS = 5;
MTi_data* MTi; 

/* MCP */

//headers outgoing packets
CAN_TxHeaderTypeDef areYouAliveHeaderToPower = {0};
CAN_TxHeaderTypeDef areYouAliveHeaderToKicker = {0};
CAN_TxHeaderTypeDef areYouAliveHeaderToDribbler = {0};
CAN_TxHeaderTypeDef chipHeader = {0};
CAN_TxHeaderTypeDef kickHeader = {0};
CAN_TxHeaderTypeDef kickerChargeHeader = {0};
CAN_TxHeaderTypeDef kickerStopChargeHeader = {0};
CAN_TxHeaderTypeDef killHeader = {0};
CAN_TxHeaderTypeDef setDribblerSpeedHeader = {0};

//payload incoming packets
MCP_DribblerAlive dribblerAlive = {0};
MCP_KickerAlive kickerAlive = {0};
MCP_KickerCapacitorVoltage kickerCapacitorVoltage = {0};
MCP_PowerAlive powerAlive = {0};
MCP_PowerVoltage powerVoltage = {0};
MCP_SeesBall seesBall = {0};
MCP_DribblerEncoder dribblerEncoder = {0};

/* REM */

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
REM_SX1280Filler sx1280filler = {0};

REM_RobotCommand activeRobotCommand = {0};
float activeStateReference[3];

StateInfo stateInfo = {0.0f, false, {0.0f}, 0.0f, 0.0f, {0.0f}};

/* Watchdog timer */

IWDG_Handle* iwdg;

/* Counters, timers & heartbeats */

volatile uint32_t counter_loop = 0;
volatile uint32_t counter_htim6 = 0;
volatile uint32_t counter_TIM_CONTROL = 0;
volatile uint32_t counter_TIM_BUZZER = 0;
volatile uint32_t counter_TIM_SHOOT = 0;
volatile uint32_t counter_RobotCommand = 0;
volatile uint32_t counter_RobotBuzzer = 0;
uint8_t last_valid_RSSI = 0;
uint32_t timestamp_initialized = 0;
uint64_t unix_timestamp = 0;

uint32_t timestamp_last_packet_serial = 0;
uint32_t timestamp_last_packet_wireless = 0;
uint32_t timestamp_last_packet_xsens = 0;

uint32_t heartbeat_17ms_counter = 0;
uint32_t heartbeat_17ms = 0;
uint32_t heartbeat_100ms = 0;
uint32_t heartbeat_1000ms = 0;

/* flags and bools */

bool flag_send_PID_gains = false;
bool flag_sdcard_write_feedback = false;
bool flag_sdcard_write_command = false;
bool is_connected_serial = false;
bool is_connected_wireless = false;
bool is_connected_xsens = false;
bool halt = true;
bool xsens_CalibrationDone = false;
bool xsens_CalibrationDoneFirst = true;
volatile bool REM_last_packet_had_correct_version = true;
bool flag_PowerBoard_alive = false;
bool flag_DribblerBoard_alive = false;
bool flag_KickerBoard_alive = false;

/* SX data */
extern SX1280_Settings SX1280_DEFAULT_SETTINGS;
static Wireless SX1280 = {0};
static Wireless* SX = &SX1280;
static uint8_t SX_TX_buffer[MAX_PAYLOAD_SIZE + 3] __attribute__((aligned(4))) = {0};
static uint8_t SX_RX_buffer[MAX_PAYLOAD_SIZE + 3] __attribute__((aligned(4))) = {0};

static volatile Wireless_Packet txPacket;
static volatile Wireless_Packet rxPacket;

// The pins cannot be set at this point as they are not "const" enough for the compiler, so set them in the init
SX1280_Interface SX_Interface = {.SPI= COMM_SPI, .TXbuf= SX_TX_buffer, .RXbuf= SX_RX_buffer /*, .logger=LOG_printf*/,};



void updateTestCommand(REM_RobotCommand* rc, uint32_t time);
void check_otherboards(CAN_TxHeaderTypeDef board_header, bool *board_state, MCP_AreYouAlivePayload* board_payload);

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
	Wireless_SendPacket();
}

void Wireless_SendPacket() {
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

	if (txPacket.payloadLength < 6) {
		encodeREM_SX1280Filler( (REM_SX1280FillerPayload*) (txPacket.message + txPacket.payloadLength), &sx1280filler);
	}

	WritePacket_DMA(SX, &txPacket, &Wireless_Writepacket_Cplt);
}

void Wireless_Default(){
	if (!TEST_MODE) WaitForPacket(SX);
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
	stateReference[vel_x] = (robotCommand->rho) * cosf(robotCommand->theta);
	stateReference[vel_y] = (robotCommand->rho) * sinf(robotCommand->theta);
	stateReference[vel_w] = robotCommand->angularVelocity;
	stateReference[yaw] = robotCommand->angle;
	stateControl_SetRef(stateReference);

	MCP_SetDribblerSpeed sds = {0};
	sds.speed = robotCommand->dribbler;
	MCP_SetDribblerSpeedPayload sdsp = {0};
	encodeMCP_SetDribblerSpeed(&sdsp, &sds);
	MCP_Send_Message(&hcan1, sdsp.payload, setDribblerSpeedHeader, MCP_DRIBBLER_BOARD);
	
	if (seesBall.ballsensorSeesBall || robotCommand->doForce) {	
		if (robotCommand->doChip) {
			MCP_Chip chip = {0};
			chip.shootPower = robotCommand->kickChipPower;
			MCP_ChipPayload cp = {0};
			encodeMCP_Chip(&cp, &chip);
			MCP_Send_Message(&hcan1, cp.payload, chipHeader, MCP_KICKER_BOARD);
		} else if (robotCommand->doKick) {
			MCP_Kick kick = {0};
			kick.shootPower = robotCommand->kickChipPower;
			MCP_KickPayload kp = {0};
			encodeMCP_Kick(&kp, &kick);
			MCP_Send_Message(&hcan1, kp.payload, kickHeader, MCP_KICKER_BOARD);
		} else if (robotCommand->kickAtAngle) {
			float localState[4] = {0.0f};
			stateEstimation_GetState(localState);
			if (fabs(localState[yaw] - robotCommand->angle) < 0.025) {
				MCP_Kick kick = {0};
				kick.shootPower = robotCommand->kickChipPower;
				MCP_KickPayload kp = {0};
				encodeMCP_Kick(&kp, &kick);
				MCP_Send_Message(&hcan1, kp.payload, kickHeader, MCP_KICKER_BOARD);
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
void updateTestCommand(REM_RobotCommand* rc, uint32_t time){
	// First, empty the entire RobotCommand
	resetRobotCommand(rc);
	// Set the basic required stuff
	rc->header = REM_PACKET_TYPE_REM_ROBOT_COMMAND;
	rc->remVersion = REM_LOCAL_VERSION;
	rc->toRobotId = ROBOT_ID;

	uint32_t c_time = time - get_system_test_time_started();

	// Split up testing window into blocks of two seconds
	float period_fraction = (c_time%2000)/2000.f;

	// Rotate around, slowly
	rc->angularVelocity = 6 * (float) sin(period_fraction * 2 * M_PI);
	// Turn on dribbler
	rc->dribbler = period_fraction;
	// Kick a little every block
	if(0.95f < period_fraction){
		rc->doKick = true;
		rc->kickChipPower = 1;
		rc->doForce = true;
	}
}


/* ============================================================ */
/* ====================== MCP CALLBACKS ======================= */
/* ============================================================ */
void MCP_Process_Message(mailbox_buffer *to_Process) {
	if (ROBOT_INITIALIZED) toggle_Pin(LED7_pin);
	bool send_ack = true;
	switch (to_Process->message_id) {
		case MCP_PACKET_ID_POWER_TO_TOP_MCP_POWER_ALIVE: ;
			MCP_PowerAlivePayload* pap = (MCP_PowerAlivePayload*) to_Process->data_Frame;
			decodeMCP_PowerAlive(&powerAlive, pap);
			flag_PowerBoard_alive = true;
			send_ack = false;
			break;
		case MCP_PACKET_ID_DRIBBLER_TO_TOP_MCP_DRIBBLER_ALIVE: ;
			MCP_DribblerAlivePayload* dap = (MCP_DribblerAlivePayload*) to_Process->data_Frame;
			decodeMCP_DribblerAlive(&dribblerAlive, dap);
			flag_DribblerBoard_alive = true;
			send_ack = false;
			break;
		case MCP_PACKET_ID_KICKER_TO_TOP_MCP_KICKER_ALIVE: ;
			MCP_KickerAlivePayload* kap = (MCP_KickerAlivePayload*) to_Process->data_Frame;
			decodeMCP_KickerAlive(&kickerAlive, kap);
			flag_KickerBoard_alive = true;
			send_ack = false;
			break;
		case MCP_PACKET_ID_KICKER_TO_TOP_MCP_KICKER_CAPACITOR_VOLTAGE: ;
			MCP_KickerCapacitorVoltagePayload* kcvp = (MCP_KickerCapacitorVoltagePayload*) to_Process->data_Frame;
			decodeMCP_KickerCapacitorVoltage(&kickerCapacitorVoltage, kcvp);
			break;
		case MCP_PACKET_ID_POWER_TO_TOP_MCP_POWER_VOLTAGE: ;
			MCP_PowerVoltagePayload* pvp = (MCP_PowerVoltagePayload*) to_Process->data_Frame;
			decodeMCP_PowerVoltage(&powerVoltage, pvp);
			break;
		case MCP_PACKET_ID_DRIBBLER_TO_TOP_MCP_SEES_BALL: ;
			MCP_SeesBallPayload* spb = (MCP_SeesBallPayload*) to_Process->data_Frame;
			decodeMCP_SeesBall(&seesBall, spb);
			LOG_printf("Sees ball?");
			LOG_sendAll();
			break;		
	}

	if (send_ack) MCP_Send_Ack(&hcan1, to_Process->data_Frame[0], to_Process->message_id);

	LOG_sendAll();
	to_Process->empty = true;
	*to_Process->data_Frame  = 0;
	to_Process->message_id = 0;
}



/* ======================================================== */
/* ==================== INITIALIZATION ==================== */
/* ======================================================== */
void init(void){

	// Turn off all leds. Use leds to indicate init() progress
	set_Pin(LED0_pin, 0); set_Pin(LED1_pin, 0); set_Pin(LED2_pin, 0); set_Pin(LED3_pin, 0); set_Pin(LED4_pin, 0); set_Pin(LED5_pin, 0); set_Pin(LED6_pin, 0), set_Pin(LED7_pin, 0);
	
	// Initialize (and break) the wheels as soon as possible. This prevents wheels from randomly spinning when powering up the robot.
	int wheels_init_attemps = 0;
	Motor_StatusTypeDef all_wheels_initialized = MOTOR_NORESPONSE;
	while (all_wheels_initialized != MOTOR_OK &&wheels_init_attemps < 3) {
		all_wheels_initialized = wheels_Init();
		wheels_init_attemps++;
		HAL_Delay(10);
	}
	encoder_Init();

{ // ====== WATCHDOG TIMER, COMMUNICATION BUFFERS ON TOPBOARD, BATTERY, ROBOT SWITCHES, OUTGOING PACKET HEADERS
	/* Read robot ID (d), wireless channel (c), and if we're running a test (t), from the switches on the topboard
	* t x x c    d d d d 		<= swtiches
	* 7 6 5 4    3 2 1 0   		<= numbers below the switches
	*/
	ROBOT_ID = get_Id();
	ROBOT_CHANNEL = read_Pin(SW4_pin) == GPIO_PIN_SET ? BLUE_CHANNEL : YELLOW_CHANNEL;
	//UNDEFINED = read_Pin(SW5_pin);
	DISABLE_BUZZER = read_Pin(SW6_pin);
	TEST_MODE = read_Pin(SW7_pin);

	if (!TEST_MODE) {
		/* Enable the watchdog timer and set the threshold at 7.5 seconds. It should not be needed in the initialization but
		sometimes for some reason the code keeps hanging when powering up the robot using the power switch. It's not nice
		but its better than suddenly having non-responding robots in a match */
		IWDG_Init(iwdg, 7500);
	}
	
	
	initPacketHeader((REM_Packet*) &activeRobotCommand, ROBOT_ID, ROBOT_CHANNEL, REM_PACKET_TYPE_REM_ROBOT_COMMAND);
	initPacketHeader((REM_Packet*) &robotFeedback, ROBOT_ID, ROBOT_CHANNEL, REM_PACKET_TYPE_REM_ROBOT_FEEDBACK);
	initPacketHeader((REM_Packet*) &robotStateInfo, ROBOT_ID, ROBOT_CHANNEL, REM_PACKET_TYPE_REM_ROBOT_STATE_INFO);
 	initPacketHeader((REM_Packet*) &robotPIDGains, ROBOT_ID, ROBOT_CHANNEL, REM_PACKET_TYPE_REM_ROBOT_PIDGAINS);
	initPacketHeader((REM_Packet*) &robotLog, ROBOT_ID, ROBOT_CHANNEL, REM_PACKET_TYPE_REM_LOG);
	sx1280filler.header = REM_PACKET_INDEX_REM_SX1280FILLER;
	sx1280filler.remVersion = REM_LOCAL_VERSION;
	sx1280filler.fillerBits = 0;
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

	/* === Wired communication with robot; Can now receive RobotCommands (and other REM packets) via UART */
	REM_UARTinit(UART_PC);
}
	
	set_Pin(LED1_pin, 1);

{ // ====== INITIALIZE CONTROL CONSTANTS, STATE CONTROL, STATE ESTIMATION, OLED SCREEN
    // Initialize control constants
    control_util_Init();
	LOG("[init:"STRINGIZE(__LINE__)"] control_utils_Init step passed!\n");
    stateControl_Init();
    stateEstimation_Init();

	pages_init();
	SSD1306_Init(); // init oled
	OLED_Init();//start the menu

	HAL_Delay(300);

	if (all_wheels_initialized != MOTOR_OK) {
		buzzer_Play_WarningThree();
		HAL_Delay(1000);
	}

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
		// buzzer_Play(beep_blue); HAL_Delay(350);
	}else{
		Wireless_setChannel(SX, YELLOW_CHANNEL);
		LOG("[init:"STRINGIZE(__LINE__)"] YELLOW CHANNEL\n");
		// buzzer_Play(beep_yellow); HAL_Delay(350);
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

	/* 
	Check whether the MTi is already intialized.
	If the 3rd and 4th bit of the statusword are non-zero, then the initializion hasn't completed yet.
	*/
	while ((MTi == NULL || (MTi->statusword & (0x18)) != 0) && MTi_made_init_attempts < MTi_MAX_INIT_ATTEMPTS) {
		MTi = MTi_Init(1, XFP_VRU_general);
		if (!TEST_MODE) IWDG_Refresh(iwdg);


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
	} else {
		int maxCounts= 50;
		float averagedRateOfTurn = 0.0f;
		float rateOfTurn = 0.0f;
		float rotOffset;

		for (int counter = 0; counter < maxCounts; counter++){ // should run for maxCounts time steps (500 ms)
			rateOfTurn = MTi->gyr[2];
			averagedRateOfTurn += rateOfTurn/((float) maxCounts);
			HAL_Delay(10);
		}
		set_rotOffset(rotOffset);
		LOG_printf("[init:"STRINGIZE(__LINE__)"] RateOfRotation offset: %f\n", rotOffset);
	}
	LOG_sendAll();
}
	
	set_Pin(LED4_pin, 1);

{

	// Check if we are in test mode. If so, sound an alarm
	if(TEST_MODE) {
		LOG("[init:"STRINGIZE(__LINE__)"] In test mode! Flip pin SW7 and reboot to disable.\n");
		LOG_sendAll();
		buzzer_Play_BatteryDrainWarning();
		HAL_Delay(1000);
	}

}

	set_Pin(LED5_pin, 1);

	// Ensure that the speaker is stopped. The speaker keeps going even if the robot is reset
	speaker_Stop();

	// Play RobotID
	// buzzer_Play_ID(ROBOT_ID);
	// HAL_Delay(1500);


{	// ====== MCP =====
  	//initialize MCP
	MCP_Init(&hcan1, MCP_TOP_BOARD);
	LOG_printf("[init:"STRINGIZE(__LINE__)"] CAN VERSION: %d\n", MCP_LOCAL_VERSION);
	
	//initialize headers
	areYouAliveHeaderToPower = MCP_Initialize_Header(MCP_PACKET_TYPE_MCP_ARE_YOU_ALIVE, MCP_POWER_BOARD);
	areYouAliveHeaderToDribbler = MCP_Initialize_Header(MCP_PACKET_TYPE_MCP_ARE_YOU_ALIVE, MCP_DRIBBLER_BOARD);
	areYouAliveHeaderToKicker = MCP_Initialize_Header(MCP_PACKET_TYPE_MCP_ARE_YOU_ALIVE, MCP_KICKER_BOARD);
	chipHeader = MCP_Initialize_Header(MCP_PACKET_TYPE_MCP_CHIP, MCP_KICKER_BOARD);
	kickHeader = MCP_Initialize_Header(MCP_PACKET_TYPE_MCP_KICK, MCP_KICKER_BOARD);
	kickerChargeHeader = MCP_Initialize_Header(MCP_PACKET_TYPE_MCP_KICKER_CHARGE, MCP_KICKER_BOARD);
	kickerStopChargeHeader = MCP_Initialize_Header(MCP_PACKET_TYPE_MCP_KICKER_STOP_CHARGE, MCP_KICKER_BOARD);
	killHeader = MCP_Initialize_Header(MCP_PACKET_TYPE_MCP_KILL, MCP_POWER_BOARD);
	setDribblerSpeedHeader = MCP_Initialize_Header(MCP_PACKET_TYPE_MCP_SET_DRIBBLER_SPEED, MCP_DRIBBLER_BOARD);

	MCP_SetReadyToReceive(true);

	//check if communication with other boards is working
	MCP_AreYouAlive areYouAlive = {0};
	MCP_AreYouAlivePayload ayap = {0};
	encodeMCP_AreYouAlive(&ayap, &areYouAlive);

	check_otherboards(areYouAliveHeaderToPower, &flag_PowerBoard_alive, &ayap);
	if (!flag_PowerBoard_alive) LOG("[init:"STRINGIZE(__LINE__)"] Powerboard not alive\n");
	if (!TEST_MODE) {IWDG_Refresh(iwdg);}
	check_otherboards(areYouAliveHeaderToDribbler, &flag_DribblerBoard_alive, &ayap);
	if (!flag_DribblerBoard_alive) LOG("[init:"STRINGIZE(__LINE__)"] Dribblerboard not alive\n");
	if (!TEST_MODE) {IWDG_Refresh(iwdg);}
	check_otherboards(areYouAliveHeaderToKicker, &flag_KickerBoard_alive, &ayap);
	if (!flag_KickerBoard_alive) LOG("[init:"STRINGIZE(__LINE__)"] Kickerboard not alive\n");
	if (!TEST_MODE) {IWDG_Refresh(iwdg);}
	bool all_alive = flag_PowerBoard_alive && flag_DribblerBoard_alive && flag_KickerBoard_alive;
	if (!all_alive) {
		buzzer_Play_WarningFour();
		HAL_Delay(2000);
	}
	LOG_sendAll();
	end_of_boot_screen(all_alive);
	mcp_page_check_alive();
}
	
	set_Pin(LED6_pin, 1);

	LOG("[init:"STRINGIZE(__LINE__)"] Initialized\n");

	// Tell the SX to start listening for packets. This is non-blocking. It simply sets the SX into receiver mode.
	// SX1280 section 10.7 Transceiver Circuit Modes Graphical Illustration
	// Ignore packets when we're in test mode by simply never entering this receive-respond loop
	if(!TEST_MODE) WaitForPacket(SX);


	// Start timer TIM_1us
	HAL_TIM_Base_Start_IT(TIM_1us);

	/* Reset the watchdog timer and set the threshold at 250ms */
	if (!TEST_MODE) {
		IWDG_Refresh(iwdg);
		IWDG_Init(iwdg, 250);
	}

	/* Turn of all leds. Will now be used to indicate robot status */
	set_Pin(LED0_pin, 0); set_Pin(LED1_pin, 0); set_Pin(LED2_pin, 0); set_Pin(LED3_pin, 0); set_Pin(LED4_pin, 0); set_Pin(LED5_pin, 0); set_Pin(LED6_pin, 0), set_Pin(LED7_pin, 0);
	timestamp_initialized = HAL_GetTick();

	/* Start charging the kicker */
	MCP_KickerCharge kc = {0};
    MCP_KickerChargePayload kcp = {0};
    encodeMCP_KickerCharge(&kcp, &kc);
    MCP_Send_Message(&hcan1, &kcp, kickerChargeHeader, MCP_KICKER_BOARD);

	/* Set the heartbeat timers */
	heartbeat_17ms   = timestamp_initialized + 17;
	heartbeat_100ms  = timestamp_initialized + 100;
	heartbeat_1000ms = timestamp_initialized + 1000;
	
	ROBOT_INITIALIZED = true;
	buzzer_Play_Startup();

	// MCP_KickerCharge kc = {0};
	// MCP_KickerChargePayload kcp = {0};
	// encodeMCP_KickerCharge(&kcp, &kc);
	// MCP_Send_Message(&hcan1, &kcp, kickerChargeHeader, MCP_KICKER_BOARD);
}

uint8_t robot_get_ID() {
	return ROBOT_ID;
}

uint8_t robot_get_Channel() {
	return ROBOT_CHANNEL == YELLOW_CHANNEL ? 0 : 1;
}

void check_otherboards(CAN_TxHeaderTypeDef board_header, bool *board_state, MCP_AreYouAlivePayload* board_payload) {

	//We check if the board is alive three times, which means we send the message thrice
	uint8_t MAX_ATTEMPTS = 0;
	while (MAX_ATTEMPTS < 3 && *board_state == false) {
		MAX_ATTEMPTS++;
		MCP_Send_Message_Always(&hcan1, &board_payload, board_header);
		HAL_Delay(10);
		if (MCP_to_process){
			if (!MailBox_one.empty) MCP_Process_Message(&MailBox_one);
			if (!MailBox_two.empty) MCP_Process_Message(&MailBox_two);
			if (!MailBox_three.empty) MCP_Process_Message(&MailBox_three);
			MCP_to_process = false;
		}
	}
}



/* =================================================== */
/* ==================== MAIN LOOP ==================== */
/* =================================================== */
void loop(void){
    uint32_t current_time = HAL_GetTick();
    counter_loop++;

	OLED_Update(getRecentlyPressedButton(), TEST_MODE);

    /* Send anything in the log buffer over UART */
    LOG_send();

	/* CAN BUS RELATED PROCESS */
	if (MCP_to_process){
		if (!MailBox_one.empty) MCP_Process_Message(&MailBox_one);
		if (!MailBox_two.empty) MCP_Process_Message(&MailBox_two);
		if (!MailBox_three.empty) MCP_Process_Message(&MailBox_three);
		MCP_to_process = false;
	}

    // Check for connection to serial, wireless, and xsens
    // Cast to int32_t is needed since it might happen that current_time is smaller than time_last_packet_*
    // Not casting to int32 causes an overflow and thus a false negative
    is_connected_serial   = (int32_t)(current_time - timestamp_last_packet_serial)   < 250;
    is_connected_wireless = (int32_t)(current_time - timestamp_last_packet_wireless) < 250;
    is_connected_xsens    = (int32_t)(current_time - timestamp_last_packet_xsens)    < 250;

    // Refresh Watchdog timer
    if (!TEST_MODE) IWDG_Refresh(iwdg);

    /** MUSIC TEST CODE **/
    if(RobotMusicCommand_received_flag){
        RobotMusicCommand_received_flag = false;
        speaker_HandleCommand(&RobotMusicCommand);
    }

    /* === Determine HALT state === */
    xsens_CalibrationDone = (MTi->statusword & (0x18)) == 0; // if bits 3 and 4 of status word are zero, calibration is done
    halt = !xsens_CalibrationDone || !(is_connected_wireless || is_connected_serial) || !REM_last_packet_had_correct_version;
    if(get_system_test_running() || DRAIN_BATTERY) halt = false;

    if (halt) {
        // LOG_printf("HALT %d %d %d\n", xsens_CalibrationDone, checkWirelessConnection(), isSerialConnected);
        stateControl_ResetAngleI();
        resetRobotCommand(&activeRobotCommand);
        initPacketHeader((REM_Packet*) &activeRobotCommand, ROBOT_ID, ROBOT_CHANNEL, REM_PACKET_TYPE_REM_ROBOT_COMMAND);

        REM_last_packet_had_correct_version = true;
    }

    // Unbrake wheels when Xsens calibration is done
    if (xsens_CalibrationDoneFirst && xsens_CalibrationDone) {
        xsens_CalibrationDoneFirst = false;
        wheels_Unbrake();
    }

    // Update test (if active)
    // test_Update();

    // // Go through all commands if robot is not in HALT state or TEST_MODE
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

        if(system_test_running){
			// Test is running fine
			if (OLED_get_current_page_test_type() == NON_BLOCKING_TEST) {
				updateTestCommand(&activeRobotCommand, current_time - timestamp_initialized);
				flag_sdcard_write_command = true;
			} else { 
				// Test ended early so reset
				system_test_reset();
			}
        }

		if (TEST_MODE) {
			Wireless_SendPacket();
		}
    }	

    // Heartbeat every 100ms	
    if(heartbeat_100ms < current_time){
        while (heartbeat_100ms < current_time) heartbeat_100ms += 100;

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

		// Play warning if battery is getting low
		if (powerVoltage.voltagePowerBoard >= 18.0f && powerVoltage.voltagePowerBoard <= 22.0f) {
			if(!buzzer_IsPlaying()) {
				buzzer_Play_QuickBeepDown();
			}
		}

        // If the XSens isn't connected anymore, play a warning sound
        if(!is_connected_xsens){
			if(!buzzer_IsPlaying()) {
            	buzzer_Play_QuickBeepUp();
			}
        }

		// Play a warning if a REM packet with an incorrect version was received
		if(!REM_last_packet_had_correct_version) {
			if(!buzzer_IsPlaying()) {
				buzzer_Play_WarningTwo();
			}
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
    set_Pin(LED4_pin, seesBall.ballsensorSeesBall || seesBall.dribblerSeesBall);       // On when the dribbler detects the ball
	set_Pin(LED5_pin, SDCard_Initialized());		// On when SD card is initialized
	// LED6 Toggled when a REM packet is received
    // LED7 Wireless_Readpacket_Cplt : toggled when a MCP packet is received
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
	MCP_KillPayload kp = {0};
	MCP_Send_Message_Always(&hcan1, &kp, killHeader);
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
				LOG_printf("[REM Handler] Error! At %d of %d bytes. [Packet type] = %d\n", total_bytes_processed, packet_length, packet_header);
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
	}else if(GPIO_Pin == BTN_SW0_Pin) {
		calculateButtonTime(BUTTON_LEFT);
	}else if(GPIO_Pin == BTN_SW1_Pin) {
		calculateButtonTime(BUTTON_RIGHT);
	}else if(GPIO_Pin == BTN_SW2_Pin) {
		calculateButtonTime(BUTTON_DOWN);
	}else if(GPIO_Pin == BTN_SW3_Pin) {
		calculateButtonTime(BUTTON_OK);
	}else if(GPIO_Pin == BTN_SW4_Pin) {
		calculateButtonTime(BUTTON_UP);
	}
}

// Handles the interrupts of the different timers.
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    uint32_t current_time = HAL_GetTick();
    if(htim->Instance == TIM_CONTROL->Instance) {
		if(!ROBOT_INITIALIZED || OLED_get_current_page_test_type() == BLOCKING_TEST) return;

		if (!unix_initalized && activeRobotCommand.timestamp != 0){
			unix_timestamp = activeRobotCommand.timestamp;
			unix_initalized = true;
		}

		rem_page_add_timestamp(activeRobotCommand.timestamp);

		counter_TIM_CONTROL++;

		// State Info
		stateInfo.visionAvailable = activeRobotCommand.useCameraAngle;
		stateInfo.visionYaw = activeRobotCommand.cameraAngle; // TODO check if this is scaled properly with the new REM messages
		
		wheels_GetMeasuredSpeeds(stateInfo.wheelSpeeds);
		stateInfo.xsensAcc[vel_x] = MTi->acc[vel_x];
		stateInfo.xsensAcc[vel_y] = MTi->acc[vel_y];
		stateInfo.xsensYaw = (MTi->angles[2]*M_PI/180); //Gradients to Radians
		stateInfo.rateOfTurn = MTi->gyr[2];

		// State Estimation
		stateEstimation_Update(&stateInfo);

		if(halt || test_is_finished){
			unix_initalized = false;
			wheels_Stop();
			return;
		}

		if(is_connected_wireless && activeRobotCommand.useCameraAngle && !yaw_hasCalibratedOnce()) {
			wheels_Stop();
			return;
		}

		// State control
		float stateLocal[4] = {0.0f};
		stateEstimation_GetState(stateLocal);
		stateControl_SetState(stateLocal);
		stateControl_Update();

		float* refSpeedWheelsPointer;
		refSpeedWheelsPointer = stateControl_GetWheelRef();
		
		float* pointerGlobalBodyRef;
		pointerGlobalBodyRef = stateControl_GetBodyGlobalRef();

		if (!TEST_MODE || OLED_get_current_page_test_type() == NON_BLOCKING_TEST) {
		
			wheels_set_command_speed( stateControl_GetWheelRef() );

			// In order to drain the battery as fast as possible we instruct the wheels to go their maximum possible speeds.
			// However, for the sake of safety we make sure that if the robot actually turns it immediately stops doing this, since you
			// only want to execute this on a roll of tape.
			if(DRAIN_BATTERY){

				// TODO Instruct each wheel to go 30 rad/s
				float wheel_speeds[4] = {10.0f * M_PI, 10.0f * M_PI, 10.0f * M_PI, 10.0f * M_PI};
				wheels_set_command_speed(wheel_speeds);

				// If the gyroscope detects some rotational movement, we stop the drainage program.
				if (fabs(MTi->gyr[2]) > 0.3f) {
					end_of_test();
					DRAIN_BATTERY = false;
				}
			}
			wheels_Update();
		}

		/* == Fill robotFeedback packet == */ {
			robotFeedback.timestamp = unix_timestamp;
			robotFeedback.XsensCalibrated = xsens_CalibrationDone;
			robotFeedback.batteryLevel = powerVoltage.voltagePowerBoard;
			robotFeedback.ballSensorWorking = dribblerAlive.ballsensorWorking;
			robotFeedback.ballSensorSeesBall = seesBall.ballsensorSeesBall;
			// robotFeedback.ballPos = ballSensor_isInitialized() ? (-.5 + ballPosition.x / 700.) : 0;
			// robotFeedback.capacitor_voltage = kicker_capacitor_voltage;

			float localState[4] = {0.0f};
			stateEstimation_GetState(localState);
			float vu = localState[vel_u];
			float vv = localState[vel_v];
			robotFeedback.rho = sqrt(vu*vu + vv*vv);
			robotFeedback.angle = localState[yaw];
			robotFeedback.theta = atan2(vv, vu);
			robotFeedback.wheelBraking = wheels_GetWheelsBraking(); // TODO Locked feedback has to be changed to brake feedback in PC code
			robotFeedback.rssi = last_valid_RSSI; // Should be divided by two to get dBm but RSSI is 8 bits so just send all 8 bits back
			robotFeedback.dribblerSeesBall = seesBall.dribblerSeesBall;
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
			robotStateInfo.dribbleSpeed = dribblerEncoder.measuredSpeed;
			robotStateInfo.filteredDribbleSpeed = dribblerEncoder.filteredSpeed;
			robotStateInfo.dribblespeedBeforeGotBall = seesBall.dribblerSpeedBefore;
			robotStateInfo.bodyXIntegral = pointerGlobalBodyRef[vel_x]; // NEEDS TO BE CHANGED LATER ! since the name for those REM messages are not the correct ones!
			robotStateInfo.bodyYIntegral = pointerGlobalBodyRef[vel_y]; //
			robotStateInfo.bodyWIntegral = pointerGlobalBodyRef[vel_w]; //
			robotStateInfo.bodyYawIntegral = pointerGlobalBodyRef[yaw]; //
			robotStateInfo.wheel1Integral = refSpeedWheelsPointer[0]; // NEEDS TO BE CHANGED LATER ! since the name for those REM messages are not the correct ones!
			robotStateInfo.wheel2Integral = refSpeedWheelsPointer[1]; //
			robotStateInfo.wheel3Integral = refSpeedWheelsPointer[2]; //
			robotStateInfo.wheel4Integral = refSpeedWheelsPointer[3]; // 


			flag_sdcard_write_feedback = true;
			unix_timestamp += 1	;
		}
    }
    else if (htim->Instance == TIM_BUZZER->Instance) {
		counter_TIM_BUZZER++;
		buzzer_Callback();
	}
}


