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
    PWR_BackupAccessCmd(ENABLE);
    RCC_LSEConfig(RCC_LSE_OFF);
    RCC_HSEConfig(RCC_HSE_OFF);
    PWR_BackupAccessCmd(DISABLE);
    
    RCC_PLLCmd(DISABLE);
  
    RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_12);
    RCC_PLLCmd(ENABLE);
    
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    RCC_PCLK1Config(RCC_HCLK_Div2);
    RCC_PCLK2Config(RCC_HCLK_Div1);
    
    RCC_ADCCLKConfig(RCC_PCLK2_Div4);

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    // 这里做一下 remap OSCIO
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO|RCC_APB2Periph_ADC1,ENABLE);

    
    
    GPIO_PinRemapConfig(GPIO_Remap_PD01, ENABLE);
}

