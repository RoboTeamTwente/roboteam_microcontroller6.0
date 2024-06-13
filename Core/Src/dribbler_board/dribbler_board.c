#include "dribbler_board.h"

volatile bool BOARD_INITIALIZED = false;

void MCP_Process_Message(mailbox_buffer *to_Process);
void MCP_Send_Im_Alive();

// Outgoing MCP headers
CAN_TxHeaderTypeDef dribblerAliveHeaderToTop = {0};
CAN_TxHeaderTypeDef dribblerAliveHeaderToPower = {0};
CAN_TxHeaderTypeDef dribblerAliveHeaderToKicker = {0};
CAN_TxHeaderTypeDef dribblerEncoderHeader = {0};
CAN_TxHeaderTypeDef seesBallHeaderToTop = {0};
CAN_TxHeaderTypeDef seesBallHeaderToKicker = {0};

// Outgoing MCP 
MCP_SeesBall mcp_seesBall = {0};
MCP_DribblerEncoder mcp_encoder = {0};

// Incoming MCP
MCP_PowerVoltage mcp_power = {0};
MCP_DribblerCommand dribblerCommand = {0};

/* ====================================================================== */    
/* ====================== CAN RELEATED VARIABLES ======================== */    
/* ====================================================================== */    

// These values are sent to the top board, depending on weither the ballsensor or dribbler detects the ball
bool dribbler_state;
bool ballsensor_state;
static bool sendSeesBall = false;

// Checks for how long we lost the ball
uint8_t ball_counter = 0;

// Heart Beats
uint32_t current_beat = 0;
uint32_t heart_beat_10ms = 0;


/* ======================================================== */
/* ==================== INITIALIZATION ==================== */
/* ======================================================== */
void init(){
    HAL_IWDG_Refresh(&hiwdg);
    // Peripherals
    dribbler_Init();
    ballsensor_init();
    ball_counter = 250; // making sure that the dribbler doesn't spin on bootup

    //MCP
    MCP_Init(&hcan, MCP_DRIBBLER_BOARD);
    dribblerAliveHeaderToTop = MCP_Initialize_Header(MCP_PACKET_TYPE_MCP_DRIBBLER_ALIVE, MCP_TOP_BOARD);
    dribblerAliveHeaderToKicker = MCP_Initialize_Header(MCP_PACKET_TYPE_MCP_DRIBBLER_ALIVE, MCP_KICKER_BOARD);
    dribblerAliveHeaderToPower = MCP_Initialize_Header(MCP_PACKET_TYPE_MCP_DRIBBLER_ALIVE, MCP_POWER_BOARD);
    dribblerEncoderHeader = MCP_Initialize_Header(MCP_PACKET_TYPE_MCP_DRIBBLER_ENCODER, MCP_TOP_BOARD);
    seesBallHeaderToTop = MCP_Initialize_Header(MCP_PACKET_TYPE_MCP_SEES_BALL, MCP_TOP_BOARD);
    seesBallHeaderToKicker = MCP_Initialize_Header(MCP_PACKET_TYPE_MCP_SEES_BALL, MCP_KICKER_BOARD);

    // MCP Alive
    MCP_SetReadyToReceive(true);
	MCP_Send_Im_Alive();
    
    BOARD_INITIALIZED = true;
    HAL_IWDG_Refresh(&hiwdg);
}

uint8_t robot_get_ID(){
  return 0;
}

uint8_t robot_get_Channel(){
  return 0;
}

/* =================================================== */
/* ==================== MAIN LOOP ==================== */
/* =================================================== */
void loop(){
    HAL_IWDG_Refresh(&hiwdg);
    MCP_timeout();
    if (MCP_to_process){
        if (!MailBox_one.empty)
            MCP_Process_Message(&MailBox_one);
        if (!MailBox_two.empty)
            MCP_Process_Message(&MailBox_two);
        if (!MailBox_three.empty)
            MCP_Process_Message(&MailBox_three);
        MCP_to_process = false;
	}
}

/* ============================================= */
/* ==================== MCP ==================== */
/* ============================================= */
void MCP_Process_Message(mailbox_buffer *to_Process){
    bool send_ack = true;

    if (to_Process->message_id == MCP_PACKET_ID_TOP_TO_DRIBBLER_MCP_ARE_YOU_ALIVE) {
        MCP_Send_Im_Alive();
		send_ack = false;
    } else if (to_Process->message_id == MCP_PACKET_ID_TOP_TO_DRIBBLER_MCP_DRIBBLER_COMMAND) {
        MCP_DribblerCommandPayload* dcp = (MCP_DribblerCommandPayload*) to_Process->data_Frame;
        decodeMCP_DribblerCommand(&dribblerCommand, dcp);
    } else if (to_Process->message_id == MCP_PACKET_ID_TOP_TO_KICKER_MCP_REBOOT) {
        HAL_Delay(1000);
    }

    if (send_ack) MCP_Send_Ack(&hcan, to_Process->data_Frame[0], to_Process->message_id);
	
	to_Process->empty = true;
	*to_Process->data_Frame  = 0;
	to_Process->message_id = 0;
}

void MCP_Send_Im_Alive() {
    MCP_DribblerAlive da = {0};
    MCP_DribblerAlivePayload dap = {0};
    da.ballsensorWorking = ballSensor_isWorking;
    da.dribblerEncoderWorking = false;
    encodeMCP_DribblerAlive(&dap, &da);
    MCP_Send_Message_Always(&hcan, dap.payload, dribblerAliveHeaderToTop);
	MCP_Send_Message_Always(&hcan, dap.payload, dribblerAliveHeaderToKicker);
	MCP_Send_Message_Always(&hcan, dap.payload, dribblerAliveHeaderToPower);
}


void MCP_Send_Ball_State(){
    if ((MCP_GetFreeToSend(MCP_TOP_BOARD) && MCP_GetFreeToSend(MCP_KICKER_BOARD))) {
        MCP_SeesBallPayload sbp = {0};
        encodeMCP_SeesBall(&sbp, &mcp_seesBall);
        MCP_Send_Message(&hcan, &sbp, seesBallHeaderToTop, MCP_TOP_BOARD);
        MCP_Send_Message(&hcan, &sbp, seesBallHeaderToKicker, MCP_KICKER_BOARD);
        sendSeesBall = false;
    }
}

/* =================================================== */
/* ===================== METHODS ===================== */
/* =================================================== */

void do_send_ballState(){
    sendSeesBall = false; 

    if (mcp_seesBall.ballsensorSeesBall != ballsensor_hasBall()) {
        mcp_seesBall.ballsensorSeesBall = ballsensor_hasBall();
        sendSeesBall = true;
    }

    if (mcp_seesBall.dribblerSeesBall != dribbler_hasBall()) {
        mcp_seesBall.dribblerSeesBall = dribbler_hasBall();
        sendSeesBall = true;
    }

    if (sendSeesBall) {
        MCP_Send_Ball_State();
    }
}

void control_dribbler_callback() { 
    set_Pin(LED1, ballsensor_hasBall());
    set_Pin(LED2, dribbler_hasBall());

    do_send_ballState();
    if (dribblerCommand.dribblerOn) {
        if(ballsensor_hasBall()){
            ball_counter = 0;
            dribbler_SetSpeed(0.8f, 1);
            return;
        }
        else if (ball_counter < 5){
            ball_counter = ball_counter + 1;
            dribbler_SetSpeed(0.2f, 1);
            return;
        }
    }
    dribbler_SetSpeed(0.0f, 1);
}


/* ============================================================ */
/* ===================== STM HAL CALLBACKS ==================== */
/* ============================================================ */

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
    if (hadc == CURRENT_DRIBBLER){// hadc == &hadc1
        control_dribbler_callback(); 
    }
}