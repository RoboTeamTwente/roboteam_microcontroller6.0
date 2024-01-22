#include "robot.h"

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

//StateInfo stateInfo = {0.0f, false, {0.0}, 0.0f, 0.0f, {0.0}};
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




/* ======================================================== */
/* ==================== INITIALIZATION ==================== */
/* ======================================================== */
void init(void){

	// Turn off all leds. Use leds to indicate init() progress
	set_Pin(LED0_pin, 0); set_Pin(LED1_pin, 0); set_Pin(LED2_pin, 0); set_Pin(LED3_pin, 0); set_Pin(LED4_pin, 0); set_Pin(LED5_pin, 0); set_Pin(LED6_pin, 0);
	
	// Initialize (and break) the wheels as soon as possible. This prevents wheels from randomly spinning when powering up the robot.
	// wheels_Init();

{ // ====== WATCHDOG TIMER, COMMUNICATION BUFFERS ON TOPBOARD, BATTERY, ROBOT SWITCHES, OUTGOING PACKET HEADERS
	/* Enable the watchdog timer and set the threshold at 5 seconds. It should not be needed in the initialization but
	 sometimes for some reason the code keeps hanging when powering up the robot using the power switch. It's not nice
	 but its better than suddenly having non-responding robots in a match */
	IWDG_Init(iwdg, 7500);
	
    /* Read robot ID (d), wireless channel (c), and if we're running a test (t), from the switches on the topboard
	* t c x x    d d d d 		<= swtiches
	* 7 6 5 4    3 2 1 0   		<= numbers below the switches
	*/
	ROBOT_ID = get_Id();
	ROBOT_CHANNEL = read_Pin(FT1_pin) == GPIO_PIN_SET ? BLUE_CHANNEL : YELLOW_CHANNEL;
	IS_RUNNING_TEST = read_Pin(FT0_pin);
	ENABLE_UART_PC = read_Pin(FT2_pin);
	DRAIN_BATTERY = read_Pin(FT3_pin);
	
	
	// initPacketHeader((REM_Packet*) &activeRobotCommand, ROBOT_ID, ROBOT_CHANNEL, REM_PACKET_TYPE_REM_ROBOT_COMMAND);
	// initPacketHeader((REM_Packet*) &robotFeedback, ROBOT_ID, ROBOT_CHANNEL, REM_PACKET_TYPE_REM_ROBOT_FEEDBACK);
	// initPacketHeader((REM_Packet*) &robotStateInfo, ROBOT_ID, ROBOT_CHANNEL, REM_PACKET_TYPE_REM_ROBOT_STATE_INFO);
 	// initPacketHeader((REM_Packet*) &robotPIDGains, ROBOT_ID, ROBOT_CHANNEL, REM_PACKET_TYPE_REM_ROBOT_PIDGAINS);
	// initPacketHeader((REM_Packet*) &robotLog, ROBOT_ID, ROBOT_CHANNEL, REM_PACKET_TYPE_REM_LOG);
	}

	set_Pin(LED0_pin, 1);

{ // ====== USER FEEDBACK (LOGGING, SDCARD, BUZZER, GIT BRANCH)
	//TODO double check
	// LOG_init();
	// LOG("[init:"STRINGIZE(__LINE__)"] Last programmed on " __DATE__ "\n");
	// LOG("[init:"STRINGIZE(__LINE__)"] GIT: " STRINGIZE(__GIT_STRING__) "\n");
	// LOG_printf("[init:"STRINGIZE(__LINE__)"] REM_LOCAL_VERSION: %d\n", REM_LOCAL_VERSION);
	// LOG_printf("[init:"STRINGIZE(__LINE__)"] ROBOT_ID: %d\n", ROBOT_ID);
	// LOG_sendAll();

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

{ // ====== INITIALIZE CONTROL CONSTANTS, STATE CONTROL, STATE ESTIMATION, OLED SCREEN
    // Initialize control constants
    // control_util_Init();
    // stateControl_Init();
    // stateEstimation_Init();

	SSD1306_Init(); // init oled
	menu_Init();//start the menu

	HAL_Delay(300);

	menu_SetVariableName(0, 0, "Motor");
	menu_SetVariableName(0, 1, "Encoder");
	menu_SetVariable(0, 0, 0);
	menu_SetVariable(0, 1, 0);


	// LOG_sendAll();
}

	set_Pin(LED2_pin, 1);

{ // ====== SX : PINS, CALLBACKS, CHANNEL, SYNCWORDS
	/* Initialize the SX1280 wireless chip */
	// SX1280_Settings set = SX1280_DEFAULT_SETTINGS;
	// set.periodBaseCount = WIRELESS_RX_COUNT;
	// Wireless_Error err;
	// SX_Interface.BusyPin = SX_BUSY_pin;
	// SX_Interface.CS = SX_NSS_pin;
	// SX_Interface.Reset = SX_RST_pin;
	// // err |= Wireless_setPrint_Callback(SX, LOG_prinstf);
    // err = Wireless_Init(SX, set, &SX_Interface);
    // if(err != WIRELESS_OK){ LOG("[init:"STRINGIZE(__LINE__)"] SX1280 error\n"); LOG_sendAll(); while(1); }
	// err = Wireless_setIRQ_Callbacks(SX, &SX_IRQcallbacks);
    // if(err != WIRELESS_OK){ LOG("[init:"STRINGIZE(__LINE__)"] SX1280 error\n"); LOG_sendAll(); while(1); }
	// LOG_sendAll();
	// // Use the pins on the topboard to determine the wireless frequency 
	// if(ROBOT_CHANNEL == BLUE_CHANNEL){
	// 	Wireless_setChannel(SX, BLUE_CHANNEL);
	// 	LOG("[init:"STRINGIZE(__LINE__)"] BLUE CHANNEL\n");
	// 	buzzer_Play(beep_blue); HAL_Delay(350);
	// }else{
	// 	Wireless_setChannel(SX, YELLOW_CHANNEL);
	// 	LOG("[init:"STRINGIZE(__LINE__)"] YELLOW CHANNEL\n");
	// 	buzzer_Play(beep_yellow); HAL_Delay(350);
	// }
	// LOG_sendAll();
    // // SX1280 section 7.3 FLRC : Syncword is 4 bytes at the beginning of each transmission, that ensures that only the right robot / basestation listens to that transmission.
	// Wireless_setTXSyncword(SX, robot_syncWord[16]); // TX syncword is set to the basestation its syncword
	// uint32_t syncwords[2] = {robot_syncWord[ROBOT_ID],0};
	// Wireless_setRXSyncwords(SX, syncwords); // RX syncword is specific for the robot its ID
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
		IWDG_Refresh(iwdg);

		if (MTi_made_init_attempts > 0) {
			LOG_printf("[init:"STRINGIZE(__LINE__)"] Failed to initialize MTi in attempt %d out of %d\n", MTi_made_init_attempts, MTi_MAX_INIT_ATTEMPTS);
		}
		MTi_made_init_attempts += 1;
		// LOG_sendAll();

		// The MTi is allowed to take 1 second per attempt. Hence we wait a bit more and then check again whether the initialization succeeded.
		HAL_Delay(1100);
	}

	// If after the maximum number of attempts the calibration still failed, play a warning sound... :(
	if (MTi == NULL || (MTi->statusword & (0x18)) != 0) {
		LOG_printf("[init:"STRINGIZE(__LINE__)"] Failed to initialize MTi after %d out of %d attempts\n", MTi_made_init_attempts, MTi_MAX_INIT_ATTEMPTS);
		buzzer_Play_WarningOne();
		HAL_Delay(1500); // The duration of the sound
	}
	// LOG_sendAll();
}
	
	set_Pin(LED4_pin, 1);

{
	LOG("[init:"STRINGIZE(__LINE__)"] Initialized\n");
	
	// Check if we are running a test. If so, sound an alarm
	if(IS_RUNNING_TEST){
		LOG("[init:"STRINGIZE(__LINE__)"] In test-mode! Flip pin FT0 and reboot to disable test-mode\n");
		// LOG_sendAll();
		for(uint8_t t = 0; t < 5; t++){
			buzzer_Play(warningRunningTest);
			HAL_Delay(400);
		}
		HAL_Delay(100);
	}

	// Check if we are draining the battery. If so, sound an alarm
	if(DRAIN_BATTERY) {
		LOG("[init:"STRINGIZE(__LINE__)"] In drain mode! Flip pin FT3 and reboot to disable.");
		// LOG_sendAll();
		buzzer_Play_BatteryDrainWarning();
		HAL_Delay(1000);
	}

}

	set_Pin(LED5_pin, 1);

	// Ensure that the speaker is stopped. The speaker keeps going even if the robot is reset
	speaker_Stop();

{	// ====== Check if communication if other boards is working

}
	set_Pin(LED6_pin, 1);

	// Tell the SX to start listening for packets. This is non-blocking. It simply sets the SX into receiver mode.
	// SX1280 section 10.7 Transceiver Circuit Modes Graphical Illustration
	// Ignore packets when we're in test- or battery drain mode by simply never entering this receive-respond loop
	// if(!(IS_RUNNING_TEST || DRAIN_BATTERY)) WaitForPacket(SX);


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

uint8_t robot_get_ID(){
	return ROBOT_ID;
}

uint8_t robot_get_Channel(){
	return ROBOT_CHANNEL == YELLOW_CHANNEL ? 0 : 1;
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

    // if (halt) {
    //     // LOG_printf("HALT %d %d %d\n", xsens_CalibrationDone, checkWirelessConnection(), isSerialConnected);
    //     // toggle_Pin(LED5_pin);
    //     stateControl_ResetAngleI();
    //     resetRobotCommand(&activeRobotCommand);
    //     initPacketHeader((REM_Packet*) &activeRobotCommand, ROBOT_ID, ROBOT_CHANNEL, REM_PACKET_TYPE_REM_ROBOT_COMMAND);
    //     // Quick fix to also stop the dribbler from rotating when the command is reset
    //     // TODO: maybe move executeCommand to TIMER_7?
    //     dribbler_SetSpeed(0);

    //     REM_last_packet_had_correct_version = true;
    // }

    // // Unbrake wheels when Xsens calibration is done
    // if (xsens_CalibrationDoneFirst && xsens_CalibrationDone) {
    //     xsens_CalibrationDoneFirst = false;
    //     wheels_Unbrake();
    // }

    // // Update test (if active)
    // // test_Update();

    // // Go through all commands if robot is not in HALT state
    // if (!halt) {
    //     executeCommands(&activeRobotCommand);
    // }

    // if(flag_sdcard_write_feedback){
    //     flag_sdcard_write_feedback = false;
    //     encodeREM_RobotFeedback( &robotFeedbackPayload, &robotFeedback );
    //     encodeREM_RobotStateInfo( &robotStateInfoPayload, &robotStateInfo);

    //     // Write to SD card
    //     SDCard_Write(robotFeedbackPayload.payload, REM_PACKET_SIZE_REM_ROBOT_FEEDBACK, true);
    //     SDCard_Write(robotStateInfoPayload.payload, REM_PACKET_SIZE_REM_ROBOT_STATE_INFO, false);
    // }
    // if(flag_sdcard_write_command){
    //     flag_sdcard_write_command = false;
    //     encodeREM_RobotCommand( &robotCommandPayload, &activeRobotCommand );
    //     SDCard_Write(robotCommandPayload.payload, REM_PACKET_SIZE_REM_ROBOT_COMMAND, false);
    // }

    // // Heartbeat every 17ms	
    // if(heartbeat_17ms < current_time){
    //     while (heartbeat_17ms < current_time) heartbeat_17ms += 17;

    //     if(IS_RUNNING_TEST){
    //         IS_RUNNING_TEST = updateTestCommand(&activeRobotCommand, current_time - timestamp_initialized);
    //         flag_sdcard_write_command = true;
    //     }
    // }	

    // Heartbeat every 100ms	
    if(heartbeat_100ms < current_time){
        while (heartbeat_100ms < current_time) heartbeat_100ms += 100;

        // Plays a sounds when the robot detects that it has a ball.
        static uint32_t played_dribbler_igotit = 0;
        // if(dribbler_GetHasBall() && played_dribbler_igotit < current_time){
        //     played_dribbler_igotit = current_time + 10000;
        //     speaker_Setvolume(30);
        //     HAL_Delay(10);
        //     speaker_PlayIndex(11);
        // }

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
            // buzzer_Play_QuickBeepUp();
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
    //set_Pin(LED2_pin, wheels_GetWheelsBraking());   // On when braking 
    set_Pin(LED3_pin, halt);						// On when halting
    //set_Pin(LED4_pin, dribbler_GetHasBall());       // On when the dribbler detects the ball
	set_Pin(LED5_pin, SDCard_Initialized());		// On when SD card is initialized
	// LED6 Toggled when a MCP packet is received
    // LED7 Wireless_Readpacket_Cplt : toggled when a REM packet is received
}

/* ========================================================= */
/* ==================== PACKET HANDLERS ==================== */
/* ========================================================= */




/* ============================================================ */
/* ===================== STM HAL CALLBACKS ==================== */
/* ============================================================ */

// Handles the interrupts of the different timers.
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    uint32_t current_time = HAL_GetTick();
    if(htim->Instance == TIM_CONTROL->Instance) {
        unix_timestamp += 1	;
    }
    else if (htim->Instance == TIM_BUZZER->Instance) {
		counter_TIM_BUZZER++;
		buzzer_Callback();
	}
}


