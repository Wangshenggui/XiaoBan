#include "system.h"


void delay_us(int16_t nus) 
{
  int32_t temp; 
  SysTick->LOAD = nus*9; //72MHz
  SysTick->VAL=0X00;
  SysTick->CTRL=0X01;
  do 
  { 
    temp=SysTick->CTRL;
  }
  while((temp&0x01)&&(!(temp&(1<<16))));
     
  SysTick->CTRL=0x00; 
  SysTick->VAL =0X00; 
}

void HAL_Delay(uint32_t Delay)
{
    delay_us(Delay*1000);
}












