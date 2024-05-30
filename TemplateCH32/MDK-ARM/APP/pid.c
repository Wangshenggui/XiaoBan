#include "pid.h"


PID_TypeDef  g_speed_pid1;           /* �ٶȻ�PID�����ṹ�� */
PID_TypeDef  g_speed_pid2;           /* �ٶȻ�PID�����ṹ�� */


void pid_init(void)
{
    g_speed_pid1.SetPoint = 0;       /* �趨Ŀ��ֵ */
    g_speed_pid1.ActualValue = 0.0;  /* �������ֵ */
    g_speed_pid1.SumError = 0.0;     /* ����ֵ */
    g_speed_pid1.Error = 0.0;        /* Error[1] */
    g_speed_pid1.LastError = 0.0;    /* Error[-1] */
    g_speed_pid1.PrevError = 0.0;    /* Error[-2] */
    g_speed_pid1.Proportion = KP1;    /* �������� Proportional Const */
    g_speed_pid1.Integral = KI1;      /* ���ֳ��� Integral Const */
    g_speed_pid1.Derivative = KD1;    /* ΢�ֳ��� Derivative Const */
    
    g_speed_pid2.SetPoint = 0;       /* �趨Ŀ��ֵ */
    g_speed_pid2.ActualValue = 0.0;  /* �������ֵ */
    g_speed_pid2.SumError = 0.0;     /* ����ֵ */
    g_speed_pid2.Error = 0.0;        /* Error[1] */
    g_speed_pid2.LastError = 0.0;    /* Error[-1] */
    g_speed_pid2.PrevError = 0.0;    /* Error[-2] */
    g_speed_pid2.Proportion = KP2;    /* �������� Proportional Const */
    g_speed_pid2.Integral = KI2;      /* ���ֳ��� Integral Const */
    g_speed_pid2.Derivative = KD2;    /* ΢�ֳ��� Derivative Const */
}


int32_t increment_pid_ctrl(PID_TypeDef *PID,float Feedback_value)
{
    PID->Error = (float)(PID->SetPoint - Feedback_value);                   /* ����ƫ�� */
    
#if  INCR_LOCT_SELECT                                                       /* ����ʽPID */
    
    PID->ActualValue += (PID->Proportion * (PID->Error - PID->LastError))                          /* �������� */
                        + (PID->Integral * PID->Error)                                             /* ���ֻ��� */
                        + (PID->Derivative * (PID->Error - 2 * PID->LastError + PID->PrevError));  /* ΢�ֻ��� */
    
    PID->PrevError = PID->LastError;                                        /* �洢ƫ������´μ��� */
    PID->LastError = PID->Error;
    
#else                                                                       /* λ��ʽPID */
    
    PID->SumError += PID->Error;

    PID->ActualValue = (PID->Proportion * PID->Error)                       /* �������� */
                       + (PID->Integral * PID->SumError)                    /* ���ֻ��� */
                       + (PID->Derivative * (PID->Error - PID->LastError)); /* ΢�ֻ��� */
    PID->LastError = PID->Error;
    
    
#endif
    if(PID->ActualValue > 100)                      /* ����޷� */
    {
        PID->ActualValue = 100;
    }
    else if(PID->ActualValue < -100)
    {
        PID->ActualValue = -100;
    }
    
    return ((int32_t)(PID->ActualValue));                                   /* ���ؼ�����������ֵ */
}



