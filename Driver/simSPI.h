/*
Decription	:
Author		:Alan Zhang
Date		:2018-10-10 22:58:17
Version		:1.0.0
*/
#ifndef _SIMSPI_H_
#define _SIMSPI_H_

#include "typedef.h"
#include "gpio.h"

typedef enum
{
    SimSpiMode_MOSI = 0x01 ,
    SimSpiMode_MISO = 0x02 ,
}SimSpiMode ;

typedef struct
{
    GPIO CS ;
    GPIO Clk ;
    GPIO MOSI ;
    GPIO MISO ;
}SimSpiInfo ;

typedef struct
{
    unsigned char index ;
    SimSpiMode mode ;
    SimSpiInfo* info ;
}SimSpi ;

#ifdef __cplusplus
extern C{
#endif

void simSpiInit(void);


#ifdef __cplusplus
}
#endif
#endif
