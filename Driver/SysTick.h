/*
Decription	:
Author		:Alan Zhang
Date		:2018-08-18 16:37:56
Version		:1.0.0
*/
#ifndef _SYSTICK_H_
#define _SYSTICK_H_

#include "stm32f10x.h"

#define SYSTICK_NEW_MS_FLAG 0x01
#define SYSTICK_NEW_S_FLAG  0x02

#ifdef __cplusplus
extern C{
#endif

void sysTickInit(void);
void sysTickItHandle(void);
u16 sysTickGetMsCounter(void);
u32 sysTickGetSCounter(void);
u8 sysTickGetFlag(void);
void systickDelay(u32 msCouter);


#ifdef __cplusplus
}
#endif
#endif
