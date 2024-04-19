#include "MCP_Driver.h"

// Definition of mailbox buffers
mailbox_buffer MailBox_one;
mailbox_buffer MailBox_two;
mailbox_buffer MailBox_three;
uint32_t TxMailbox[1];
bool MCP_to_process = false;

/**
 * @brief initialize CAN communication
*/
void MCP_Init(CAN_HandleTypeDef *hcan, uint8_t board_id){

    // Configuration of CAN filter
    CAN_FilterTypeDef canfilterconfig;
    canfilterconfig.FilterActivation = CAN_FILTER_ENABLE;
    canfilterconfig.FilterBank = 10;
    canfilterconfig.FilterFIFOAssignment = CAN_RX_FIFO0;
    canfilterconfig.FilterIdHigh = board_id << 12;
    canfilterconfig.FilterIdLow = 0x0000;
    canfilterconfig.FilterMaskIdHigh = 0xF000;
    canfilterconfig.FilterMaskIdLow = 0x0000;
    canfilterconfig.FilterMode = CAN_FILTERMODE_IDMASK;
    canfilterconfig.FilterScale = CAN_FILTERSCALE_32BIT;
    canfilterconfig.SlaveStartFilterBank = 0;

    MailBox_one.empty = true;
    MailBox_one.message_id = 0;
    MailBox_two.empty = true;
    MailBox_two.message_id = 0;
    MailBox_three.empty = true;
    MailBox_three.message_id = 0;

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

// Function to handle CAN errors
void MCP_error_LOG(CAN_TxHeaderTypeDef *Header){
    return;  // Placeholder function, not implemented
}

// Function to extract command from received CAN data
bool extract_command(uint8_t RxData[], CAN_RxHeaderTypeDef *Header){
    uint16_t message_ID = Header->StdId;
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
 * @brief Function to initialize CAN header structure
*/
CAN_TxHeaderTypeDef MCP_Initialize_Header(uint16_t type, uint8_t receiving_board){

    CAN_TxHeaderTypeDef TxHeader;

    TxHeader.DLC = MCP_TYPE_TO_SIZE(type);
    TxHeader.StdId = MCP_TYPE_TO_ID(type, receiving_board);
    TxHeader.ExtId = 0;
    TxHeader.IDE = CAN_ID_STD;
    TxHeader.RTR = CAN_RTR_DATA;
    TxHeader.TransmitGlobalTime = DISABLE;
    return TxHeader;
}

void MCP_Send_Message(CAN_HandleTypeDef *hcan, uint8_t *payload, CAN_TxHeaderTypeDef CAN_TxHeader) {
    if (CAN_TxHeader.StdId == 0xFFFF) MCP_error_LOG(&CAN_TxHeader);
    else if (HAL_CAN_AddTxMessage(hcan, &CAN_TxHeader, payload, &TxMailbox[0]) != HAL_OK) MCP_error_LOG(&CAN_TxHeader);
}