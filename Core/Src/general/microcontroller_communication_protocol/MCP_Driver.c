#include "MCP_Driver.h"

// Definition of mailbox buffers
mailbox_buffer MailBox_one;
mailbox_buffer MailBox_two;
mailbox_buffer MailBox_three;
uint32_t TxMailbox[1];
bool MCP_to_process = false;

// Acknowledgement helpers
uint8_t ack_numbers[MCP_MAX_ID_PLUS_ONE];
bool free_to_send[MCP_MAX_ID_PLUS_ONE];
uint8_t sending_board_id;

/**
 * @brief initialize CAN communication
*/
void MCP_Init(CAN_HandleTypeDef *hcan, uint8_t board_id){
    sending_board_id = board_id;

    // Configuration of CAN filter
    CAN_FilterTypeDef canfilterconfig;
    canfilterconfig.FilterActivation = CAN_FILTER_ENABLE;
    canfilterconfig.FilterMode = CAN_FILTERMODE_IDMASK;
    canfilterconfig.FilterScale = CAN_FILTERSCALE_32BIT;
    canfilterconfig.FilterBank = 10;
    canfilterconfig.FilterFIFOAssignment = CAN_RX_FIFO0;
    canfilterconfig.FilterIdHigh = ((MCP_LOCAL_VERSION << MCP_VERSION_BIT_SHIFT) | (sending_board_id << MCP_TO_ID_BIT_SHIFT)) << 3;
    canfilterconfig.FilterIdLow = 0x00000000;
    canfilterconfig.FilterMaskIdHigh = (MCP_VERSION_BIT_MASK | sending_board_id) << 3;
    canfilterconfig.FilterMaskIdLow = 0x00000000;

    canfilterconfig.SlaveStartFilterBank = 0;

    // Mailboxes
    MailBox_one.empty = true;
    MailBox_one.message_id = 0;
    MailBox_two.empty = true;
    MailBox_two.message_id = 0;
    MailBox_three.empty = true;
    MailBox_three.message_id = 0;

    // Acknowledgements
    for (int i = 0; i < MCP_MAX_ID_PLUS_ONE; i++) {
        ack_numbers[i] = 0x00;
        free_to_send[i] = true;
    }

    // Configure CAN filter
    HAL_CAN_ConfigFilter(hcan, &canfilterconfig);

    // Start CAN communication
    HAL_CAN_Start(hcan);
    HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan){
    CAN_RxHeaderTypeDef RxHeader;
    uint8_t RxData[8];
    memset(RxData, 0, sizeof(RxData));
    HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData);

    // Extract and process the received command
    MCP_to_process = extract_command(RxData, &RxHeader);
}

// Function to handle MCP errors
void MCP_error_LOG(CAN_TxHeaderTypeDef *Header){
    return;  // Placeholder function, not implemented
}

// Function to extract command from received MCP data
bool extract_command(uint8_t RxData[], CAN_RxHeaderTypeDef *Header){
    uint32_t message_ID = Header->ExtId;
    uint8_t data[8];
    memset(data, 0, sizeof(data));

    // Copy received data to local array
    for (int i = 0; i < Header->DLC; i++)
        data[i] = RxData[i];

    // Check and store the command in the appropriate mailbox
    if(MailBox_one.empty){
        MailBox_one.empty = false;
        MailBox_one.message_id = message_ID;
        memcpy(MailBox_one.data_Frame, data, sizeof(data));
        return true;
    } else if (MailBox_two.empty){
        MailBox_two.empty = false;
        MailBox_two.message_id = message_ID;
        memcpy(MailBox_two.data_Frame, data, sizeof(data));
        return true;
    } else if (MailBox_three.empty){
        MailBox_three.empty = false;
        MailBox_three.message_id = message_ID;
        memcpy(MailBox_three.data_Frame, data, sizeof(data));
        return true;
    }

    // Free dynamically allocated memory and return false if mailboxes are full
    free(data);
    return false;
}

/**
 * @brief Function to initialize MCP header structure
*/
CAN_TxHeaderTypeDef MCP_Initialize_Header(uint16_t type, uint8_t receiving_board){

    CAN_TxHeaderTypeDef TxHeader;

    TxHeader.DLC = MCP_TYPE_TO_SIZE(type);
    TxHeader.StdId = 0;
    TxHeader.ExtId = MCP_TYPE_TO_ID(type, receiving_board, sending_board_id);
    TxHeader.IDE = CAN_ID_EXT;
    TxHeader.RTR = CAN_RTR_DATA;
    TxHeader.TransmitGlobalTime = DISABLE;
    
    return TxHeader;
}

/**
 * @brief send messages over CAN bus if there is space
*/
void MCP_Send_Message(CAN_HandleTypeDef *hcan, uint8_t *payload, CAN_TxHeaderTypeDef CAN_TxHeader, uint8_t to_board) {
    if ((CAN_TxHeader.ExtId & MCP_ERROR_BIT_MASK) >> MCP_ERROR_BIT_SHIFT == 1) MCP_error_LOG(&CAN_TxHeader);
    else if (free_to_send[to_board]){
        // set ack numbers
        payload[0] = ack_numbers[to_board];
        // send
        if (HAL_CAN_AddTxMessage(hcan, &CAN_TxHeader, payload, &TxMailbox[0]) == HAL_OK) free_to_send[to_board] = false;
        else MCP_error_LOG(&CAN_TxHeader);
    }
}

/**
 * @brief send messages that over CAN bus, disregarding acknowledgements
*/
void MCP_Send_Message_Always(CAN_HandleTypeDef *hcan, uint8_t *payload, CAN_TxHeaderTypeDef CAN_TxHeader) {
    if ((CAN_TxHeader.ExtId & MCP_ERROR_BIT_MASK) >> MCP_ERROR_BIT_SHIFT == 1) MCP_error_LOG(&CAN_TxHeader);
    else {
        payload[0] = 0;
        if (HAL_CAN_AddTxMessage(hcan, &CAN_TxHeader, payload, &TxMailbox[0]) != HAL_OK) MCP_error_LOG(&CAN_TxHeader);
    }
}