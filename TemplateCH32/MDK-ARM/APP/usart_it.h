#ifndef _USART_IT_H
#define _USART_IT_H

#include "main.h"
#include "usart.h"

#define Rx_LENG 200

extern UART_HandleTypeDef huart1;

extern uint8_t usart_rxFlag;

extern uint8_t SeedBCondition;

typedef struct
{
    uint8_t receive;
    uint8_t Rx_Buff[Rx_LENG];
    uint8_t Rx_len;
    uint8_t Buff[Rx_LENG];
}USART1_RxStructure;
extern USART1_RxStructure USART1_RxStruct;

void USART1_IDLE_Handler(void);




#endif
