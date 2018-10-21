/*
Decription	:
Author		:Alan Zhang
Date		:2018-10-21 14:23:52
Version		:1.0.0
*/
#ifndef _FONT_H_
#define _FONT_H_

typedef enum
{
    FontIndex_none = 0 ,
    FontIndex_8x16 ,
}FontIndex ;

typedef struct
{
    FontIndex index ;
    const char * name ;
    
    unsigned char width ;
    unsigned char height ;
    const unsigned char * pData ;
}Font ;

#ifdef __cplusplus
extern C{
#endif

const Font * fontGetByIndex(unsigned char index);
const Font * fontGetByName(const char * name);


#ifdef __cplusplus
}
#endif
#endif
