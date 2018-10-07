/*
Decription	:
Author		:Alan Zhang
Date		:2018-10-07 00:11:34
Version		:1.0.0
*/
#include "main.h"


#include "stm32f10x.h"

void gpioInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct ;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 ;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP ;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz ;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
}

int main(void)
{
    SystemInit();
    rccInit();
    gpioInit();
    sysTickInit();
    while(1)
    {
        systickDelay(1000);
        GPIO_SetBits(GPIOB, GPIO_Pin_9);
        systickDelay(1000);
        GPIO_ResetBits(GPIOB, GPIO_Pin_9);
    }
}

