#include "dribbler_board.h"
#include <stdlib.h>
#include <string.h>

volatile bool BOARD_INITIALIZED = false;

void MCP_Process_Message(mailbox_buffer *to_Process);
void MCP_Send_Im_Alive();
void do_send_ballState();

void no_encoder_control();
void has_encoder_control();


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
static bool sendSeesBall = false;

// Checks for how long we lost the ball
uint8_t ball_counter = 0;

// Heart Beats
uint32_t current_beat = 0;
uint32_t heart_beat_10ms = 0;

uint8_t Uart_Tx_Buffer[40] = {0};

bool dribbler_initialized = false;

//Dribbler control
#define CONTROL_TIMER_PERIOD 0.001f
float setpoint = 0;
float PWM = 0.0f;
float speed = 0; 
float timestamp = 0;

float Kp = 0.002f;  
float Ki = 0.00f; 
float Kd = 0.00f;  

float previous_error = 0.0f;
float integral = 0.0f;

int state = 0;

// #define LOGGING //uncomment if you want output

/* ======================================================== */
/* ==================== INITIALIZATION ==================== */
/* ======================================================== */
void init(){
    HAL_IWDG_Refresh(&hiwdg);
    // Peripherals
    HAL_TIM_Base_Start_IT(CONTROL_TIMER); //start the timer used for the control loop
    HAL_TIM_Encoder_Start_IT(&htim2, TIM_CHANNEL_ALL); //enable timer for the encoder
    LOG_init();
    dribbler_initialized = dribbler_Init();
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
    LOG_printf("Drib start!\n");
    LOG_sendAll();
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
    do_send_ballState();

    // if(dribblerCommand.dribblerOn){
    //     LOG_printf("Dribbler is on\n");
    // } else {
    //     LOG_printf("Dribbler is off\n");
    // }
    // LOG_sendAll();

#ifdef LOGGING
    sprintf((char*) Uart_Tx_Buffer, "S:%.2f,D:%.2f,P:%.2f,T:%.4f\n",setpoint, speed, PWM, timestamp);
    HAL_UART_Transmit_DMA(&huart1, Uart_Tx_Buffer, sizeof (Uart_Tx_Buffer)-1);
#endif



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
    }
}

void MCP_resetSendMsg() {
    sendSeesBall = false;
}

/* =================================================== */
/* ===================== METHODS ===================== */
/* =================================================== */

void do_send_ballState(){ 

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
        HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
    }
}
void control_dribbler_callback() { 

    dribbler_UpdateEncoderSpeed();
    timestamp += CONTROL_TIMER_PERIOD;

    set_Pin(LED1, ballsensor_hasBall());
    // set_Pin(LED2, dribbler_hasBall()); //moved to mcp send sees ball

    do_send_ballState();

    if(dribbler_initialized){
        if(dribbler_hasEncoder()){
            has_encoder_control();
        } else{
            no_encoder_control();
        }
    }

} 




void has_encoder_control() {


    if(ballsensor_hasBall() && dribblerCommand.dribblerOn){
            setpoint = 500;
            state = 1;
    } else {
            setpoint = 0;
            state = 2;
    }


    speed = dribbler_GetEncoderSpeed();

    float error = setpoint - (float)fabs(speed);
    
    integral += error * CONTROL_TIMER_PERIOD;
    
    float derivative = (error - previous_error) / CONTROL_TIMER_PERIOD;
    
    float output = (Kp * error) + (Ki * integral) + (Kd * derivative);
    
    PWM += output;

    if (PWM > 1.0f) {
        PWM = 1.0f;
    } else if (PWM < 0.0f) {
        PWM = 0.0f;
    }
    
    previous_error = error;

    dribbler_SetSpeed(PWM,1);
}


void no_encoder_control(){
    if(dribblerCommand.dribblerOn){
        if(ballsensor_hasBall()){
            ball_counter = 0;
            dribbler_SetMaxSpeed(1);
            return;
        }
        else if (ball_counter < 5){
            ball_counter = ball_counter + 1;
            dribbler_SetIdleSpeed(1);
            return;
        } else if (dribblerCommand.SystemTest) {
            dribbler_SetSpeed(0.5f, 1);
            return;
        } 
            dribbler_SetSpeed(0.0f, 1);
    } else{
        dribbler_SetSpeed(0.0f, 1);
    }
}


/* ============================================================ */
/* ===================== STM HAL CALLBACKS ==================== */
/* ============================================================ */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
    if (hadc == CURRENT_DRIBBLER){// hadc == &hadc1
        ballsensor_DetectBall();

    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == CONTROL_TIMER->Instance) {
        control_dribbler_callback();
	}
}
