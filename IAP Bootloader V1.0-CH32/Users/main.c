/**
 ******************************************************************************
 * @file     main.c
 * @author   正点原子团队(ALIENTEK)
 * @version  V1.0
 * @date     2023-08-01
 * @brief    IAP BootLoader V1.0
 * @license  Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ******************************************************************************
 * @attention
 *
 * 实验平台:正点原子 M48Z-M3最小系统板STM32F103版
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
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

    HAL_Init();                                             /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9);                     /* 设置时钟, 72Mhz */
    delay_init(72);                                         /* 延时初始化 */
    usart_init(115200);                                     /* 初始化串口 */
    led_init();                                             /* 初始化LED */
    key_init();                                             /* 初始化KEY */
    
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
    //判断是否需要升级固件
    if (HAL_GPIO_ReadPin(WKUP_GPIO_PORT, WKUP_GPIO_PIN) == 1)
    {
        delay_ms(100);
        if (HAL_GPIO_ReadPin(WKUP_GPIO_PORT, WKUP_GPIO_PIN) == 1)
        {
            //进入固件升级
            while (1)
            {
                if (g_usart_rx_cnt)
                {
                    if (lastcount == g_usart_rx_cnt)   /* 新周期内,没有收到任何数据,认为本次数据接收完成 */
                    {
                        applenth = g_usart_rx_cnt;
                        lastcount = 0;
                        g_usart_rx_cnt = 0;
//                        printf("用户程序接收完成!\r\n");
//                        printf("代码长度:%dBytes\r\n", applenth);

                        delay_ms(50);
                        if (applenth != 0)
                        {
//                            printf("开始更新固件...\r\n");
//                            printf("Copying APP2FLASH...\r\n");
                            if (((*(volatile uint32_t*)(RAMARRER + 4)) & 0xFF000000) == 0x08000000)
                            {
                                iap_write_appbin(FLASH_APP1_ADDR, g_usart_rx_buf, applenth);
//                                printf("Copy APP Successed!!\r\n");
//                                printf("固件更新完成!\r\n");

                                delay_ms(50);
//                                printf("flash addr :%x \r\n", (*(volatile uint32_t*)(FLASH_APP1_ADDR + 4)) & 0xFF000000);

                                if (((*(volatile uint32_t*)(FLASH_APP1_ADDR + 4)) & 0xFF000000) == 0x08000000)
                                {
//                                    printf("开始执行FLASH用户代码!!\r\n\r\n");
                                    delay_ms(10);
                                    iap_load_app(FLASH_APP1_ADDR);
                                }
                                else
                                {
//                                    printf("没有可以运行的固件!\r\n");
//                                    printf("No APP!\r\n");
                                }
                            }
                            else
                            {
//                                printf("Illegal FLASH APP!  \r\n");
//                                printf("非FLASH应用程序!\r\n");
                            }
                        }
                        else
                        {
//                            printf("没有可以更新的固件!\r\n");
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

        //运行APP
        while (1)
        {
            if (((*(volatile uint32_t*)(FLASH_APP1_ADDR + 4)) & 0xFF000000) == 0x08000000)
            {
//                printf("开始执行FLASH用户代码!!\r\n\r\n");
                delay_ms(10);
                iap_load_app(FLASH_APP1_ADDR);
            }
            else
            {
                //如果没有APP，跳转到固件升级代码
//                printf("没有可以运行的固件!\r\n");
//                printf("No APP!\r\n");
                goto BOOT;
            }
        }
}
