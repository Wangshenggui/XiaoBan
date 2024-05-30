#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "main.h"


void delay_us(int16_t nus);
void HAL_Delay(uint32_t Delay);

#define delay_ms HAL_Delay



#endif
