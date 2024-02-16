#include "dribbler_board.h"

/*
    ======================================================================
    ====================== CAN RELEATED VARIABLES ========================
    ======================================================================
*/
uint64_t TxMailbox[1];// Array used in transmission of messages in CAN bus
    // These values are set depending on weither or not the dribbler initalizes correctly, used ONLY FOR INITLIZATION
bool dribbler_functioning_state;
bool ballsensor_functioning_state;
    // These values are sent to the top board, depending on weither the ballsensor or dribbler detects the ball
bool dribbler_state;
bool ballsensor_state;

void init(){
    
}

void loop(){

}

void CAN_Process_Message(mailbox_buffer *to_Process){

    if (to_Process->message_id == ARE_YOU_ALIVE){

        if (get_MCP_version(to_Process->data_Frame) != MCP_VERSION){
            //TODO send a message or something saying that incorrect
        }

    }
    else if (to_Process->message_id == DRIBBLER_SPEED){
        float new_dribbler_speed = get_dribbler_sees_ball(to_Process->data_Frame);
        //set_dribbler_speed(new_dribbler_speed); 
    }   

}
void CAN_Send_Message(uint8_t sending_message_ID, uint8_t reciever_ID ,CAN_HandleTypeDef *hcan){

    uint8_t payload[8];
    memset(payload, 0, sizeof(payload));
    CAN_TxHeaderTypeDef CAN_TxHeader = CAN_Initalize_Header();

    if (reciever_ID == TOP_ID){

        if (sending_message_ID == DRIBBLER_SEESBALL_MESSAGE){
            set_dribbler_sees_ball_header(&CAN_TxHeader);
            set_dribbler_sees_ball(payload, dribbler_state);
        }

        else if (sending_message_ID == BALLSENSOR_MESSAGE){
            set_ballsensor_sees_ball_header(&CAN_TxHeader);
	        set_ballsensor_state(payload, ballsensor_state);        
        }

        else if (sending_message_ID == IM_ALIVE_DRIBBLER){
            set_dribbler_im_alive(&CAN_TxHeader);
            set_MCP_version(payload);
            set_dribbler_state(payload, dribbler_functioning_state);
            set_ballsensor_state(payload, ballsensor_functioning_state);
        }
    }

    if (HAL_CAN_AddTxMessage(hcan, &CAN_TxHeader, &payload, &TxMailbox[0]) != HAL_OK) CAN_error_LOG(&CAN_TxHeader);

}

/*

send_message::

case IM_ALIVE_DRIBBLER:
	set_dribbler_im_alive(&TxHeader);
	set_MCP_version(payload);
	set_dribbler_state(payload, true);
	set_ballsensor_state(payload, true);
	break;

case DRIBBLER_SEESBALL_MESSAGE:
	set_dribbler_sees_ball_header(&TxHeader);
	set_dribbler_sees_ball(payload, true);
	break;

case BALLSENSOR_MESSAGE:
	set_ballsensor_sees_ball_header(&TxHeader);
	set_ballsensor_state(payload, true);
	break;

process_message::

case ARE_YOU_ALIVE:
	set_are_you_alive_message_header(&TxHeader, reciever_ID);
	set_MCP_version(payload);
	break;


*/