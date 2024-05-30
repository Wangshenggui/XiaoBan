/**
 ****************************************************************************************************
 * @file        iap.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2023-08-01
 * @brief       IAP ����
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
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

#ifndef __IAP_H
#define __IAP_H

#include "./SYSTEM/sys/sys.h"




typedef void (*iapfun)(void);                   /* ����һ���������͵Ĳ��� */

#define FLASH_APP1_ADDR         0x08008000      /* ��һ��Ӧ�ó�����ʼ��ַ(������ڲ�FLASH)
                                                 * ���� 0X08000000~0X08008FFF(36KB) �Ŀռ�Ϊ Bootloader ʹ��
                                                 */


void iap_load_app(uint32_t appxaddr);   /* ��ת��APP����ִ�� */
void iap_write_appbin(uint32_t appxaddr,uint8_t *appbuf,uint32_t applen);   /* ��ָ����ַ��ʼ,д��bin */

#endif







































