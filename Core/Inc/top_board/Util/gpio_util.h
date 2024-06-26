/*
 * gpio_util.h
 *
 *  Created on: 8 April 2019
 *      Author: Cas Doornkamp
 */

#ifndef UTILS_GPIO_UTIL_H_
#define UTILS_GPIO_UTIL_H_

#include "gpio_util_functions.h"

/////////////////////////////////// LIST OF KNOWN GPIO PINS


// Wheels PWM
extern GPIO_Pin RB_PWM_pin;
extern GPIO_Pin RF_PWM_pin;
extern GPIO_Pin LB_PWM_pin;
extern GPIO_Pin LF_PWM_pin;

// Wheels DIR
extern GPIO_Pin RB_DIR_pin;
extern GPIO_Pin RF_DIR_pin;
extern GPIO_Pin LB_DIR_pin;
extern GPIO_Pin LF_DIR_pin;

// Wheels Brake
extern GPIO_Pin RB_Brake_pin;
extern GPIO_Pin RF_Brake_pin;
extern GPIO_Pin LB_Brake_pin;
extern GPIO_Pin LF_Brake_pin;

//Motor driver chip select
extern GPIO_Pin RB_CS_pin;
extern GPIO_Pin RF_CS_pin;
extern GPIO_Pin LB_CS_pin;
extern GPIO_Pin LF_CS_pin;

// Dribbler
extern GPIO_Pin Dribbler_PWM_pin;

// LEDs
extern GPIO_Pin LED0_pin;
extern GPIO_Pin LED1_pin;
extern GPIO_Pin LED2_pin;
extern GPIO_Pin LED3_pin;
extern GPIO_Pin LED4_pin;
extern GPIO_Pin LED5_pin;
extern GPIO_Pin LED6_pin;
extern GPIO_Pin LED7_pin;

// ID select
extern GPIO_Pin ID0_pin;
extern GPIO_Pin ID1_pin;
extern GPIO_Pin ID2_pin;
extern GPIO_Pin ID3_pin;

// Feature Select
extern GPIO_Pin SW4_pin;
extern GPIO_Pin SW5_pin;
extern GPIO_Pin SW6_pin;
extern GPIO_Pin SW7_pin;

// MTi
extern GPIO_Pin MTi_RST_pin;
extern GPIO_Pin MTi_IRQ_pin;
extern GPIO_Pin MTi_NSS_pin;

// Wireless
extern GPIO_Pin SX_IRQ_pin;
extern GPIO_Pin SX_RST_pin;
extern GPIO_Pin SX_NSS_pin;
extern GPIO_Pin SX_BUSY_pin;

// Encoder Interface
extern GPIO_Pin Encoder_Enable_pin;

// SD
extern GPIO_Pin SD_CD_pin;

/////////////////////////////////// FUNCTIONS

static inline uint16_t get_Id(){
	uint16_t ID = 0;
	ID |= !read_Pin(ID3_pin) <<3;
	ID |= !read_Pin(ID2_pin) <<2;
	ID |= !read_Pin(ID1_pin) <<1;
	ID |= !read_Pin(ID0_pin);
	return ID;
}

#endif /* UTILS_GPIO_UTIL_H_ */