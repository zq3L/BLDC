/*
Decription	:
Author		:Alan Zhang
Date		:2018-10-21 08:30:17
Version		:1.0.0
*/
#include "Nokia5110.h"
#include "stm32f10x.h"
#include "gpio.h"
#include "simSpi.h"

#include <string.h>

//单例，不用Index
typedef struct
{
    const unsigned char ROW_MAX ;
    const unsigned char COL_MAX ;
    const SimSpiIndex simSpiIndex ;
    const GPIO CS ;
    const GPIO CD ;
}Nokia5110;

const Nokia5110 myNokia5110 = 
{
    6,84,SimSpiIndex0,{GPIOB,GPIO_Pin_12},{GPIOB,GPIO_Pin_13}
};

static void nokia5110WriteCommand(unsigned char command)
{
    GPIO_ResetBits(myNokia5110.CD.port, myNokia5110.CD.pins) ;
    GPIO_ResetBits(myNokia5110.CS.port, myNokia5110.CS.pins) ;

    simSpiWrite(myNokia5110.simSpiIndex, command);

    GPIO_SetBits(myNokia5110.CS.port, myNokia5110.CS.pins) ;
    GPIO_SetBits(myNokia5110.CD.port, myNokia5110.CD.pins) ;
}

static void nokia5110WriteRam(unsigned char x,unsigned char y,const unsigned char* pData,unsigned short size)
{
    unsigned short i = 0 ;
    nokia5110WriteCommand(0x80 | (y % 84 ));
    nokia5110WriteCommand(0x40 | (x % 6 ));
    
    GPIO_SetBits(myNokia5110.CD.port, myNokia5110.CD.pins);
    GPIO_ResetBits(myNokia5110.CS.port, myNokia5110.CS.pins) ;    

    for(i=0;i<size;i++)
    {
        simSpiWrite(myNokia5110.simSpiIndex, *(pData+i));
    }
    GPIO_SetBits(myNokia5110.CS.port, myNokia5110.CS.pins);  
}

static void nokia5110HarwareInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct ;
    GPIO_InitStruct.GPIO_Pin = myNokia5110.CS.pins ;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP ;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz ;
    GPIO_Init(myNokia5110.CS.port, &GPIO_InitStruct);
    
    GPIO_InitStruct.GPIO_Pin = myNokia5110.CD.pins ;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP ;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz ;
    GPIO_Init(myNokia5110.CD.port, &GPIO_InitStruct);

    GPIO_SetBits(myNokia5110.CS.port, myNokia5110.CS.pins);
    GPIO_SetBits(myNokia5110.CD.port, myNokia5110.CD.pins);
}

static void nokia5110RegInit(void)
{
    nokia5110WriteCommand(0x21);
    nokia5110WriteCommand(0xc8);
    nokia5110WriteCommand(0x06);
    nokia5110WriteCommand(0x13);
    nokia5110WriteCommand(0x20);
    nokia5110WriteCommand(0x0c);
    
    nokia5110ClearScreen(0x00);
    //nokia5110Printf(0,0,"Alan Zhang",FontIndex_8x16);
    nokia5110Printf(0,1,"BLDC Board",FontIndex_8x16);
    nokia5110Printf(0,3,"Ver  1.0.0",FontIndex_8x16);
}


void nokia5110Init()
{
    nokia5110HarwareInit();
    nokia5110RegInit();
}

void nokia5110ClearScreen(unsigned char data)
{
    unsigned short size = 6 * 84 ;
    nokia5110WriteCommand(0x80 );
    nokia5110WriteCommand(0x40 );
    
    GPIO_SetBits(myNokia5110.CD.port, myNokia5110.CD.pins);
    GPIO_ResetBits(myNokia5110.CS.port, myNokia5110.CS.pins) ;    

    while(size--)
    {
        simSpiWrite(myNokia5110.simSpiIndex, data);
    }
    GPIO_SetBits(myNokia5110.CS.port, myNokia5110.CS.pins);  
}

void nokia5110Printf(unsigned char row,unsigned char col,const char * str,FontIndex index)
{
    const Font * fontObj = fontGetByIndex(index);
    unsigned char strLength = strlen(str) ;
    unsigned char i ,j ;
    if(0 == fontObj)
    {
        return ;
    }

    strLength = strLength > (myNokia5110.COL_MAX - col)/fontObj->width ? (myNokia5110.COL_MAX - col)/fontObj->width : strLength ;

    for(i=0;i<strLength;i++)
    {
        for(j=0;j<fontObj->height/8;j++)
        {
            nokia5110WriteRam(col+j, row+i*(fontObj->width), fontObj->pData + (*(str+i) - ' ')*((fontObj->width * fontObj->height)>>3)+j*fontObj->width, fontObj->width);
        }
    }
}

