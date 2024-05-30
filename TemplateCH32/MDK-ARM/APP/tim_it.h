#ifndef _TIM_IT_H
#define _TIM_IT_H

#include "main.h"
#include "pid.h"
#include "motor_encode.h"
#include "motor.h"


//��ס��ֵ�����ٶ�ֵС�ڸ�ֵʱ��Ϊ��ס
#define JamThreshold1 0
#define JamThreshold2 0

//��סʱ�䣬����ס����������ֵʱ������ס����
#define JamTimer1 0
#define JamTimer2 0

//��תʱ�䣬��ת��������ֵʱ�����ס״̬
#define ReversalTimer1 8
#define ReversalTimer2 7

typedef struct
{
    uint8_t PWM;
    uint8_t Speed;
    uint8_t JamT;
    uint8_t JamFlag;//��ס��־
    uint8_t Reversal_n;//��ת����
}MotorJamStructure1;

typedef struct
{
    uint8_t PWM;
    uint8_t Speed;
    uint8_t JamT;
    uint8_t JamFlag;//��ס��־
    uint8_t Reversal_n;//��ת����
}MotorJamStructure2;


void myHAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);




#endif
