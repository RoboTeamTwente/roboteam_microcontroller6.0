/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32f3xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "kicker_board.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern CAN_HandleTypeDef hcan;
extern ADC_HandleTypeDef hadc2;
extern IWDG_HandleTypeDef hiwdg;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define APB 8
#define Kick_Pin GPIO_PIN_1
#define Kick_GPIO_Port GPIOA
#define Chip_Pin GPIO_PIN_2
#define Chip_GPIO_Port GPIOA
#define Charge_done_Pin GPIO_PIN_3
#define Charge_done_GPIO_Port GPIOA
#define Fault_Pin GPIO_PIN_4
#define Fault_GPIO_Port GPIOA
#define Charge_Pin GPIO_PIN_5
#define Charge_GPIO_Port GPIOA
#define V_pos_Pin GPIO_PIN_6
#define V_pos_GPIO_Port GPIOA
#define V_neg_Pin GPIO_PIN_7
#define V_neg_GPIO_Port GPIOA
#define Temp_sensor_Pin GPIO_PIN_1
#define Temp_sensor_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
