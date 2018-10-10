/*
Decription	:
Author		:Alan Zhang
Date		:2018-10-07 00:11:34
Version		:1.0.0
*/
#include "main.h"


#include "stm32f10x.h"


int main(void)
{
    unsigned char i = 0 ;
    SystemInit();
    rccInit();
    ledInit();
    keyInit();
    sysTickInit();
    while(1)
    {
        keyRun();
        for(i=0;i<KeySum;i++)
        {
            if(KeyStateClick == keyGetState((KeyIndex)(KeyIndex0+i)))
            {
                ledGetState(0) == LedStateOff ? ledSetState(0, LedStateOn):ledSetState(0, LedStateOff);
            }
        }
        systickDelay(20);
    }
}

