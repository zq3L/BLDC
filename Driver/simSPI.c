/*
Decription	:
Author		:Alan Zhang
Date		:2018-10-10 22:58:17
Version		:1.0.0
*/
#include "simSPI.h"
#include "typedef.h"


const SimSpiInfo simSpiInfos[] = 
{
    {{GPIOB,GPIO_Pin_15},{GPIOB,GPIO_Pin_14},{GPIOB,GPIO_Pin_14},SimSpiMode1_edge,(SimSpiDirection)(SimSpiDirection_MOSI)},
};

SimSpi simSpis[] = 
{
    {SimSpiIndex0,5,simSpiInfos},
};

static void simSpiHardwareInit(void)
{
    unsigned char i = 0 ;
    GPIO_InitTypeDef GPIO_InitStruct ;
    
    for(;i<COUNTER_OF_ITEM(simSpis,SimSpi);i++)
    {
        if(simSpis[i].info->direction & SimSpiDirection_MOSI)
        {
            GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP ;
            GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz ;
            GPIO_InitStruct.GPIO_Pin = simSpis[i].info->MOSI.pins ;
            GPIO_Init(simSpis[i].info->MOSI.port, &GPIO_InitStruct);
            GPIO_SetBits(simSpis[i].info->MOSI.port, simSpis[i].info->MOSI.pins);
        }
        
        if(simSpis[i].info->direction & SimSpiDirection_MISO)
        {
            GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU ;
            GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz ;
            GPIO_InitStruct.GPIO_Pin = simSpis[i].info->MISO.pins ;
            GPIO_Init(simSpis[i].info->MISO.port, &GPIO_InitStruct);
        }

        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP ;
        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz ;
        GPIO_InitStruct.GPIO_Pin = simSpis[i].info->Clk.pins ;
        GPIO_Init(simSpis[i].info->Clk.port, &GPIO_InitStruct);
        
        GPIO_SetBits(simSpis[i].info->Clk.port, simSpis[i].info->Clk.pins);
    }
}

static SimSpi* simSpiGetByIndex(SimSpiIndex index)
{
    unsigned char i = 0 ;
    for(;i<COUNTER_OF_ITEM(simSpis, SimSpi);i++)
    {
        if(simSpis[i].index == index)
        {
            return simSpis+i ;
        }
    }

    return (SimSpi*)0 ;
}

static void simSpiDelay(unsigned int delayTime)
{
    while(delayTime--);
}

void simSpiInit(void)
{
    simSpiHardwareInit();
}

Bool simSpiWrite(SimSpiIndex index, unsigned char data)
{
    unsigned char i = 0 ;
    SimSpi* pSimSpi = simSpiGetByIndex(index);
    if(pSimSpi)
    {
        for(i=0;i<8;i++)
        {
            GPIO_ResetBits(pSimSpi->info->Clk.port,pSimSpi->info->Clk.pins);
            (0x80 & (data<<i))?GPIO_SetBits(pSimSpi->info->MOSI.port, pSimSpi->info->MOSI.pins):GPIO_ResetBits(pSimSpi->info->MOSI.port, pSimSpi->info->MOSI.pins);
            simSpiDelay(pSimSpi->delayTime);
            GPIO_SetBits(pSimSpi->info->Clk.port,pSimSpi->info->Clk.pins);
            simSpiDelay(pSimSpi->delayTime);
        }
        return true ;
    }else{
        return false ;
    }
}

Bool simSpiRead(SimSpiIndex index, unsigned char * pData)
{
    unsigned char i = 0 ;
    SimSpi* pSimSpi = simSpiGetByIndex(index);
    *pData = 0 ;
    if(pSimSpi)
    {
        for(i=0;i<8;i++)
        {
            /*
            *(pData) <<= 1 ;
            simSpiDelay(pSimSpi->delayTime);
            GPIO_WriteBit(pSimSpi->info->Clk.port, pSimSpi->info->Clk.pins, Bit_RESET);
            simSpiDelay(pSimSpi->delayTime);
            GPIO_WriteBit(pSimSpi->info->Clk.port, pSimSpi->info->Clk.pins, Bit_SET);
            *(pData) |= GPIO_ReadInputDataBit(pSimSpi->info->MISO.port, pSimSpi->info->MISO.pins) == Bit_SET ? 0x01 : 0x00 ;
            */
        }
        return true ;
    }else{
        return false ;
    }
}




