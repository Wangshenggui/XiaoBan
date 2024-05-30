/**
 ******************************************************************************
 * @file     main.c
 * @author   ����ԭ���Ŷ�(ALIENTEK)
 * @version  V1.0
 * @date     2023-08-01
 * @brief    IAP BootLoader V1.0
 * @license  Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ******************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� M48Z-M3��Сϵͳ��STM32F103��
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 ******************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./IAP/iap.h"
#include "./BSP/KEY/key.h"


int main(void)
{
    uint32_t lastcount = 0;
    uint32_t applenth = 0;
    uint8_t clearflag = 0;
    uint8_t t = 0;
    uint8_t key;

    HAL_Init();                                             /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9);                     /* ����ʱ��, 72Mhz */
    delay_init(72);                                         /* ��ʱ��ʼ�� */
    usart_init(115200);                                     /* ��ʼ������ */
    led_init();                                             /* ��ʼ��LED */
    key_init();                                             /* ��ʼ��KEY */
    
//    printf("IAP Bootloader\r\n");

    delay_ms(500);
//    printf("IAP Bootloader\r\n");

//    while(1)
//    {
//    LED0_TOGGLE();
//                LED1_TOGGLE();
//                delay_ms(50);
//    }

BOOT:
    //�ж��Ƿ���Ҫ�����̼�
    if (HAL_GPIO_ReadPin(WKUP_GPIO_PORT, WKUP_GPIO_PIN) == 1)
    {
        delay_ms(100);
        if (HAL_GPIO_ReadPin(WKUP_GPIO_PORT, WKUP_GPIO_PIN) == 1)
        {
            //����̼�����
            while (1)
            {
                if (g_usart_rx_cnt)
                {
                    if (lastcount == g_usart_rx_cnt)   /* ��������,û���յ��κ�����,��Ϊ�������ݽ������ */
                    {
                        applenth = g_usart_rx_cnt;
                        lastcount = 0;
                        g_usart_rx_cnt = 0;
//                        printf("�û�����������!\r\n");
//                        printf("���볤��:%dBytes\r\n", applenth);

                        delay_ms(50);
                        if (applenth != 0)
                        {
//                            printf("��ʼ���¹̼�...\r\n");
//                            printf("Copying APP2FLASH...\r\n");
                            if (((*(volatile uint32_t*)(RAMARRER + 4)) & 0xFF000000) == 0x08000000)
                            {
                                iap_write_appbin(FLASH_APP1_ADDR, g_usart_rx_buf, applenth);
//                                printf("Copy APP Successed!!\r\n");
//                                printf("�̼��������!\r\n");

                                delay_ms(50);
//                                printf("flash addr :%x \r\n", (*(volatile uint32_t*)(FLASH_APP1_ADDR + 4)) & 0xFF000000);

                                if (((*(volatile uint32_t*)(FLASH_APP1_ADDR + 4)) & 0xFF000000) == 0x08000000)
                                {
//                                    printf("��ʼִ��FLASH�û�����!!\r\n\r\n");
                                    delay_ms(10);
                                    iap_load_app(FLASH_APP1_ADDR);
                                }
                                else
                                {
//                                    printf("û�п������еĹ̼�!\r\n");
//                                    printf("No APP!\r\n");
                                }
                            }
                            else
                            {
//                                printf("Illegal FLASH APP!  \r\n");
//                                printf("��FLASHӦ�ó���!\r\n");
                            }
                        }
                        else
                        {
//                            printf("û�п��Ը��µĹ̼�!\r\n");
//                            printf("No APP!\r\n");
                        }
                    }
                    else
                    {
                        lastcount = g_usart_rx_cnt;
                    }
                }
                LED0_TOGGLE();
                LED1_TOGGLE();
                delay_ms(30);
            }
        }
    }
    else

        //����APP
        while (1)
        {
            if (((*(volatile uint32_t*)(FLASH_APP1_ADDR + 4)) & 0xFF000000) == 0x08000000)
            {
//                printf("��ʼִ��FLASH�û�����!!\r\n\r\n");
                delay_ms(10);
                iap_load_app(FLASH_APP1_ADDR);
            }
            else
            {
                //���û��APP����ת���̼���������
//                printf("û�п������еĹ̼�!\r\n");
//                printf("No APP!\r\n");
                goto BOOT;
            }
        }
}
