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
#include "stm32f1xx_hal.h"

#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_exti.h"
#include "stm32f1xx_ll_cortex.h"
#include "stm32f1xx_ll_utils.h"
#include "stm32f1xx_ll_pwr.h"
#include "stm32f1xx_ll_dma.h"
#include "stm32f1xx_ll_gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern uint8_t ModeIdleFlag;
extern uint8_t BIST;
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
#define led_Pin GPIO_PIN_13
#define led_GPIO_Port GPIOC
#define Motor1PWM_Pin GPIO_PIN_6
#define Motor1PWM_GPIO_Port GPIOA
#define Motor2PWM_Pin GPIO_PIN_7
#define Motor2PWM_GPIO_Port GPIOA
#define E8421_1_Pin GPIO_PIN_12
#define E8421_1_GPIO_Port GPIOB
#define E8421_8_Pin GPIO_PIN_13
#define E8421_8_GPIO_Port GPIOB
#define E8421_2_Pin GPIO_PIN_14
#define E8421_2_GPIO_Port GPIOB
#define E8421_4_Pin GPIO_PIN_15
#define E8421_4_GPIO_Port GPIOB
#define RS485_TX_Pin GPIO_PIN_9
#define RS485_TX_GPIO_Port GPIOA
#define RS485_RX_Pin GPIO_PIN_10
#define RS485_RX_GPIO_Port GPIOA
#define RS485_RE_Pin GPIO_PIN_11
#define RS485_RE_GPIO_Port GPIOA
#define M1_CWCCW_Pin GPIO_PIN_4
#define M1_CWCCW_GPIO_Port GPIOB
#define M2_CWCCW_Pin GPIO_PIN_5
#define M2_CWCCW_GPIO_Port GPIOB
#define M1_Encode_Pin GPIO_PIN_6
#define M1_Encode_GPIO_Port GPIOB
#define M1_Encode_EXTI_IRQn EXTI9_5_IRQn
#define M2_Encode_Pin GPIO_PIN_7
#define M2_Encode_GPIO_Port GPIOB
#define M2_Encode_EXTI_IRQn EXTI9_5_IRQn
#define led1_Pin GPIO_PIN_8
#define led1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
