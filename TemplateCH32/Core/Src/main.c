/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "iwdg.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "tim_it.h"
#include "exti_it.h"
#include "motor_encode.h"
#include "motor.h"
#include "usart_it.h"
#include "pid.h"
#include "e_8421.h"
#include "system.h"
#include <string.h>
#include "arm_math.h"
#include "fft.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
extern uint8_t FFT_Flag;
extern float buff[FFT_LENGTH];

float outsum=0;

uint8_t SSS=1;



extern //记录卡顿的脉冲
uint16_t KartunPulse;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
        /* 设置NVIC的向量表偏移寄存器,VTOR低9位保留,即[8:0]保留 */
    SCB->VTOR = FLASH_BASE | (0x08000 & (uint32_t)0xFFFFFE00);
    
    uint16_t i = 0;
    UNUSED(i);
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_USART1_UART_Init();
//  MX_IWDG_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  
//  if(GetE_8421() == 0)
//  {
////	  for(uint16_t i=0;i<100;i++)
////			HAL_Delay(10);
//	  U_Speed = 0x30;
//  }
//  else
//  {
//	U_Speed = 0;
//  }
  
  
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);

    HAL_TIM_Base_Start_IT(&htim4);
    
//    //启动计数器
//    HAL_TIM_Base_Start_IT(&htim2);
    

    HAL_UART_Receive_IT(&huart1, &USART1_RxStruct.receive, 1);

    pid_init();

    SetMotorCCW(0, GPIO_PIN_RESET);
    SetMotorCCW(1, GPIO_PIN_RESET);
    SetMotorPWM(0, 10);
    SetMotorPWM(1, 10);
    delay_ms(10);//相当于复位，以启动电机 
    SetMotorCCW(0, GPIO_PIN_SET);
    SetMotorCCW(1, GPIO_PIN_SET);
    SetMotorPWM(0, 0);
    SetMotorPWM(1, 0);
    
    
//    U_Speed = 0x10;

//    printf("Init\n");
    
//    SSS=0x50;
//    while(1)
//    {
//        if(TIM3->CCR1<100)
//        {
//            SSS++;
//        }
//        else
//        {
//            static uint16_t n=0;
//            n++;
//            if(n==5)
//            {
//                goto START;
//            }
//        }
//        HAL_Delay(100);
//    }
    
    START:
    SSS+=5;
//    U_Speed = 0x20;
//    FFT_64_Init();
    
//    U_Speed = 0;

  if(GetE_8421() == 0)
  {
	  for(uint16_t i=0;i<1000;i++)
			HAL_Delay(10);
	  U_Speed = 0x30;
	  HAL_GPIO_WritePin(led1_GPIO_Port,led1_Pin,GPIO_PIN_RESET);
  }
  else
  {
	U_Speed = 0;
  }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1)
    {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		
        HAL_IWDG_Refresh(&hiwdg);
        while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0));
    }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_2)
  {
  }
  LL_RCC_HSE_Enable();

   /* Wait till HSE is ready */
  while(LL_RCC_HSE_IsReady() != 1)
  {

  }
  LL_RCC_LSI_Enable();

   /* Wait till LSI is ready */
  while(LL_RCC_LSI_IsReady() != 1)
  {

  }
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE_DIV_1, LL_RCC_PLL_MUL_9);
  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {

  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {

  }
  LL_SetSystemCoreClock(72000000);

   /* Update the time base */
  if (HAL_InitTick (TICK_INT_PRIORITY) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
      /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
      /* User can add his own implementation to report the file name and line number,
         ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
