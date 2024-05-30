#include "usart_it.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "e_8421.h"
#include "motor.h"
#include "pid.h"
#include "motor_encode.h"

/*
��������ͨ��Э�飺

*/

uint8_t SeedBCondition=0;

USART1_RxStructure USART1_RxStruct;
//���ڽ������ʧЧ����
uint8_t usart_rxFlag=0;

uint8_t TxCMD[10]={0};
//����
void USART1_IDLE_Handler()
{
    uint8_t E_8421temp;
    
    USART1_RxStruct.Rx_Buff[USART1_RxStruct.Rx_len]=USART1_RxStruct.receive;
    if(USART1_RxStruct.Rx_Buff[USART1_RxStruct.Rx_len]==0x90)//��Ҫ�ȴ��Լ����
    {
        memcpy(USART1_RxStruct.Buff,USART1_RxStruct.Rx_Buff,200);
        if(USART1_RxStruct.Buff[0]==0xEB && \
            (USART1_RxStruct.Buff[3]==0x90 || USART1_RxStruct.Buff[4]==0x90))
        {
            usart_rxFlag=1;
            E_8421temp=GetE_8421();
            /*----------------------------------------------*/
            //���������ٶ�ָ��\
                            0     1         2      3    4\
            �ٶȱ�׼����֡��EB �ӻ���ַ ������(C1) DATA 90
            if(USART1_RxStruct.Buff[1]==E_8421temp && USART1_RxStruct.Buff[2]==0xc1)//ָ����ַ�Ĵӻ��ٶ�
            {
                U_Speed=USART1_RxStruct.Buff[3];
            }
            /*----------------------------------------------*/
            //�������Ͷ�ȡ���Ӳ���Ϣ���ӻ��յ���Ϣ�᷵�����Ӳ�״̬��\
                            0     1       2     3\
            �ٶȱ�׼����֡��EB �ӻ���ַ ״̬λ   90
            //�յ����ݣ����������Ӳ�״̬��
            if(USART1_RxStruct.Buff[1]==E_8421temp && USART1_RxStruct.Buff[2]==0xD1)
            {
				//����ģʽ
                HAL_GPIO_WritePin(RS485_RE_GPIO_Port,RS485_RE_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(led1_GPIO_Port,led1_Pin,GPIO_PIN_SET);
                TxCMD[0]=0xEB;//֡ͷ
                TxCMD[1]=USART1_RxStruct.Buff[1];//�ӻ���ַ
                TxCMD[2]=SeedBCondition;//���Ӳ�״̬Seed bin condition
                TxCMD[3]=M2Speed;//���͵���ٶ�
                TxCMD[4]=M1Speed;//��������ٶ�
                TxCMD[5]=0x90;//����β
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

//��������ж�
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	//����ģʽ
	HAL_GPIO_WritePin(RS485_RE_GPIO_Port,RS485_RE_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led1_GPIO_Port,led1_Pin,GPIO_PIN_RESET);
}





