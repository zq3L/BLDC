/*
Decription	:
Author		:Alan Zhang
Date		:2018-10-10 22:23:43
Version		:1.0.0
*/
#include "FIFO.h"


void fifoInit(Fifo* pFifo,void* pData,unsigned char size,unsigned char itemSize)
{
    pFifo->pData = pData ;
    pFifo->size = size ;
    pFifo->usedSize = 0 ;
    pFifo->itemSize = itemSize ;
    pFifo->readPersion = 0 ;
    pFifo->writePersion = 0 ;
}

Bool fifoWrite(Fifo* pFifo,void* pItem)
{
    unsigned char i = 0 ;
    
    if(pFifo->usedSize >= pFifo->size)
    {
        return false ;
    }

    pFifo->usedSize++ ;
    if(++pFifo->writePersion >= pFifo->size)
    {
        pFifo->writePersion = 0 ;
    }

    for(i=0;i<pFifo->itemSize;i++)
    {
        *((char*)pFifo->pData+i) = *((char*)pItem+i);
    }

    return true ;
}


Bool fifoRead(Fifo* pFifo,void* pItem)
{
    unsigned char i = 0 ;
    if(pFifo->usedSize == 0)
    {
        return false ;
    }

    pFifo->usedSize -- ;
    if(++pFifo->readPersion >= pFifo->size)
    {
        pFifo->readPersion = 0 ;
    }
    
    for(i=0;i<pFifo->itemSize;i++)
    {
        *((char*)pItem+i)= *((char*)pFifo->pData+i);
    }

    return true ;    
}


Bool fifoPeek(Fifo * pFifo, void * pItem)
{
    unsigned char i = 0 ;
    
    if(0 == pFifo->usedSize)
    {
        return false ;
    }
    
    for(i=0;i<pFifo->itemSize;i++)
    {
        *((char*)pItem+i)= *((char*)pFifo->pData+i);
    }

    return true ;   
}


