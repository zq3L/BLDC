/*
Decription	:
Author		:Alan Zhang
Date		:2018-10-07 16:55:39
Version		:1.0.0
*/
#ifndef _TYPEDEF_H_
#define _TYPEDEF_H_

#include "stm32f10x.h"

#define COUNTER_OF_ITEM(ARRAY_NAME,TYPE) (sizeof(ARRAY_NAME)/sizeof(TYPE))
#define OFF_SET_OF(TYPE,ITEM) (((TYPE*)(void *)0)->(ITEM))


/*
#define CONTAINDER_OF(TYPE,ITEM,pItem,) ((TYPE*)((char*)pItem-(unsigned int)OFF_SET_OF(TYPE, ITEM)))
#define GET_ITEM_VALUE(pVALUE,TYPE,ITEM,ITEM_SIZE) (((unsigned long*)(pVALUE+OFF_SET_OF(TYPE, ITEM)))>>(sizeof(long) - ITEM_SIZE))   
*/

#ifdef __cplusplus
extern C{
#endif

typedef enum
{
    false = 0 ,
    true ,
}Bool ;




#ifdef __cplusplus
}
#endif
#endif
