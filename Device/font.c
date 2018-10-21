/*
Decription	:
Author		:Alan Zhang
Date		:2018-10-21 14:23:52
Version		:1.0.0
*/
#include "font.h"
#include "typedef.h"
#include "string.h"

#include "font8x16.c"

const Font fonts[] = 
{
    {FontIndex_8x16,"font8x16",8,16,(const unsigned char*)font8x16SourceMap},
};


const Font* fontGetByIndex(unsigned char index)
{
    unsigned char i = 0 ;
    for(;i<COUNTER_OF_ITEM(fonts, Font);i++)
    {
        if(index == fonts[i].index)
        {
            return fonts +i ;
        }
    }

    return (Font*)0;
}

const Font* fontGetByName(const char * name)
{
    unsigned char i = 0 ;
    for(;i<COUNTER_OF_ITEM(fonts, Font);i++)
    {
        if(0 == strcmp(name,fonts[i].name))
        {
            return fonts + i ;
        }
    }

    return (Font*)0;
}


