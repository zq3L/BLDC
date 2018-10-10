/*
Decription	:
Author		:Alan Zhang
Date		:2018-08-18 16:37:56
Version		:1.0.0
*/
#include "SysTick.h"



typedef struct
{
    u8 flag ;
    u32 sCounter ;
    u16 msCounter ;
}SystickCounter ;

static SystickCounter mySystickCounter ;

void sysTickInit(void)
{
    
    mySystickCounter.msCounter = 0 ;
    mySystickCounter.sCounter = 0 ;
    mySystickCounter.flag = 0 ;
    SysTick_Config(6000);
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8) ;
}

void sysTickItHandle(void)
{
    mySystickCounter.flag |= SYSTICK_NEW_MS_FLAG ;
    if(++mySystickCounter.msCounter >= 1000)
    {
        mySystickCounter.flag |= SYSTICK_NEW_S_FLAG ;
        mySystickCounter.msCounter = 0 ;
        mySystickCounter.sCounter++ ;
    }
}

u16 sysTickGetMsCounter(void)
{
    return mySystickCounter.msCounter ; 
}


u32 sysTickGetSCounter(void)
{
    return mySystickCounter.sCounter ;
}

u8 sysTickGetFlag(void)
{
    u8 returnValue = mySystickCounter.flag ;
    mySystickCounter.flag = 0 ;
    return returnValue ;
}

void systickDelay(u32 msCouter)
{
    SystickCounter timeUp ;
    timeUp.msCounter = mySystickCounter.msCounter + msCouter%1000 ;

    timeUp.sCounter = timeUp.msCounter/1000 + mySystickCounter.sCounter + msCouter/1000 ;
    timeUp.msCounter %= 1000 ;

    while(1)
    {
        if((mySystickCounter.sCounter >= timeUp.sCounter) && (mySystickCounter.msCounter>= timeUp.msCounter))
        {
            return ;
        }
    }
    
}


