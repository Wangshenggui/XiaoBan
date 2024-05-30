#include "motor.h"

//串口接收的速度
uint8_t U_Speed=0;

void SetMotorCCW(bool bit,GPIO_PinState state)
{
    !bit?(HAL_GPIO_WritePin(M1_CWCCW_GPIO_Port,M1_CWCCW_Pin,state))\
        :(HAL_GPIO_WritePin(M2_CWCCW_GPIO_Port,M2_CWCCW_Pin,state));
}

void SetMotorPWM(bool bit,int32_t pwm)
{
    if(pwm>100)
        pwm=100;
    if(pwm<-100)
        pwm=-100;
    if(pwm<0)
        pwm=-pwm;
    !bit?(TIM3->CCR1=pwm):(TIM3->CCR2=pwm);
}











