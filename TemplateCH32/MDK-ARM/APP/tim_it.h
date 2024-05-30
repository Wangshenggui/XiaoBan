#ifndef _TIM_IT_H
#define _TIM_IT_H

#include "main.h"
#include "pid.h"
#include "motor_encode.h"
#include "motor.h"


//卡住阈值，当速度值小于该值时认为卡住
#define JamThreshold1 0
#define JamThreshold2 0

//卡住时间，当卡住次数超过该值时触发卡住处理
#define JamTimer1 0
#define JamTimer2 0

//反转时间，反转计数到该值时解除卡住状态
#define ReversalTimer1 8
#define ReversalTimer2 7

typedef struct
{
    uint8_t PWM;
    uint8_t Speed;
    uint8_t JamT;
    uint8_t JamFlag;//卡住标志
    uint8_t Reversal_n;//反转计数
}MotorJamStructure1;

typedef struct
{
    uint8_t PWM;
    uint8_t Speed;
    uint8_t JamT;
    uint8_t JamFlag;//卡住标志
    uint8_t Reversal_n;//反转计数
}MotorJamStructure2;


void myHAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);




#endif
