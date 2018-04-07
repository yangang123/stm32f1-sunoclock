#ifndef _STM32F1COMMON_COMMON_H
#define _STM32F1COMMON_COMMON_H

#define _32 long
#define _16 short
#define _8  char

typedef unsigned _32 u32;
typedef signed   _32 i32;
typedef unsigned _32 u32f;
typedef signed   _32 i32f;

typedef unsigned _16 u16;
typedef signed   _16 i16;
typedef unsigned _32 u16f;
typedef signed   _32 i16f;

typedef unsigned _8  u8;
typedef signed   _8  i8;
typedef unsigned _32 u8f;
typedef signed   _32 i8f;

typedef unsigned _32 size;

#undef _32
#undef _16
#undef _8

#endif

