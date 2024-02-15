#include "power_board.h"

/* ======================================================== */
/* ==================== INITIALIZATION ==================== */
/* ======================================================== */
void init() {
    // Set power circuit pin to HIGH, meaning on. When pulled again to LOW, it signals the power circuit to turn off, and power is then cut off instantly.
	// This pin must be set HIGH within a few milliseconds after powering on the robot, or it will turn the robot off again
	set_Pin(BAT_KILL_pin, 0); //0 SHOULD BE 1 BUT ELECTRONICS NEEDS TO FIX IT

    /* === Wired communication with robot; Can now receive RobotCommands (and other REM packets) via UART */
	REM_UARTinit(UART_PC);
}



/* =================================================== */
/* ==================== MAIN LOOP ==================== */
/* =================================================== */
void loop() {
    HAL_Delay(5);
}