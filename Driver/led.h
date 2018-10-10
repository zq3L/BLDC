/*
Decription	:
Author		:Alan Zhang
Date		:2018-10-07 00:11:21
Version		:1.0.0
*/
#ifndef _LED_H_
#define _LED_H_

#include "typedef.h"

typedef enum
{
    LedStateOff = 0 ,
    LedStateOn
}LedState ;

#ifdef __cplusplus
extern C{
#endif

void ledInit(void);
Bool ledSetState(u8 index,LedState state);
LedState ledGetState(u8 index);


#ifdef __cplusplus
}
#endif
#endif
