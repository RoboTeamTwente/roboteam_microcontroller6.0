#include "logging.h"

uint8_t to_send[STRING_SIZE] = {'\0'};
char printf_buffer[50];

void LOG_init(){
    LOG_printf(" ");
    LOG_printf("[INIT]\r\n");
    return;
}

void LOG_deinit(){
    return;
}

/*
    This function can take multiple strings as input
    Transmits them will a small delay in between them
*/
bool LOG_printf(char* format, ...){
    strcpy(to_send, format);
    HAL_UART_Transmit(&huart1, to_send, sizeof(to_send), 100);
    HAL_Delay(100);
    // va_list aptr;
    // va_start(aptr, format);
    // vsnprintf(printf_buffer, 256, format, aptr);
    // va_end(aptr);

    // LOG();
}

void LOG(){
    strcpy(to_send, printf_buffer);
    HAL_UART_Transmit(&huart1, to_send, sizeof(to_send), 100);
    HAL_Delay(100);
}