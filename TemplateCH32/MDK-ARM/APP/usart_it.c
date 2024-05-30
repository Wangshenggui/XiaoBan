#include "usart_it.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "e_8421.h"
#include "motor.h"
#include "pid.h"
#include "motor_encode.h"

/*
与主机的通信协议：

*/

uint8_t SeedBCondition=0;

USART1_RxStructure USART1_RxStruct;
//用于解决接收失效问题
uint8_t usart_rxFlag=0;

uint8_t TxCMD[10]={0};
//接收
void USART1_IDLE_Handler()
{
    uint8_t E_8421temp;
    
    USART1_RxStruct.Rx_Buff[USART1_RxStruct.Rx_len]=USART1_RxStruct.receive;
    if(USART1_RxStruct.Rx_Buff[USART1_RxStruct.Rx_len]==0x90)//需要等待自检完成
    {
        memcpy(USART1_RxStruct.Buff,USART1_RxStruct.Rx_Buff,200);
        if(USART1_RxStruct.Buff[0]==0xEB && \
            (USART1_RxStruct.Buff[3]==0x90 || USART1_RxStruct.Buff[4]==0x90))
        {
            usart_rxFlag=1;
            E_8421temp=GetE_8421();
            /*----------------------------------------------*/
            //主机发送速度指令\
                            0     1         2      3    4\
            速度标准数据帧：EB 从机地址 功能码(C1) DATA 90
            if(USART1_RxStruct.Buff[1]==E_8421temp && USART1_RxStruct.Buff[2]==0xc1)//指定地址的从机速度
            {
                U_Speed=USART1_RxStruct.Buff[3];
            }
            /*----------------------------------------------*/
            //主机发送读取种子仓信息（从机收到信息会返回种子仓状态）\
                            0     1       2     3\
            速度标准数据帧：EB 从机地址 状态位   90
            //收到数据（将返回种子仓状态）
            if(USART1_RxStruct.Buff[1]==E_8421temp && USART1_RxStruct.Buff[2]==0xD1)
            {
				//发送模式
                HAL_GPIO_WritePin(RS485_RE_GPIO_Port,RS485_RE_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(led1_GPIO_Port,led1_Pin,GPIO_PIN_SET);
                TxCMD[0]=0xEB;//帧头
                TxCMD[1]=USART1_RxStruct.Buff[1];//从机地址
                TxCMD[2]=SeedBCondition;//种子仓状态Seed bin condition
                TxCMD[3]=M2Speed;//传送电机速度
                TxCMD[4]=M1Speed;//辅助电机速度
                TxCMD[5]=0x90;//数据尾
				HAL_UART_Transmit_IT(&huart1,TxCMD,6);
            }
        }
        USART1_RxStruct.Rx_len=0;
    }
    else
    {
        USART1_RxStruct.Rx_len++;
    }
    HAL_UART_Receive_IT(&huart1, &USART1_RxStruct.receive, 1);
}

//发送完成中断
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	//接收模式
	HAL_GPIO_WritePin(RS485_RE_GPIO_Port,RS485_RE_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led1_GPIO_Port,led1_Pin,GPIO_PIN_RESET);
}





