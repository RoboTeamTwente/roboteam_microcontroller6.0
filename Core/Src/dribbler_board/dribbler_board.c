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
MCP_SetDribblerSpeed mcp_SetDribblerSpeed = {0};

static bool sendSeesBall = false;
static uint32_t lastTimeSendSeesBall = 0;
static uint32_t heartbeat_10ms;

/* ====================================================================== */    
/* ====================== CAN RELEATED VARIABLES ======================== */    
/* ====================================================================== */    

// Array used in transmission of messages in CAN bus
uint64_t TxMailbox[1];

// These values are set depending on weither or not the dribbler initalizes correctly, used ONLY FOR INITLIZATION
bool dribbler_functioning_state = true;
bool ballsensor_functioning_state = true;

// These values are sent to the top board, depending on weither the ballsensor or dribbler detects the ball
bool dribbler_state;
bool ballsensor_state;

// Checks for how long we lost the ball
uint8_t ball_counter = 0;

// Heart Beats
uint32_t current_beat = 0;
uint32_t heart_beat_10ms = 0;


/* ======================================================== */
/* ==================== INITIALIZATION ==================== */
/* ======================================================== */
void init(){
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
    
    // Peripherals
    dribbler_Init();
    ballsensor_init();
    dribbler_SetSpeed(0.0f);
    BOARD_INITIALIZED = true;
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
    if (CAN_to_process){
        if (!MailBox_one.empty)
            MCP_Process_Message(&MailBox_one);
        if (!MailBox_two.empty)
            MCP_Process_Message(&MailBox_two);
        if (!MailBox_three.empty)
            MCP_Process_Message(&MailBox_three);
        MCP_to_process = false;
	}

    // sendSeesBall = false;

    // if (mcp_seesBall.ballsensorSeesBall != bs_seesBall) {
    //     mcp_seesBall.ballsensorSeesBall = bs_seesBall;
    //     sendSeesBall = true;
    // }

    // if (mcp_seesBall.dribblerSeesBall != dribbler_GetHasBall()) {
    //     mcp_seesBall.dribblerSeesBall = dribbler_GetHasBall();
    //     mcp_seesBall.dribblerSpeedBefore = dribbler_GetSpeedBeforeGotBall();
    //     sendSeesBall = true;
    // }

    // if (sendSeesBall) {
    //     // send seesBall if freeToSend for both top and kicker is free
    //     // or after 250ms try to send to both in case one of them is not acknowledging
    //     if (current_time + 250 > lastTimeSendSeesBall || (MCP_GetFreeToSend(MCP_TOP_BOARD) && MCP_GetFreeToSend(MCP_KICKER_BOARD))) {
    //         MCP_SeesBallPayload sbp = {0};
    //         encodeMCP_SeesBall(&sbp, &mcp_seesBall);
    //         MCP_Send_Message(&hcan, &sbp, seesBallHeaderToTop, MCP_TOP_BOARD);
    //         MCP_Send_Message(&hcan, &sbp, seesBallHeaderToKicker, MCP_KICKER_BOARD);
    //         lastTimeSendSeesBall = current_time;
    //         sendSeesBall = false;
    //     }
    // }

    // if (heartbeat_10ms < current_time && MCP_GetFreeToSend(MCP_TOP_BOARD)) {
    //     heartbeat_10ms = current_time + 10;
    //     mcp_encoder.measuredSpeed = dribbler_GetMeasuredSpeeds();
    //     mcp_encoder.filteredSpeed = dribbler_GetFilteredSpeeds();
    //     MCP_DribblerEncoderPayload dep = {0};
    //     encodeMCP_DribblerEncoder(&dep, &mcp_encoder);
    //     MCP_Send_Message(&hcan, &dep, dribblerEncoderHeader, MCP_TOP_BOARD);
    // }
    

}

/* ============================================= */
/* ==================== MCP ==================== */
/* ============================================= */
void MCP_Process_Message(mailbox_buffer *to_Process){
    bool send_ack = true;

    if (to_Process->message_id == MCP_PACKET_ID_TOP_TO_DRIBBLER_MCP_ARE_YOU_ALIVE) {
        MCP_Send_Im_Alive();
		send_ack = false;
    } else if (to_Process->message_id == MCP_PACKET_ID_TOP_TO_DRIBBLER_MCP_SET_DRIBBLER_SPEED) {
        //TODO
    }

    if (send_ack) MCP_Send_Ack(&hcan, to_Process->data_Frame[0], to_Process->message_id);
	
	to_Process->empty = true;
	*to_Process->data_Frame  = 0;
	to_Process->message_id = 0;
}

void MCP_Send_Im_Alive() {
    MCP_DribblerAlive da = {0};
    MCP_DribblerAlivePayload dap = {0};
    da.ballsensorWorking = ballSensorIsWorking;
    da.dribblerEncoderWorking = false;
    encodeMCP_DribblerAlive(&dap, &da);
    MCP_Send_Message_Always(&hcan, dap.payload, dribblerAliveHeaderToTop);
	MCP_Send_Message_Always(&hcan, dap.payload, dribblerAliveHeaderToKicker);
	MCP_Send_Message_Always(&hcan, dap.payload, dribblerAliveHeaderToPower);
}


void control_dribbler_callback(){    
    if(ballsensor_hasBall()){
        HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 1);
        ball_counter = 0;
        dribbler_SetSpeed(1.0f);
    }
    else if (ball_counter < 50){
        ball_counter = ball_counter + 1;
        dribbler_SetSpeed(0.35f);
    }else{
        dribbler_SetSpeed(0.0);
        HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 0);
    }
    current_beat = HAL_GetTick();
}


/* =================================================== */
/* ===================== METHODS ===================== */
/* =================================================== */
void dribbler_CALLBACK_FUNCTION(){
    dribbler_Update();
    dribbler_CalculateHasBall();
}


/* ============================================================ */
/* ===================== STM HAL CALLBACKS ==================== */
/* ============================================================ */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
 
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
    if (hadc == CUR_DRIBBLER){// hadc == &hadc1
        control_dribbler_callback(); 
    }
    // HAL_GPIO_WritePin(LED1_Pin, LED1_GPIO_Port, 1);
}



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

    
}