#include <stdio.h>
#include <string.h>

#include "rem.h"
#include "REM_BaseTypes.h"
#include "REM_RobotCommand.h"
#include "REM_RobotMusicCommand.h"
#include "peripheral_util.h"
#include "logging.h"
#include "main.h"

// Buffers to move received packets in to
static uint8_t REM_buffer[100];
static REM_RobotCommandPayload rcp;
static REM_RobotMusicCommandPayload rmcp;

/**
 * @brief Starts the first UART read. This read will eventually lead to 
 * REM_UARTCallback, which will schedule any subsequent reads. 
 * 
 * @param huart The UART to start the first read on. Generally UART_PC.
 */
void REM_UARTinit(UART_HandleTypeDef *huart){
    LOG("[REM_UARTinit]\n");
    HAL_UART_Receive_IT(huart, REM_buffer, 1); // if uncommented, only use with programmer connected
}