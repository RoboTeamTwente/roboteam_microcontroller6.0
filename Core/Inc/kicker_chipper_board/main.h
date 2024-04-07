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

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
extern CAN_HandleTypeDef hcan;
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
#define Charge_done_Pin GPIO_PIN_1
#define Charge_done_GPIO_Port GPIOA
#define Fault_Pin GPIO_PIN_2
#define Fault_GPIO_Port GPIOA
#define Charge_Pin GPIO_PIN_5
#define Charge_GPIO_Port GPIOA
#define Kick_Pin GPIO_PIN_6
#define Kick_GPIO_Port GPIOA
#define Chip_Pin GPIO_PIN_7
#define Chip_GPIO_Port GPIOA
#define Temp_Sens_Pin GPIO_PIN_1
#define Temp_Sens_GPIO_Port GPIOB
#define Cap_VoltageN_Pin GPIO_PIN_6
#define Cap_VoltageN_GPIO_Port GPIOB
#define Cap_VoltageP_Pin GPIO_PIN_7
#define Cap_VoltageP_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */