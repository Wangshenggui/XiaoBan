#include "motor_encode.h"
#include <stdlib.h>
#include <stdio.h>


uint16_t M1Speed=0;
uint16_t M2Speed=0;

uint16_t GetMotorSpeed(bool bit)
{
    uint16_t temp;
    
//    temp=!bit?EXTI6_N:EXTI7_N;
//    !bit?(EXTI6_N=0):(EXTI7_N=0);
//    
//    return temp;
    
    if(!bit)
    {
        temp=abs((short)EXTI6_N);
        EXTI6_N=0;
    }
    else
    {
        temp=abs((short)EXTI7_N);
        EXTI7_N=0;
    }
    return temp;
}



