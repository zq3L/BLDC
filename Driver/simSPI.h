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

/*
----------------|        |--------|        |--------|        |--------|        |--------|        |--------
                |        |        |        |        |        |        |        |        |        |
                |--------|        |--------|        |--------|        |--------|        |--------|

            
----------\  /--------------\  /--------------\  /--------------\  /--------------\  /--------------\  /---
           \/                \/                \/                \/                \/                \/
           /\                /\                /\                /\                /\                /\
----------/  \--------------/  \--------------/  \--------------/  \--------------/  \--------------/  \---


-------------------\  /--------------\  /--------------\  /--------------\  /--------------\  /-----------
                    \/                \/                \/                \/                \/
                    /\                /\                /\                /\                /\
-------------------/  \--------------/  \--------------/  \--------------/  \--------------/  \------------
*/

typedef enum
{
    SimSpiMode2_edge = 0x00 ,
    SimSpiMode1_edge = 0x01 ,
}SimSpiMode ;

typedef enum
{
    SimSpiDirection_MOSI = 0x01 ,
    SimSpiDirection_MISO = 0x02 ,
}SimSpiDirection ;

typedef struct
{
    GPIO Clk ;
    GPIO MOSI ;
    GPIO MISO ;

    SimSpiMode mode ;
    SimSpiDirection direction ;
}SimSpiInfo ;

typedef enum
{
    SimSpiIndexNone = 0 ,
    SimSpiIndex0,
}SimSpiIndex ;

typedef struct
{
    SimSpiIndex index ;
    unsigned char delayTime ;
    const SimSpiInfo* info ;
}SimSpi ;


#ifdef __cplusplus
extern C{
#endif

void simSpiInit(void);
Bool simSpiWrite(SimSpiIndex index, unsigned char data);
Bool simSpiRead(SimSpiIndex index,unsigned char * pData);



#ifdef __cplusplus
}
#endif
#endif
