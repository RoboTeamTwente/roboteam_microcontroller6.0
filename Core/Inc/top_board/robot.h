#ifndef __ROBOT__H_
#define __ROBOT__H_

#include <unistd.h>
#include "main.h"

#include "control_util.h"
#include "gpio_util.h"
#include "tim_util.h"
#include "peripheral_util.h"
#include "wheels.h"
#include "stateControl.h"
#include "stateEstimation.h"
#include "sdcard.h"
#include "Wireless.h"
#include "buzzer.h"
#include "speaker.h"
#include "MTi.h"
#include "yawCalibration.h"
#include "iwdg.h"
#include "logging.h"
#include "SX1280_Constants.h"
#include "AssuredPacketManager.h"
#include "drivers.h"
#include "pages.h"

#include "CanDriver.h"
#include "system_test.h"
#include "drain_battery.h"
#include "mcp_page.h"

#include "rem.h"

#include "REM_Packet.h"
#include "REM_RobotCommand.h"
#include "REM_RobotFeedback.h"
#include "REM_RobotBuzzer.h"
#include "REM_RobotStateInfo.h"
#include "REM_RobotGetPIDGains.h"
#include "REM_RobotSetPIDGains.h"
#include "REM_RobotPIDGains.h"
#include "REM_SX1280Filler.h"
#include "REM_RobotMusicCommand.h"
#include "REM_Log.h"
#include "REM_RobotKillCommand.h"

#include <time.h>
#include <unistd.h>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

// These three are currently a callback hack for the REM implementation
REM_RobotCommandPayload myRobotCommandPayload;
REM_RobotCommand myRobotCommand;

extern uint64_t unix_timestamp;
extern bool DISABLE_BUZZER;
extern uint16_t powerboard_voltage;
extern bool powerBoard_alive;
extern bool TEST_MODE;
extern bool powerBoard_alive, dribblerBoard_alive, kickerBoard_alive, chip_state, kick_state;
extern uint8_t shoot_power;
extern bool dribbler_speed;

void init(void);
void loop(void);
uint8_t robot_get_ID();
uint8_t robot_get_Channel();
void check_otherboards(uint8_t board_ID, bool *board_state);

void robot_setRobotCommandPayload(REM_RobotCommandPayload* rcp);
void robot_setRobotMusicCommandPayload(REM_RobotMusicCommandPayload* rmcp);
bool handlePacket(uint8_t* packet_buffer, uint8_t packet_length);

#endif /* __ROBOT__H_ */