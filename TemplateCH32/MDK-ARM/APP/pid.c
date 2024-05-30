#include "pid.h"


PID_TypeDef  g_speed_pid1;           /* 速度环PID参数结构体 */
PID_TypeDef  g_speed_pid2;           /* 速度环PID参数结构体 */


void pid_init(void)
{
    g_speed_pid1.SetPoint = 0;       /* 设定目标值 */
    g_speed_pid1.ActualValue = 0.0;  /* 期望输出值 */
    g_speed_pid1.SumError = 0.0;     /* 积分值 */
    g_speed_pid1.Error = 0.0;        /* Error[1] */
    g_speed_pid1.LastError = 0.0;    /* Error[-1] */
    g_speed_pid1.PrevError = 0.0;    /* Error[-2] */
    g_speed_pid1.Proportion = KP1;    /* 比例常数 Proportional Const */
    g_speed_pid1.Integral = KI1;      /* 积分常数 Integral Const */
    g_speed_pid1.Derivative = KD1;    /* 微分常数 Derivative Const */
    
    g_speed_pid2.SetPoint = 0;       /* 设定目标值 */
    g_speed_pid2.ActualValue = 0.0;  /* 期望输出值 */
    g_speed_pid2.SumError = 0.0;     /* 积分值 */
    g_speed_pid2.Error = 0.0;        /* Error[1] */
    g_speed_pid2.LastError = 0.0;    /* Error[-1] */
    g_speed_pid2.PrevError = 0.0;    /* Error[-2] */
    g_speed_pid2.Proportion = KP2;    /* 比例常数 Proportional Const */
    g_speed_pid2.Integral = KI2;      /* 积分常数 Integral Const */
    g_speed_pid2.Derivative = KD2;    /* 微分常数 Derivative Const */
}


int32_t increment_pid_ctrl(PID_TypeDef *PID,float Feedback_value)
{
    PID->Error = (float)(PID->SetPoint - Feedback_value);                   /* 计算偏差 */
    
#if  INCR_LOCT_SELECT                                                       /* 增量式PID */
    
    PID->ActualValue += (PID->Proportion * (PID->Error - PID->LastError))                          /* 比例环节 */
                        + (PID->Integral * PID->Error)                                             /* 积分环节 */
                        + (PID->Derivative * (PID->Error - 2 * PID->LastError + PID->PrevError));  /* 微分环节 */
    
    PID->PrevError = PID->LastError;                                        /* 存储偏差，用于下次计算 */
    PID->LastError = PID->Error;
    
#else                                                                       /* 位置式PID */
    
    PID->SumError += PID->Error;

    PID->ActualValue = (PID->Proportion * PID->Error)                       /* 比例环节 */
                       + (PID->Integral * PID->SumError)                    /* 积分环节 */
                       + (PID->Derivative * (PID->Error - PID->LastError)); /* 微分环节 */
    PID->LastError = PID->Error;
    
    
#endif
    if(PID->ActualValue > 100)                      /* 输出限幅 */
    {
        PID->ActualValue = 100;
    }
    else if(PID->ActualValue < -100)
    {
        PID->ActualValue = -100;
    }
    
    return ((int32_t)(PID->ActualValue));                                   /* 返回计算后输出的数值 */
}



