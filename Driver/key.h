/*
Decription	:
Author		:Alan Zhang
Date		:2018-10-07 00:11:17
Version		:1.0.0
*/
#ifndef _KEY_H_
#define _KEY_H_

typedef enum


{
    KeyStateNone = 0 ,
    KeyStateClick,
    KeyStateLongPush ,
    KeyStateLongLongPush ,
}KeyState ;

typedef enum
{
    KeyIndexNone = 0 ,
    KeyIndex0 ,
    KeyIndex1 ,
    KeyIndex2 ,
    KeyIndex3 ,
    KeyIndex4 ,    
    KeySum  = KeyIndex4 ,
}KeyIndex ;

#ifdef __cplusplus
extern C{
#endif

KeyState keyGetState(KeyIndex index);
void keyInit(void);
void keyRun(void);

#ifdef __cplusplus
}
#endif
#endif
