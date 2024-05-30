#include "e_8421.h"


uint8_t GetE_8421()
{
    uint8_t temp;
    
    if(HAL_GPIO_ReadPin(E8421_1_GPIO_Port,E8421_1_Pin)==0)//13579
    {
        if(HAL_GPIO_ReadPin(E8421_2_GPIO_Port,E8421_2_Pin)==0)//37
        {
            if(HAL_GPIO_ReadPin(E8421_4_GPIO_Port,E8421_4_Pin)==0)//7
            {
                temp=7;
            }
            else//3
            {
                temp=3;
            }
        }
        else//159
        {
            if(HAL_GPIO_ReadPin(E8421_4_GPIO_Port,E8421_4_Pin)==0)//5
            {
                temp=5;
            }
            else if(HAL_GPIO_ReadPin(E8421_8_GPIO_Port,E8421_8_Pin)==0)//9
            {
                temp=9;
            }
            else//1
            {
                temp=1;
            }
        }
    }
    else//2468
    {
        if(HAL_GPIO_ReadPin(E8421_2_GPIO_Port,E8421_2_Pin)==0)//26
        {
            if(HAL_GPIO_ReadPin(E8421_4_GPIO_Port,E8421_4_Pin)==0)//6
            {
                temp=6;
            }
            else//2
            {
                temp=2;
            }
        }
        else//48
        {
            if(HAL_GPIO_ReadPin(E8421_4_GPIO_Port,E8421_4_Pin)==0)//4
            {
                temp=4;
            }
            else//8
            {
                temp=8;
            }
        }
    }
    if(HAL_GPIO_ReadPin(E8421_8_GPIO_Port,E8421_8_Pin) 
        && HAL_GPIO_ReadPin(E8421_4_GPIO_Port,E8421_4_Pin) 
    && HAL_GPIO_ReadPin(E8421_2_GPIO_Port,E8421_2_Pin) 
    && HAL_GPIO_ReadPin(E8421_1_GPIO_Port,E8421_1_Pin))
    {
        temp=0;
    }
    
    return temp;
}










