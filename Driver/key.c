/*
Decription	:
Author		:Alan Zhang
Date		:2018-10-07 00:11:17
Version		:1.0.0
*/
#include "key.h"
#include "typedef.h"
#include "gpio.h"


//config 20ms 为单位
#define KEY_LONG_PUSH_MAX           100
#define KEY_LONG_LONG_PUSH_MAX      200

typedef enum
{
    KeyValueNone = 0 ,
    KeyValue0 = (0x01<<0) ,
    KeyValue1 = (0x01<<1) ,
    KeyValue2 = (0x01<<2) ,
    KeyValue3 = (0x01<<3) ,
    KeyValue4 = (0x01<<4) ,
}KeyValue;

typedef struct
{
    KeyIndex index ;
    unsigned short value ;
    unsigned char keyPushedState ;
    unsigned int longPushCounterMax ;
    unsigned int longLongPushCounterMax ;
}KeyInfo ;

typedef struct
{
    const KeyInfo* info ;
    unsigned int counter ;
    KeyState state ;
}Key ;

const GPIO keyIos[KeySum] = 
{
    {GPIOC,GPIO_Pin_13},
    {GPIOC,GPIO_Pin_14},
    {GPIOC,GPIO_Pin_15},
    {GPIOD,GPIO_Pin_0},
    {GPIOD,GPIO_Pin_1},
};

const KeyInfo keyInfos[KeySum] = 
{
    {KeyIndex0,KeyValue0,0,KEY_LONG_PUSH_MAX,KEY_LONG_LONG_PUSH_MAX},
    {KeyIndex1,KeyValue1,0,KEY_LONG_PUSH_MAX,KEY_LONG_LONG_PUSH_MAX},
    {KeyIndex2,KeyValue2,0,KEY_LONG_PUSH_MAX,KEY_LONG_LONG_PUSH_MAX},
    {KeyIndex3,KeyValue3,0,KEY_LONG_PUSH_MAX,KEY_LONG_LONG_PUSH_MAX},
    {KeyIndex4,KeyValue4,0,KEY_LONG_PUSH_MAX,KEY_LONG_LONG_PUSH_MAX},
};

static Key keys[KeySum] ;

static void keySoftwareInit(void)
{
    unsigned char i = 0 ;
    for(;i<KeySum;i++)
    {
        keys[i].counter = 0;
        keys[i].info = keyInfos+i;
        keys[i].state = KeyStateNone ;
    }
}

static void keyHardwareInit(void)
{
    unsigned char i = 0 ;
    GPIO_InitTypeDef GPIO_InitStruct ;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING ;
    for(;i<KeySum;i++)
    {
        GPIO_InitStruct.GPIO_Pin = keyIos[i].pins ;
        GPIO_Init(keyIos[i].port,&GPIO_InitStruct);
    }
}


static unsigned char keyLowLevelGetKeyValue(void)
{
    unsigned char i = 0 ;
    unsigned char returnValue = (unsigned char)KeyValueNone ;
    for(;i<KeySum;i++)
    {
        if(keys[i].info->keyPushedState == (keyIos[i].pins & GPIO_ReadInputData(keyIos[i].port)))
        {
            returnValue |= keys[i].info->value ;
        }else{
            returnValue &= ~keys[i].info->value ;
        }
    }

    return returnValue ;
}

static Key* keyGetByIndex(KeyIndex index)
{
    unsigned char i = 0 ;
    for(;i<COUNTER_OF_ITEM(keys, Key);i++)
    {
        if(index == keys[i].info->index)
        {
            return keys+i ;
        }
    }
    return (Key*)0 ;
}


void keyInit(void)
{
    keySoftwareInit();
    keyHardwareInit();
}

KeyState keyGetState(KeyIndex index)
{
    Key * pKey = keyGetByIndex(index);
    if(pKey)
    {
        return pKey->state ;
    }
    return KeyStateNone ;
}

/*
20ms 调用一次
*/
void keyRun(void)
{
    unsigned char i = 0 ;
    unsigned char currentKeyState = keyLowLevelGetKeyValue();

    if(currentKeyState != KeyValueNone)
    {
        for(;i<KeySum;i++)
        {
            if(keys[i].info->value & currentKeyState)
            {
                if(keys[i].counter++ >= keys[i].info->longPushCounterMax)
                {
                    keys[i].state = KeyStateLongPush ;
                    if(keys[i].counter >= keys[i].info->longLongPushCounterMax)
                    {
                        keys[i].state = KeyStateLongLongPush ;
                        keys[i].counter = keys[i].info->longLongPushCounterMax ;
                    }
                }
            }else{
                if(keys[i].counter)
                {
                    keys[i].counter = 0 ;
                    keys[i].state = KeyStateClick ;
                }else{
                    keys[i].state = KeyStateNone ;
                }
            }            
        }
    }else{
        for(;i<KeySum;i++)
        {
            if(keys[i].counter)
            {
                if(keys[i].state == KeyStateNone)
                {
                    keys[i].state = KeyStateClick ;
                }
                keys[i].counter = 0 ;
            }else{
                keys[i].state = KeyStateNone ;
            }
        } 
    }
    
}


