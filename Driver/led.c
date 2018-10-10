/*
Decription	:
Author		:Alan Zhang
Date		:2018-10-07 00:11:21
Version		:1.0.0
*/
#include "led.h"
#include "stm32f10x.h"
#include "typedef.h"
#include "gpio.h"


typedef struct
{
    u8 index        : 7 ;
    LedState state  : 1 ;
}Led ;

static const GPIO ledIos[] = 
{
    {GPIOB,GPIO_Pin_9},
};

static Led leds[] = 
{
    {0,LedStateOff},
};

static void ledHardwareInit(void)
{
    u8 i = 0 ;
    GPIO_InitTypeDef GPIO_InitStruct ;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP ;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz ;
    for(;i<COUNTER_OF_ITEM(ledIos, GPIO);i++)
    {
        GPIO_InitStruct.GPIO_Pin  = ledIos[i].pins ;
        GPIO_Init(ledIos[i].port,&GPIO_InitStruct);
        leds[i].state == LedStateOff ?GPIO_ResetBits(ledIos[i].port, ledIos[i].pins):GPIO_SetBits(ledIos[i].port, ledIos[i].pins);
    }
}

static Led* ledGetElementByIndex(u8 index)
{
    u8 i = 0 ;
    for(;i<COUNTER_OF_ITEM(leds, Led);i++)
    {
        if(index == leds[i].index)
        {
            return leds+i ;
        }
    }
    return (Led*)0;
}

Bool ledSetState(u8 index, LedState state)
{
    Led* pLed = ledGetElementByIndex(index);

    if(pLed)
    {
        if(state != pLed->state)
        {
            pLed->state = state ;
            state == LedStateOff ? GPIO_ResetBits(ledIos[pLed->index].port,ledIos[pLed->index].pins):GPIO_SetBits(ledIos[pLed->index].port,ledIos[pLed->index].pins) ;
        }
        return true ;
    }else{
        return false ;
    }
}


LedState ledGetState(u8 index)
{
    Led* pLed = ledGetElementByIndex(index);
    if(pLed)
    {
        return pLed->state ;
    }else{
        return LedStateOff ;
    }
}


void ledInit(void)
{
    ledHardwareInit();
}

