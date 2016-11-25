#ifndef SOLGUI_TYPE_H		
#define SOLGUI_TYPE_H

#include <stdint.h>

typedef enum {False=0,True=!False} boolean;

//[FWLIB 2.0¿â]===================================
//typedef unsigned long  u32;
//typedef unsigned short u16;
//typedef unsigned char  u8;
//
//typedef signed long  s32;
//typedef signed short s16;
//typedef signed char  s8;

//[FWLIB 3.5¿â]===================================
typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

#endif
