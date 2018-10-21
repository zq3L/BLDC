/*
Decription	:
Author		:Alan Zhang
Date		:2018-10-21 08:30:17
Version		:1.0.0
*/
#ifndef _NOKIA5110_H_
#define _NOKIA5110_H_

#include "font.h"

#ifdef __cplusplus
extern C{
#endif

void nokia5110Init(void);
void nokia5110Printf(unsigned char row,unsigned char col,const char * str,FontIndex index);
void nokia5110ClearScreen(unsigned char data);

#ifdef __cplusplus
}
#endif
#endif
