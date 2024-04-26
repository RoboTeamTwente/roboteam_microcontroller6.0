#include "dribbler_board.h"

volatile bool BOARD_INITIALIZED = false;

void MCP_Process_Message(mailbox_buffer *to_Process);
void MCP_Send_Im_Alive();

// Outgoing MCP headers
CAN_TxHeaderTypeDef dribblerAliveToTop = {0};
CAN_TxHeaderTypeDef dribblerAliveToPower = {0};
CAN_TxHeaderTypeDef dribblerAliveToKicker = {0};
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


/* ======================================================== */
/* ==================== INITIALIZATION ==================== */
/* ======================================================== */
void init(){
    //MCP
    MCP_Init(&hcan, MCP_DRIBBLER_BOARD);
    dribblerAliveToTop = MCP_Initialize_Header(MCP_PACKET_TYPE_MCP_DRIBBLER_ALIVE, MCP_TOP_BOARD);
    dribblerAliveToKicker = MCP_Initialize_Header(MCP_PACKET_TYPE_MCP_DRIBBLER_ALIVE, MCP_KICKER_BOARD);
    dribblerAliveToPower = MCP_Initialize_Header(MCP_PACKET_TYPE_MCP_DRIBBLER_ALIVE, MCP_POWER_BOARD);
    dribblerEncoderHeader = MCP_Initialize_Header(MCP_PACKET_TYPE_MCP_DRIBBLER_ENCODER, MCP_TOP_BOARD);
    seesBallHeaderToTop = MCP_Initialize_Header(MCP_PACKET_TYPE_MCP_SEES_BALL, MCP_TOP_BOARD);
    seesBallHeaderToKicker = MCP_Initialize_Header(MCP_PACKET_TYPE_MCP_SEES_BALL, MCP_KICKER_BOARD);

    MCP_SetReadyToReceive(true);
	MCP_Send_Im_Alive();
    
    //dribbler_Init();
    //ballSensor_Init();
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
    if (MCP_to_process){
        if (!MailBox_one.empty)
            MCP_Process_Message(&MailBox_one);
        if (!MailBox_two.empty)
            MCP_Process_Message(&MailBox_two);
        if (!MailBox_three.empty)
            MCP_Process_Message(&MailBox_three);
        MCP_to_process = false;
	}

    sendSeesBall = false;

    if (mcp_seesBall.ballsensorSeesBall != bs_seesBall) {
        mcp_seesBall.ballsensorSeesBall = bs_seesBall;
        sendSeesBall = true;
    }

    if (mcp_seesBall.dribblerSeesBall != dribbler_GetHasBall()) {
        mcp_seesBall.dribblerSeesBall = dribbler_GetHasBall();
        sendSeesBall = true;
    }

    if (sendSeesBall) {
        MCP_SeesBallPayload sbp = {0};
        encodeMCP_SeesBall(&sbp, &mcp_seesBall);
        //TODO what is free_to_send is false?
        MCP_Send_Message(&hcan, &sbp, seesBallHeaderToTop, MCP_TOP_BOARD);
        MCP_Send_Message(&hcan, &sbp, seesBallHeaderToKicker, MCP_KICKER_BOARD);
        sendSeesBall = false;
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
    MCP_Send_Message_Always(&hcan, dap.payload, dribblerAliveToTop);
	MCP_Send_Message_Always(&hcan, dap.payload, dribblerAliveToKicker);
	MCP_Send_Message_Always(&hcan, dap.payload, dribblerAliveToPower);
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
    // if (GPIO_Pin == BS_IRQ_pin.PIN){
	// 	ballSensor_IRQ_Handler();
	// }
}

// void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
//     if (&htim == &htim3){
//         dribbler_CALLBACK_FUNCTION(); // 10Hz has elapsed
//     }
// }