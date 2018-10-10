/*
Decription	:
Author		:Alan Zhang
Date		:2018-10-10 22:23:43
Version		:1.0.0
*/
#ifndef _FIFO_H_
#define _FIFO_H_

#include "typedef.h"

typedef struct
{
    void *pData ;
    unsigned char usedSize ;
    
    unsigned char writePersion ;
    unsigned char readPersion ;
    
    unsigned char size ;
    unsigned char itemSize ;
}Fifo ;

#ifdef __cplusplus
extern C{
#endif

void fifoInit(Fifo* pFifo,void* pData,unsigned char size,unsigned char itemSize);
Bool fifoWrite(Fifo* pFifo,void* pItem);
Bool fifoRead(Fifo* pFifo,void* pItem);


#ifdef __cplusplus
}
#endif
#endif
