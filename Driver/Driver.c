/*
Decription	:
Author		:Alan Zhang
Date		:2018-10-21 08:18:48
Version		:1.0.0
*/
#include "stm32f10x.h"
#include "Driver.h"
#include "rcc.h"
#include "led.h"
#include "simSpi.h"
#include "key.h"
#include "systick.h"


static void nvicInit(void)
{
    
}

void driverInit(void)
{
    SystemInit();
    rccInit();
    ledInit();
    keyInit();
    simSpiInit();
    sysTickInit();
    nvicInit();
}

