#include "dribbler_board.h"

volatile bool BOARD_INITIALIZED = false;

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

/* ======================================================== */
/* ==================== INITIALIZATION ==================== */
/* ======================================================== */
void init(){
    //CAN_Init(&hcan, DRIBBLER_ID);
    dribbler_Init(&htim3, &hdac1);
    ballsensor_init();
    ballsensor_setIR_on();
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
            CAN_Process_Message(&MailBox_one);
        if (!MailBox_two.empty)
            CAN_Process_Message(&MailBox_two);
        if (!MailBox_three.empty)
            CAN_Process_Message(&MailBox_three);
        CAN_to_process = false;
	}

}

/* ============================================= */
/* ==================== CAN ==================== */
/* ============================================= */
void CAN_Process_Message(mailbox_buffer *to_Process){

    if (to_Process->message_id == ARE_YOU_ALIVE){
        HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
        if (get_MCP_version(to_Process->data_Frame) != MCP_VERSION){
            //TODO send a message or something saying that incorrect
        }
        CAN_Send_Message(IM_ALIVE_DRIBBLER, TOP_ID, &hcan);
    }
    else if (to_Process->message_id == DRIBBLER_SPEED){
        float new_dribbler_speed = get_dribbler_sees_ball(to_Process->data_Frame);
        dribbler_SetSpeed(new_dribbler_speed); 
    }   

}
void CAN_Send_Message(uint8_t sending_message_ID, uint8_t reciever_ID ,CAN_HandleTypeDef *hcan){

    uint8_t payload[8];
    memset(payload, 0, sizeof(payload));
    CAN_TxHeaderTypeDef CAN_TxHeader = CAN_Initalize_Header();

    if (reciever_ID == TOP_ID){

        if (sending_message_ID == DRIBBLER_SEESBALL_MESSAGE){
            return;
            //set_dribbler_sees_ball_header(&CAN_TxHeader);
            //set_dribbler_sees_ball(payload, dribbler_GetHasBall());
        }

        else if (sending_message_ID == BALLSENSOR_MESSAGE){
            return;
            //set_ballsensor_sees_ball_header(&CAN_TxHeader);
	        //set_ballsensor_state(payload, ballsensor_state);        
        }

        else if (sending_message_ID == IM_ALIVE_DRIBBLER){
            set_dribbler_im_alive(&CAN_TxHeader);
            set_MCP_version(payload);
            set_dribbler_state(payload, true);
            set_ballsensor_state(payload, true);
        }
    }

    if (HAL_CAN_AddTxMessage(hcan, &CAN_TxHeader, &payload, &TxMailbox[0]) != HAL_OK) CAN_error_LOG(&CAN_TxHeader);

}

/* =================================================== */
/* ===================== METHODS ===================== */
/* =================================================== */
void dribbler_CALLBACK_FUNCTION(){
    dribbler_Update();
    dribbler_CalculateHasBall();
    if (dribbler_ChangeInState()){
        CAN_Send_Message(DRIBBLER_SEESBALL_MESSAGE, TOP_ID, &hcan);
        dribbler_set_State(dribbler_GetHasBall());
    }
}


/* ============================================================ */
/* ===================== STM HAL CALLBACKS ==================== */
/* ============================================================ */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
 
}

// void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
//     if (&htim == &htim3){
//         dribbler_CALLBACK_FUNCTION(); // 10Hz has elapsed
//     }
// }