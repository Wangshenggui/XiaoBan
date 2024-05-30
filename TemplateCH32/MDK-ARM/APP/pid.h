#ifndef _PID_H
#define _PID_H

#include "main.h"

#define  INCR_LOCT_SELECT  1         /* 0��λ��ʽ ��1������ʽ */

#if INCR_LOCT_SELECT

/* ����ʽPID������غ� */
//#define  KP1      0.4f               /* P����*/
//#define  KI1      0.15f               /* I����*/
//#define  KD1      0.0f                /* D����*/

#define  KP1      0.30f               /* P����*/
#define  KI1      0.15f               /* I����*/
#define  KD1      0.0f                /* D����*/

//#define  KP2      0.5f               /* P����*/
//#define  KI2      0.25f               /* I����*/
//#define  KD2      0.0f                /* D����*/

#define  KP2      0.20f               /* P����*/
#define  KI2      0.07f               /* I����*/
#define  KD2      0.0f                /* D����*/

#else

#define  KP1      0.8f               /* P����*/
#define  KI1      0.25f               /* I����*/
#define  KD1      0.0f                /* D����*/

#define  KP2      0.8f               /* P����*/
#define  KI2      0.25f               /* I����*/
#define  KD2      0.0f                /* D����*/

#endif


/* PID�����ṹ�� */
typedef struct
{
    __IO float  SetPoint;            /* �趨Ŀ�� */
    __IO float  ActualValue;         /* �������ֵ */
    __IO float  SumError;            /* ����ۼ� */
    __IO float  Proportion;          /* �������� P */
    __IO float  Integral;            /* ���ֳ��� I */
    __IO float  Derivative;          /* ΢�ֳ��� D */
    __IO float  Error;               /* Error[1] */
    __IO float  LastError;           /* Error[-1] */
    __IO float  PrevError;           /* Error[-2] */
} PID_TypeDef;

extern PID_TypeDef  g_speed_pid1;

extern PID_TypeDef  g_speed_pid2;

void pid_init(void);
int32_t increment_pid_ctrl(PID_TypeDef *PID,float Feedback_value);




#endif
