/*
Decription	:
Author		:Alan Zhang
Date		:2018-10-07 00:11:34
Version		:1.0.0
*/
#include "main.h"
#include <stdio.h>


unsigned int adcValue = 0 ;
char strBuffer[20] = {0} ;

int main(void)
{
    driverInit();
    nokia5110Init();
    adcInit();
    while(1)
    {
        
    }
}

