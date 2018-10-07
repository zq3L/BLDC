/*
Decription	:
Author		:Alan Zhang
Date		:2018-10-07 08:00:06
Version		:1.0.0
*/
#include "rcc.h"

#include "stm32f10x.h"

void rccInit(void)
{
    RCC_PLLCmd(DISABLE);
  
    RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_12);
    RCC_PLLCmd(ENABLE);
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    RCC_PCLK1Config(RCC_HCLK_Div2);
    RCC_PCLK2Config(RCC_HCLK_Div1);
}

