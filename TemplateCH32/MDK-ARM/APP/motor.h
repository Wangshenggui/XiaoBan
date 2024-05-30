#ifndef _MOTOR_H
#define _MOTOR_H

#include "motor_encode.h"
#include "tim.h"

//串口接收的速度
extern uint8_t U_Speed;

void SetMotorPWM(bool bit,int32_t pwm);
void SetMotorCCW(bool bit,GPIO_PinState state);




#endif
