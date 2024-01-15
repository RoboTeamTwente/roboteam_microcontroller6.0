/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define APB 150
#define MAX_PWM 6000
#define ENCODER_FILTER 15
#define LF_FAULT_Pin GPIO_PIN_2
#define LF_FAULT_GPIO_Port GPIOE
#define LF_BRK_Pin GPIO_PIN_3
#define LF_BRK_GPIO_Port GPIOE
#define LF_DIR_Pin GPIO_PIN_4
#define LF_DIR_GPIO_Port GPIOE
#define LF_PWM_Pin GPIO_PIN_5
#define LF_PWM_GPIO_Port GPIOE
#define LB_PWM_Pin GPIO_PIN_6
#define LB_PWM_GPIO_Port GPIOE
#define LF_CS_Pin GPIO_PIN_13
#define LF_CS_GPIO_Port GPIOC
#define LB_CS_Pin GPIO_PIN_2
#define LB_CS_GPIO_Port GPIOF
#define LB_FAULT_Pin GPIO_PIN_3
#define LB_FAULT_GPIO_Port GPIOF
#define LB_BRK_Pin GPIO_PIN_4
#define LB_BRK_GPIO_Port GPIOF
#define LB_DIR_Pin GPIO_PIN_5
#define LB_DIR_GPIO_Port GPIOF
#define PWM_Buzzer_Pin GPIO_PIN_6
#define PWM_Buzzer_GPIO_Port GPIOF
#define RF_Current_Pin GPIO_PIN_0
#define RF_Current_GPIO_Port GPIOC
#define RB_Current_Pin GPIO_PIN_1
#define RB_Current_GPIO_Port GPIOC
#define LF_Current_Pin GPIO_PIN_2
#define LF_Current_GPIO_Port GPIOC
#define LB_Current_Pin GPIO_PIN_3
#define LB_Current_GPIO_Port GPIOC
#define LF_CHA_Pin GPIO_PIN_0
#define LF_CHA_GPIO_Port GPIOA
#define LF_CHB_Pin GPIO_PIN_1
#define LF_CHB_GPIO_Port GPIOA
#define DIP_SW0_Pin GPIO_PIN_5
#define DIP_SW0_GPIO_Port GPIOA
#define LB_CHA_Pin GPIO_PIN_6
#define LB_CHA_GPIO_Port GPIOA
#define LB_CHB_Pin GPIO_PIN_7
#define LB_CHB_GPIO_Port GPIOA
#define DIP_SW1_Pin GPIO_PIN_4
#define DIP_SW1_GPIO_Port GPIOC
#define DIP_SW2_Pin GPIO_PIN_5
#define DIP_SW2_GPIO_Port GPIOC
#define DIP_SW3_Pin GPIO_PIN_0
#define DIP_SW3_GPIO_Port GPIOB
#define DIP_SW4_Pin GPIO_PIN_1
#define DIP_SW4_GPIO_Port GPIOB
#define DIP_SW5_Pin GPIO_PIN_2
#define DIP_SW5_GPIO_Port GPIOB
#define DIP_SW6_Pin GPIO_PIN_11
#define DIP_SW6_GPIO_Port GPIOF
#define DIP_SW7_Pin GPIO_PIN_12
#define DIP_SW7_GPIO_Port GPIOF
#define LED7_Pin GPIO_PIN_13
#define LED7_GPIO_Port GPIOF
#define LED6_Pin GPIO_PIN_14
#define LED6_GPIO_Port GPIOF
#define LED5_Pin GPIO_PIN_15
#define LED5_GPIO_Port GPIOF
#define LED4_Pin GPIO_PIN_0
#define LED4_GPIO_Port GPIOG
#define LED3_Pin GPIO_PIN_1
#define LED3_GPIO_Port GPIOG
#define LED2_Pin GPIO_PIN_7
#define LED2_GPIO_Port GPIOE
#define LED1_Pin GPIO_PIN_8
#define LED1_GPIO_Port GPIOE
#define LED0_Pin GPIO_PIN_9
#define LED0_GPIO_Port GPIOE
#define SPI4_NSS_Pin GPIO_PIN_11
#define SPI4_NSS_GPIO_Port GPIOE
#define SPI4_RST_Pin GPIO_PIN_15
#define SPI4_RST_GPIO_Port GPIOE
#define SPI4_BUSY_Pin GPIO_PIN_10
#define SPI4_BUSY_GPIO_Port GPIOB
#define SPI4_IRQ_Pin GPIO_PIN_11
#define SPI4_IRQ_GPIO_Port GPIOB
#define SPI4_IRQ_EXTI_IRQn EXTI15_10_IRQn
#define BTN_SW0_Pin GPIO_PIN_15
#define BTN_SW0_GPIO_Port GPIOB
#define BTN_SW0_EXTI_IRQn EXTI15_10_IRQn
#define BTN_SW1_Pin GPIO_PIN_8
#define BTN_SW1_GPIO_Port GPIOD
#define BTN_SW1_EXTI_IRQn EXTI9_5_IRQn
#define BTN_SW2_Pin GPIO_PIN_9
#define BTN_SW2_GPIO_Port GPIOD
#define BTN_SW2_EXTI_IRQn EXTI9_5_IRQn
#define BTN_SW3_Pin GPIO_PIN_10
#define BTN_SW3_GPIO_Port GPIOD
#define BTN_SW3_EXTI_IRQn EXTI15_10_IRQn
#define RB_CHA_Pin GPIO_PIN_12
#define RB_CHA_GPIO_Port GPIOD
#define RB_CHB_Pin GPIO_PIN_13
#define RB_CHB_GPIO_Port GPIOD
#define Encoder_Enable_Pin GPIO_PIN_14
#define Encoder_Enable_GPIO_Port GPIOD
#define RB_CS_Pin GPIO_PIN_15
#define RB_CS_GPIO_Port GPIOD
#define RB_FAULT_Pin GPIO_PIN_2
#define RB_FAULT_GPIO_Port GPIOG
#define RB_BRK_Pin GPIO_PIN_3
#define RB_BRK_GPIO_Port GPIOG
#define RB_DIR_Pin GPIO_PIN_4
#define RB_DIR_GPIO_Port GPIOG
#define RF_CS_Pin GPIO_PIN_5
#define RF_CS_GPIO_Port GPIOG
#define RF_FAULT_Pin GPIO_PIN_6
#define RF_FAULT_GPIO_Port GPIOG
#define RF_BRK_Pin GPIO_PIN_7
#define RF_BRK_GPIO_Port GPIOG
#define RF_DIR_Pin GPIO_PIN_8
#define RF_DIR_GPIO_Port GPIOG
#define RB_PWM_Pin GPIO_PIN_6
#define RB_PWM_GPIO_Port GPIOC
#define RF_PWM_Pin GPIO_PIN_7
#define RF_PWM_GPIO_Port GPIOC
#define RF_CHA_Pin GPIO_PIN_8
#define RF_CHA_GPIO_Port GPIOA
#define RF_CHB_Pin GPIO_PIN_9
#define RF_CHB_GPIO_Port GPIOA
#define SD_MMC1_CD_Pin GPIO_PIN_3
#define SD_MMC1_CD_GPIO_Port GPIOD
#define XSENS_IRQ_Pin GPIO_PIN_5
#define XSENS_IRQ_GPIO_Port GPIOD
#define XSENS_IRQ_EXTI_IRQn EXTI9_5_IRQn
#define XSENS_RST_Pin GPIO_PIN_6
#define XSENS_RST_GPIO_Port GPIOD
#define SPI1_NSS_Pin GPIO_PIN_10
#define SPI1_NSS_GPIO_Port GPIOG

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */