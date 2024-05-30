#include "tim_it.h"
#include <stdio.h>
#include <string.h>
#include "usart.h"
#include "iwdg.h"
#include "usart_it.h"

#include "fft.h"


MotorJamStructure1 MotorJamStruct1 = { 0 };
MotorJamStructure2 MotorJamStruct2 = { 0 };

void JamTask1(void);
void JamTask2(void);

//一定周期内多次卡住
uint16_t Jam_n=0;
uint8_t Jam_Flag=0;

//
uint64_t start_n=0;

uint8_t FFT_Flag=0;
uint16_t i=0;
float buff[FFT_LENGTH];


extern uint8_t SSS;



//记录卡顿的脉冲
uint16_t KartunPulse=10000;



void myHAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
    static uint16_t tim4_n = 0;

    //20ms中断一次
    if (htim->Instance == TIM4)
    {
        tim4_n++;
        if (tim4_n == 5)
        {
			tim4_n=0;
            //获取速度
            M1Speed = GetMotorSpeed(0);
            M2Speed = GetMotorSpeed(1);
        }
        
        static uint8_t start_flag=0;
        UNUSED(start_flag);
        
//        U_Speed=0x40;
        if (U_Speed > 0 && U_Speed <= 0x40)
        {
            //辅助轮固定速度
            g_speed_pid1.SetPoint = 0x40;
            g_speed_pid2.SetPoint = U_Speed;
            
            SetMotorPWM(0, increment_pid_ctrl(&g_speed_pid1, M1Speed));
            SetMotorPWM(1, increment_pid_ctrl(&g_speed_pid2, M2Speed));
            
			/*
            static uint16_t bbb=0;
            bbb++;
            if(bbb==100)
            {
                SetMotorCCW(0, GPIO_PIN_RESET);
                SetMotorCCW(1, GPIO_PIN_RESET);
                SetMotorPWM(0, 40);
                SetMotorPWM(1, 40);
            }
            if(bbb==200)
            {
                bbb=0;
                SetMotorCCW(0, GPIO_PIN_SET);
                SetMotorCCW(1, GPIO_PIN_SET);
                SetMotorPWM(0, 90);
                SetMotorPWM(1, 90);
            }
			*/
            
            
            if(start_n==1)
                start_n=2;
        }
        else
        {
            SetMotorPWM(0, 0);
            SetMotorPWM(1, 0);
            
            start_n=0;
        }
        
        //记录输出值
        MotorJamStruct1.PWM=TIM3->CCR1;
        MotorJamStruct2.PWM=TIM3->CCR2;
        //记录速度值
        MotorJamStruct1.Speed=M1Speed;
        MotorJamStruct2.Speed=M2Speed;
        
        start_n++;
        if(start_n>=10)
        {
            if(MotorJamStruct1.JamFlag==0)
            {
                //判断电机状态
                JamTask1();
            }
            else
            {
                if(MotorJamStruct1.Reversal_n++==ReversalTimer1)
                {
                    MotorJamStruct1.Reversal_n=0;
                    MotorJamStruct1.JamFlag=0;//清除卡住标志
                    SetMotorCCW(0, GPIO_PIN_SET);
                }
            }
            
            if(MotorJamStruct2.JamFlag==0)
            {
                //判断电机状态
                JamTask2();
            }
            else
            {
                if(MotorJamStruct2.Reversal_n++==ReversalTimer2)
                {
                    MotorJamStruct2.Reversal_n=0;
                    MotorJamStruct2.JamFlag=0;//清除卡住标志
                    SetMotorCCW(1, GPIO_PIN_SET);
                }
            }
        }
        
        
        
        
        //通电--运行
        if (U_Speed > 0 && U_Speed <= 0x40)
        {
            //运行
            if(MotorJamStruct1.JamFlag==0 && MotorJamStruct2.JamFlag==0)
            {
                SeedBCondition=2;
            }
            else if(MotorJamStruct1.JamFlag==0 || MotorJamStruct2.JamFlag==0)
            {
                SeedBCondition=3;
            }
        }
        else
        {
            SeedBCondition=1;
        }
        
    }
}

void JamTask1()
{
    //最大输出
    if(MotorJamStruct1.PWM>=99)
//    if(1)
    {
        //卡住
        if(MotorJamStruct1.Speed<=JamThreshold1)
//        if(1)
        {
            //认为卡死
            if(MotorJamStruct1.JamT++>JamTimer1)
            {
                MotorJamStruct1.JamT=0;
                
                //设置卡住标志
                MotorJamStruct1.JamFlag=1;
                //启动电机反转
                SetMotorCCW(0, GPIO_PIN_RESET);
                
                
                
                MotorJamStruct2.JamT=0;
                
                //设置卡住标志
                MotorJamStruct2.JamFlag=1;
                //启动电机反转
                SetMotorCCW(1, GPIO_PIN_RESET);
                //以固定速度反转
                g_speed_pid2.SetPoint=0x30;
            }
        }
    }
    else
    {
        MotorJamStruct1.JamT=0;
    }
}

uint8_t Tim_Flag=1;
uint8_t Number=0;
void JamTask2()
{
    //最大输出
    if(MotorJamStruct2.PWM>=99)
//    if(1)
    {
        //卡住
        if(MotorJamStruct2.Speed<=JamThreshold2)
//        if(1)
        {
            //认为卡死
            if(MotorJamStruct2.JamT++>JamTimer2)
            {
                MotorJamStruct2.JamT=0;
                
                //设置卡住标志
                MotorJamStruct2.JamFlag=1;
                //启动电机反转
                SetMotorCCW(1, GPIO_PIN_RESET);
                //以固定速度反转
                g_speed_pid2.SetPoint=0x30;
                
                
                KartunPulse=10000;
                
                
                
                if(Tim_Flag==1)
                {
                    Number=0;
                    Tim_Flag=0;
                    HAL_TIM_Base_Stop_IT(&htim2);
                    //启动计数器
                    HAL_TIM_Base_Start_IT(&htim2);
                }
            }
        }
    }
    else
    {
        MotorJamStruct2.JamT=0;
    }
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    myHAL_TIM_PeriodElapsedCallback(htim);
    
    
    static uint16_t tim2_n=0;
    static uint8_t nn=0;
    if(htim->Instance==TIM2)
    {
        tim2_n++;
        //计数器计时10*tim2_n ms
        if(tim2_n==50)
        {
            tim2_n=0;
//            printf("进入%d次\r\n",Number+1);
            
            #include <stdlib.h>
            if(abs(KartunPulse-10000) < (9.765625*U_Speed)/4)
            {
                nn++;
//                printf("卡%d次\r\n",nn);
            }
            else
            {
//                printf("不卡\r\n");
                nn=0;
                HAL_TIM_Base_Stop_IT(&htim2);
                Number=0;
                Tim_Flag=1;
            }
            
            Number++;
            if(Number==10)
            {
                Number=0;
                Tim_Flag=1;
                if(nn==10)
                {
                    nn=0;
                    HAL_TIM_Base_Stop_IT(&htim4);
                    SetMotorCCW(0, GPIO_PIN_SET);
                    SetMotorCCW(1, GPIO_PIN_SET);
                    SetMotorPWM(0, 0);
                    SetMotorPWM(1, 0);
                    
                    
                    HAL_TIM_Base_Stop_IT(&htim2);
//                    HAL_IWDG_Refresh(&hiwdg);
                    
//                    printf("停止%d\r\n",Tim_Flag);
                    while(1);
                }
                nn=0;
                HAL_TIM_Base_Stop_IT(&htim2);
            }
        }
    }
}



