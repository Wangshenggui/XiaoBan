#ifndef _PID_H
#define _PID_H

#include "main.h"

#define  INCR_LOCT_SELECT  1         /* 0：位置式 ，1：增量式 */

#if INCR_LOCT_SELECT

/* 增量式PID参数相关宏 */
//#define  KP1      0.4f               /* P参数*/
//#define  KI1      0.15f               /* I参数*/
//#define  KD1      0.0f                /* D参数*/

#define  KP1      0.30f               /* P参数*/
#define  KI1      0.15f               /* I参数*/
#define  KD1      0.0f                /* D参数*/

//#define  KP2      0.5f               /* P参数*/
//#define  KI2      0.25f               /* I参数*/
//#define  KD2      0.0f                /* D参数*/

#define  KP2      0.20f               /* P参数*/
#define  KI2      0.07f               /* I参数*/
#define  KD2      0.0f                /* D参数*/

#else

#define  KP1      0.8f               /* P参数*/
#define  KI1      0.25f               /* I参数*/
#define  KD1      0.0f                /* D参数*/

#define  KP2      0.8f               /* P参数*/
#define  KI2      0.25f               /* I参数*/
#define  KD2      0.0f                /* D参数*/

#endif


/* PID参数结构体 */
typedef struct
{
    __IO float  SetPoint;            /* 设定目标 */
    __IO float  ActualValue;         /* 期望输出值 */
    __IO float  SumError;            /* 误差累计 */
    __IO float  Proportion;          /* 比例常数 P */
    __IO float  Integral;            /* 积分常数 I */
    __IO float  Derivative;          /* 微分常数 D */
    __IO float  Error;               /* Error[1] */
    __IO float  LastError;           /* Error[-1] */
    __IO float  PrevError;           /* Error[-2] */
} PID_TypeDef;

extern PID_TypeDef  g_speed_pid1;

extern PID_TypeDef  g_speed_pid2;

void pid_init(void);
int32_t increment_pid_ctrl(PID_TypeDef *PID,float Feedback_value);




#endif
