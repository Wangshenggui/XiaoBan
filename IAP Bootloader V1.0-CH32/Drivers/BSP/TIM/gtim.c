/**
 ****************************************************************************************************
 * @file        gtim.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2023-08-01
 * @brief       ͨ�ö�ʱ�� ��������
 * @license     Copyright (c) 2020-2032, �������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� M48Z-M3��Сϵͳ��STM32F103��
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "./BSP/TIM/gtim.h"
#include "./BSP/LED/led.h"


TIM_HandleTypeDef g_timx_handle;  /* ��ʱ��x��� */

/**
 * @brief       ͨ�ö�ʱ��TIMX��ʱ�жϳ�ʼ������
 * @note
 *              ͨ�ö�ʱ����ʱ������APB1,��PPRE1 �� 2��Ƶ��ʱ��
 *              ͨ�ö�ʱ����ʱ��ΪAPB1ʱ�ӵ�2��, ��APB1Ϊ36M, ���Զ�ʱ��ʱ�� = 72Mhz
 *              ��ʱ�����ʱ����㷽��: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=��ʱ������Ƶ��,��λ:Mhz
 *
 * @param       arr: �Զ���װֵ��
 * @param       psc: ʱ��Ԥ��Ƶ��
 * @retval      ��
 */
void gtim_timx_init(uint16_t arr, uint16_t psc)
{
    GTIM_TIMX_INT_CLK_ENABLE();                                 /* ʹ��TIMxʱ�� */

    g_timx_handle.Instance = GTIM_TIMX_INT;                     /* ͨ�ö�ʱ��x */
    g_timx_handle.Init.Prescaler = psc;                         /* Ԥ��Ƶϵ�� */
    g_timx_handle.Init.CounterMode = TIM_COUNTERMODE_UP;        /* ��������ģʽ */
    g_timx_handle.Init.Period = arr;                            /* �Զ�װ��ֵ */
    HAL_TIM_Base_Init(&g_timx_handle);

    HAL_NVIC_SetPriority(GTIM_TIMX_INT_IRQn, 1, 3);             /* �����ж����ȼ�����ռ���ȼ�1�������ȼ�3 */
    HAL_NVIC_EnableIRQ(GTIM_TIMX_INT_IRQn);                     /* ����ITMx�ж� */

    HAL_TIM_Base_Start_IT(&g_timx_handle);                      /* ʹ�ܶ�ʱ��x�Ͷ�ʱ��x�����ж� */
}

/**
 * @brief       ��ʱ���жϷ�����
 * @param       ��
 * @retval      ��
 */
void GTIM_TIMX_INT_IRQHandler(void)
{
    /* ���´���û��ʹ�ö�ʱ��HAL�⹲�ô�������������������ֱ��ͨ���ж��жϱ�־λ�ķ�ʽ */
    if(__HAL_TIM_GET_FLAG(&g_timx_handle, TIM_FLAG_UPDATE) != RESET)
    {
        LED0_TOGGLE();
        __HAL_TIM_CLEAR_IT(&g_timx_handle, TIM_IT_UPDATE);      /* �����ʱ������жϱ�־λ */
    }
}