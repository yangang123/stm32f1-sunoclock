/*
2018 David DiPaola
licensed under CC0 (public domain, see https://creativecommons.org/publicdomain/zero/1.0/)
*/

#ifndef _COMMON_IO_AFIO_H
#define _COMMON_IO_AFIO_H

/* clock source: SYSCLK --> AHB -- > APB2 (72Mhz max) --> GPIO */ /* RM0008 figure 8, figure 11 */

/* RM0008 9.5 */
struct __attribute__ ((__packed__)) afio {
	/* 0x00 */  volatile u32 EVCR;     /* EVent Control Register, RM0008 9.4.1 */ /* TODO confirm */
	/* 0x04 */  volatile u32 MAPR;     /* alternate function reMAP and debug i/o configuration Register, RM0008 9.4.2 */
	/* 0x08 */  volatile u32 EXTICR1;  /* EXTernal Interrupt Configuration Register 1, RM0008 9.4.3 */ /* TODO confirm */
	/* 0x0C */  volatile u32 EXTICR2;  /* EXTernal Interrupt Configuration Register 2, RM0008 9.4.4 */ /* TODO confirm */
	/* 0x10 */  volatile u32 EXTICR3;  /* EXTernal Interrupt Configuration Register 3, RM0008 9.4.5 */ /* TODO confirm */
	/* 0x14 */  volatile u32 EXTICR4;  /* EXTernal Interrupt Configuration Register 4, RM0008 9.4.6 */ /* TODO confirm */
	/* 0x18 */  volatile u32 _pad0;
	/* 0x1C */  volatile u32 MAPR2;    /* port configuration LoCK Register, RM0008 9.2.7 */ /* TODO confirm */
};

/* RM0008 9.4.1 */
/* TODO EVCR bits */

/* RM0008 9.4.2 */
static const u32 afio_MAPR_TIM4REMAP_MASK   = (   1 << 12);
static const u32 afio_MAPR_TIM4REMAP_0      = (   0 << 12);  /* TIM4 REMAPping 0 (CH1=PB6  CH2=PB7  CH3=PB8  CH4=PB9 ) */
static const u32 afio_MAPR_TIM4REMAP_1      = (   1 << 12);  /* TIM4 REMAPping 1 (CH1=PD12 CH2=PD13 CH3=PD14 CH4=PD15) */
static const u32 afio_MAPR_TIM3REMAP_MASK   = (0b11 << 10);
static const u32 afio_MAPR_TIM3REMAP_0      = (0b00 << 10);  /* TIM3 REMAPping 0 (CH1=PA6 CH2=PA7 CH3=PB0 CH4=PB1) */
static const u32 afio_MAPR_TIM3REMAP_2      = (0b10 << 10);  /* TIM3 REMAPping 2 (CH1=PB4 CH2=PB5 CH3=PB0 CH4=PB1) */
static const u32 afio_MAPR_TIM3REMAP_3      = (0b11 << 10);  /* TIM3 REMAPping 3 (CH1=PC6 CH2=PC7 CH3=PC8 CH4=PC9) */
static const u32 afio_MAPR_TIM2REMAP_MASK   = (0b11 <<  8);
static const u32 afio_MAPR_TIM2REMAP_0      = (0b00 <<  8);  /* TIM2 REMAPping 0 (CH1/ETR=PA0  CH2=PA1 CH3=PA2  CH4=PA3 ) */
static const u32 afio_MAPR_TIM2REMAP_1      = (0b01 <<  8);  /* TIM2 REMAPping 1 (CH1/ETR=PA15 CH2=PB3 CH3=PA2  CH4=PA3 ) */
static const u32 afio_MAPR_TIM2REMAP_2      = (0b10 <<  8);  /* TIM2 REMAPping 2 (CH1/ETR=PA0  CH2=PA1 CH3=PB10 CH4=PB11) */
static const u32 afio_MAPR_TIM2REMAP_3      = (0b11 <<  8);  /* TIM2 REMAPping 3 (CH1/ETR=PA15 CH2=PB3 CH3=PB10 CH4=PB11) */
static const u32 afio_MAPR_TIM1REMAP_MASK   = (0b11 <<  6);
static const u32 afio_MAPR_TIM1REMAP_0      = (0b00 <<  6);  /* TIM1 REMAPping 0 (ETR=PA12 CH1=PA8 CH2=PA9  CH3=PA10 CH4=PA11 BKIN=PB12 CH1N=PB13 CH2N=PB14 CH3N=PB15) */
static const u32 afio_MAPR_TIM1REMAP_1      = (0b01 <<  6);  /* TIM1 REMAPping 1 (ETR=PA12 CH1=PA8 CH2=PA9  CH3=PA10 CH4=PA11 BKIN=PA6  CH1N=PA7  CH2N=PB0  CH3N=PB1 ) */
static const u32 afio_MAPR_TIM1REMAP_3      = (0b11 <<  6);  /* TIM1 REMAPping 3 (ETR=PE7  CH1=PE9 CH2=PE11 CH3=PE13 CH4=PE14 BKIN=PE15 CH1N=PE8  CH2N=PE10 CH3N=PE12) */
static const u32 afio_MAPR_USART3REMAP_MASK = (0b11 <<  4);
static const u32 afio_MAPR_USART3REMAP_0    = (0b00 <<  4);  /* USART3 REMAPping 0 (TX=PB10 RX=PB11 CK=PB12 CTS=PB13 RTS=PB14) */
static const u32 afio_MAPR_USART3REMAP_1    = (0b01 <<  4);  /* USART3 REMAPping 1 (TX=PC10 RX=PC11 CK=PC12 CTS=PB13 RTS=PB14) */
static const u32 afio_MAPR_USART3REMAP_3    = (0b11 <<  4);  /* USART3 REMAPping 3 (TX=PD8  RX=PD9  CK=PD10 CTS=PD11 RTS=PD12) */
static const u32 afio_MAPR_USART2REMAP_MASK = (   1 <<  3);
static const u32 afio_MAPR_USART2REMAP_0    = (   0 <<  3);  /* USART2 REMAPping 0 (CTS=PA0 RTS=PA1 TX=PA2 RX=PA3 CK=PA4) */
static const u32 afio_MAPR_USART2REMAP_1    = (   1 <<  3);  /* USART2 REMAPping 1 (CTS=PD3 RTS=PD4 TX=PD5 RX=PD6 CK=PD7) */
static const u32 afio_MAPR_USART1REMAP_MASK = (   1 <<  2);
static const u32 afio_MAPR_USART1REMAP_0    = (   0 <<  2);  /* USART1 REMAPping 0 (TX=PA9 RX=PA10) */
static const u32 afio_MAPR_USART1REMAP_1    = (   1 <<  2);  /* USART1 REMAPping 1 (TX=PB6 RX=PB7 ) */
static const u32 afio_MAPR_SPI1REMAP_MASK   = (   1 <<  0);
static const u32 afio_MAPR_SPI1REMAP_0      = (   0 <<  0);  /* SPI1 REMAPping 0 (NSS=PA4  SCK=PA5 MISO=PA6 MOSI=PA7) */
static const u32 afio_MAPR_SPI1REMAP_1      = (   1 <<  0);  /* SPI1 REMAPping 1 (NSS=PA15 SCK=PB3 MISO=PB4 MOSI=PB5) */
/* TODO other MAPR bits */

/* RM0008 9.4.3 */
/* TODO EXTICR1 bits */

/* RM0008 9.4.4 */
/* TODO EXTICR2 bits */

/* RM0008 9.4.5 */
/* TODO EXTICR3 bits */

/* RM0008 9.4.6 */
/* TODO EXTICR4 bits */

/* RM0008 9.4.7 */
static const u32 afio_MAPR2_TIM14REMAP_MASK = (   1 <<  9);
static const u32 afio_MAPR2_TIM14REMAP_0    = (   0 <<  9);  /* TIM14 REMAPping 0 (CH1=PA7) */
static const u32 afio_MAPR2_TIM14REMAP_1    = (   1 <<  9);  /* TIM14 REMAPping 1 (CH1=PF9) */
static const u32 afio_MAPR2_TIM13REMAP_MASK = (   1 <<  8);
static const u32 afio_MAPR2_TIM13REMAP_0    = (   0 <<  8);  /* TIM13 REMAPping 0 (CH1=PA6) */
static const u32 afio_MAPR2_TIM13REMAP_1    = (   1 <<  8);  /* TIM13 REMAPping 1 (CH1=PF8) */
static const u32 afio_MAPR2_TIM11REMAP_MASK = (   1 <<  7);
static const u32 afio_MAPR2_TIM11REMAP_0    = (   0 <<  7);  /* TIM11 REMAPping 0 (CH1=PB9) */
static const u32 afio_MAPR2_TIM11REMAP_1    = (   1 <<  7);  /* TIM11 REMAPping 1 (CH1=PF7) */
static const u32 afio_MAPR2_TIM10REMAP_MASK = (   1 <<  6);
static const u32 afio_MAPR2_TIM10REMAP_0    = (   0 <<  6);  /* TIM10 REMAPping 0 (CH1=PB8) */
static const u32 afio_MAPR2_TIM10REMAP_1    = (   1 <<  6);  /* TIM10 REMAPping 1 (CH1=PF6) */
static const u32 afio_MAPR2_TIM9REMAP_MASK  = (   1 <<  5);
static const u32 afio_MAPR2_TIM9REMAP_0     = (   0 <<  5);  /* TIM9 REMAPping 0 (CH1=PA2 CH2=PA3) */
static const u32 afio_MAPR2_TIM9REMAP_1     = (   1 <<  5);  /* TIM9 REMAPping 1 (CH1=PE5 CH2=PE6) */
/* TODO other MAPR2 bits */

/* RM0008 3.3 */
static struct afio * const AFIO = (void *)0x40010000;

#endif

