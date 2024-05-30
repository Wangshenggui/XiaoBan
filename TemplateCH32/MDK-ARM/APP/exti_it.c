#include "exti_it.h"
#include "system.h"
#include "tim.h"
#include <stdio.h>

void delay(uint8_t x)
{
    uint8_t i=0,j;
    
    for(j=0;j<x;j++)
        for(i=0;i<72;i++)
        {
            __nop();
        }
}



extern //记录卡顿的脉冲
uint16_t KartunPulse;

__IO uint16_t EXTI6_N=0;
__IO uint16_t EXTI7_N=0;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin==GPIO_PIN_6)
    {
        if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6)==1)
        {
//            if(HAL_GPIO_ReadPin(M1_CWCCW_GPIO_Port,M1_CWCCW_Pin)==GPIO_PIN_SET)
//            {
//                EXTI6_N++;
////                HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin,GPIO_PIN_SET);
////                HAL_GPIO_WritePin(led_GPIO_Port, led_Pin,GPIO_PIN_SET);
//            }
//            else
//            {
//                EXTI6_N--;
////                HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin,GPIO_PIN_RESET);
////                HAL_GPIO_WritePin(led_GPIO_Port, led_Pin,GPIO_PIN_RESET);
//            }
            
            
            EXTI6_N++;
        }
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_6);
    }
    
    if(GPIO_Pin==GPIO_PIN_7)
    {
        /*特殊处理*/
        if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7)==1)
        {
            if(HAL_GPIO_ReadPin(M2_CWCCW_GPIO_Port,M2_CWCCW_Pin)==GPIO_PIN_SET)
            {
                KartunPulse++;
                if(KartunPulse>20000)
                {
                    KartunPulse=20000;
                }
//                HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin,GPIO_PIN_SET);
//                HAL_GPIO_WritePin(led_GPIO_Port, led_Pin,GPIO_PIN_SET);
            }
            else
            {
                KartunPulse--;
                if(KartunPulse<=0)
                {
                    KartunPulse=0;
                }
//                HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin,GPIO_PIN_RESET);
//                HAL_GPIO_WritePin(led_GPIO_Port, led_Pin,GPIO_PIN_RESET);
            }
            
            
//            if(TIM3->CCR2>10)
                EXTI7_N++;
        }
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_7);
    }
}





