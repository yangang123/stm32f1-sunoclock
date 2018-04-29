/*
2017 David DiPaola
licensed under CC0 (public domain, see https://creativecommons.org/publicdomain/zero/1.0/)
*/

#ifndef _COMMON_IO_RCC_H
#define _COMMON_IO_RCC_H

#include <feature/tim.h>

/* RM0008 7.3.11 */
struct __attribute__ ((__packed__)) rcc {
	/* 0x00 */  volatile u32 CR;        /* clock Control Register, RM0008 7.3.1 */
	/* 0x04 */  volatile u32 CFGR;      /* clock ConFiGuration Register, RM0008 7.3.2 */
	/* 0x08 */  volatile u32 CIR;       /* Clock Interrupt Register, RM0008 7.3.3 */ /* TODO confirm */
	/* 0x0C */  volatile u32 APB2RSTR;  /* APB2 peripheral ReSeT Register, RM0008 7.3.4 */ /* TODO confirm */
	/* 0x10 */  volatile u32 APB1RSTR;  /* APB1 peripheral ReSeT Register, RM0008 7.3.5 */ /* TODO confirm */
	/* 0x14 */  volatile u32 AHBENR;    /* AHB peripheral ENable Register, RM0008 7.3.6 */
	/* 0x18 */  volatile u32 APB2ENR;   /* APB2 peripheral ENable Register, RM0008 7.3.7 */
	/* 0x1C */  volatile u32 APB1ENR;   /* APB1 peripheral ENable Register, RM0008 7.3.8 */
	/* 0x20 */  volatile u32 BDCR;      /* Backup Domain Control Register, RM0008 7.3.9 */
	/* 0x24 */  volatile u32 CSR;       /* Control/Status Register, RM0008 7.3.10 */
};

/* RM0008 7.3.1 */
static const u32 rcc_CR_HSERDY = (1 << 17);
static const u32 rcc_CR_HSEON  = (1 << 16);
static const u32 rcc_CR_HSIRDY = (1 <<  1);
static const u32 rcc_CR_HSION  = (1 <<  0);
/* TODO rcc_CR bits */

/* RM0008 7.3.2 */
/* aPb high-speed PREscaler 2 */
static const u32 rcc_CFGR_PPRE2_MASK  = ( 0b111 << 11);
static const u32 rcc_CFGR_PPRE2_DIV1  = ( 0b000 << 11);  /* APB2 clock = AHB clock /  1 */
static const u32 rcc_CFGR_PPRE2_DIV2  = ( 0b100 << 11);  /* APB2 clock = AHB clock /  2 */
static const u32 rcc_CFGR_PPRE2_DIV4  = ( 0b101 << 11);  /* APB2 clock = AHB clock /  4 */
static const u32 rcc_CFGR_PPRE2_DIV8  = ( 0b110 << 11);  /* APB2 clock = AHB clock /  8 */
static const u32 rcc_CFGR_PPRE2_DIV16 = ( 0b111 << 11);  /* APB2 clock = AHB clock / 16 */
/* aPb high-speed PREscaler 1 */
static const u32 rcc_CFGR_PPRE1_MASK  = ( 0b111 << 8);
static const u32 rcc_CFGR_PPRE1_DIV1  = ( 0b000 << 8);  /* APB1 clock = AHB clock /  1 */
static const u32 rcc_CFGR_PPRE1_DIV2  = ( 0b100 << 8);  /* APB1 clock = AHB clock /  2 */
static const u32 rcc_CFGR_PPRE1_DIV4  = ( 0b101 << 8);  /* APB1 clock = AHB clock /  4 */
static const u32 rcc_CFGR_PPRE1_DIV8  = ( 0b110 << 8);  /* APB1 clock = AHB clock /  8 */
static const u32 rcc_CFGR_PPRE1_DIV16 = ( 0b111 << 8);  /* APB1 clock = AHB clock / 16 */
/* aHb PREscaler */
static const u32 rcc_CFGR_HPRE_MASK   = (0b1111 << 4);
static const u32 rcc_CFGR_HPRE_DIV1   = (0b0000 << 4);  /* AHB clock = SYSCLK /   1 */
static const u32 rcc_CFGR_HPRE_DIV2   = (0b1000 << 4);  /* AHB clock = SYSCLK /   2 */
static const u32 rcc_CFGR_HPRE_DIV4   = (0b1001 << 4);  /* AHB clock = SYSCLK /   4 */
static const u32 rcc_CFGR_HPRE_DIV8   = (0b1010 << 4);  /* AHB clock = SYSCLK /   8 */
static const u32 rcc_CFGR_HPRE_DIV16  = (0b1011 << 4);  /* AHB clock = SYSCLK /  16 */
static const u32 rcc_CFGR_HPRE_DIV64  = (0b1100 << 4);  /* AHB clock = SYSCLK /  64 */
static const u32 rcc_CFGR_HPRE_DIV128 = (0b1101 << 4);  /* AHB clock = SYSCLK / 128 */
static const u32 rcc_CFGR_HPRE_DIV256 = (0b1110 << 4);  /* AHB clock = SYSCLK / 256 */
static const u32 rcc_CFGR_HPRE_DIV512 = (0b1111 << 4);  /* AHB clock = SYSCLK / 512 */
/* System clock sWitch Status */
static const u32 rcc_CFGR_SWS_MASK = (0b11 << 2);
static const u32 rcc_CFGR_SWS_PLL  = (0b10 << 2);  /* switch SYSCLK to PLL complete */
static const u32 rcc_CFGR_SWS_HSE  = (0b01 << 2);  /* switch SYSCLK to HSE complete */
static const u32 rcc_CFGR_SWS_HSI  = (0b00 << 2);  /* switch SYSCLK to HSI complete */
/* System clock sWitch */
static const u32 rcc_CFGR_SW_MASK = (0b11 << 0);
static const u32 rcc_CFGR_SW_PLL  = (0b10 << 0);  /* start switch SYSCLK to PLL */
static const u32 rcc_CFGR_SW_HSE  = (0b01 << 0);  /* start switch SYSCLK to HSE */
static const u32 rcc_CFGR_SW_HSI  = (0b00 << 0);  /* start switch SYSCLK to HSI */
/* TODO rcc_CFGR bits */

/* RM0008 7.3.4 */
#if defined(FEATURE_TIM11)
static const u32 rcc_APB2RSTR_TIM11RST = (1 << 21);  /* TIM11 ReSeT */
#endif
#if defined(FEATURE_TIM10)
static const u32 rcc_APB2RSTR_TIM10RST = (1 << 20);  /* TIM10 ReSeT */
#endif
#if defined(FEATURE_TIM9)
static const u32 rcc_APB2RSTR_TIM9RST  = (1 << 19);  /* TIM9 ReSeT */
#endif
#if defined(FEATURE_TIM8)
static const u32 rcc_APB2RSTR_TIM8RST  = (1 << 13);  /* TIM8 ReSeT */
#endif
#if defined(FEATURE_TIM1)
static const u32 rcc_APB2RSTR_TIM1RST  = (1 << 11);  /* TIM1 ReSeT */
#endif
/* TODO rcc_APB2RSTR bits */

/* RM0008 7.3.5 */
#if defined(FEATURE_TIM14)
static const u32 rcc_APB1RSTR_TIM14RST = (1 <<  8);  /* TIM14 ReSeT */
#endif
#if defined(FEATURE_TIM13)
static const u32 rcc_APB1RSTR_TIM13RST = (1 <<  7);  /* TIM13 ReSeT */
#endif
#if defined(FEATURE_TIM12)
static const u32 rcc_APB1RSTR_TIM12RST = (1 <<  6);  /* TIM12 ReSeT */
#endif
#if defined(FEATURE_TIM7)
static const u32 rcc_APB1RSTR_TIM7RST  = (1 <<  5);  /* TIM7 ReSeT */
#endif
#if defined(FEATURE_TIM6)
static const u32 rcc_APB1RSTR_TIM6RST  = (1 <<  4);  /* TIM6 ReSeT */
#endif
#if defined(FEATURE_TIM5)
static const u32 rcc_APB1RSTR_TIM5RST  = (1 <<  3);  /* TIM5 ReSeT */
#endif
#if defined(FEATURE_TIM4)
static const u32 rcc_APB1RSTR_TIM4RST  = (1 <<  2);  /* TIM4 ReSeT */
#endif
#if defined(FEATURE_TIM3)
static const u32 rcc_APB1RSTR_TIM3RST  = (1 <<  1);  /* TIM3 ReSeT */
#endif
#if defined(FEATURE_TIM2)
static const u32 rcc_APB1RSTR_TIM2RST  = (1 <<  0);  /* TIM2 ReSeT */
#endif
/* TODO rcc_APB1RSTR bits */

/* RM0008 7.3.7 */
#if defined(FEATURE_TIM11)
static const u32 rcc_APB2ENR_TIM11EN  = (1 << 21);  /* TIM11 clock ENable */
#endif
#if defined(FEATURE_TIM10)
static const u32 rcc_APB2ENR_TIM10EN  = (1 << 20);  /* TIM10 clock ENable */
#endif
#if defined(FEATURE_TIM9)
static const u32 rcc_APB2ENR_TIM9EN   = (1 << 19);  /* TIM9 clock ENable */
#endif
static const u32 rcc_APB2ENR_USART1EN = (1 << 14);  /* USART1 clock ENable */
#if defined(FEATURE_TIM8)
static const u32 rcc_APB2ENR_TIM8EN   = (1 << 13);  /* TIM8 clock ENable */
#endif
static const u32 rcc_APB2ENR_SPI1EN   = (1 << 12);  /* SPI1 clock ENable */
#if defined(FEATURE_TIM1)
static const u32 rcc_APB2ENR_TIM1EN   = (1 << 11);  /* TIM1 clock ENable */
#endif
static const u32 rcc_APB2ENR_IOPCEN   = (1 <<  4);  /* gpIO Port C clock ENable */
static const u32 rcc_APB2ENR_IOPAEN   = (1 <<  2);  /* gpIO Port A clock ENable */
static const u32 rcc_APB2ENR_AFIOEN   = (1 <<  0);  /* Alternate Function IO clock ENable */
/* TODO rcc_APB2ENR bits */

/* RM0008 7.3.8 */
static const u32 rcc_APB1ENR_PWREN  = (1 << 28);  /* PoWeR interface clock ENable */
static const u32 rcc_APB1ENR_BKPEN  = (1 << 27);  /* BacKuP interface clock ENable */
#if defined(FEATURE_TIM14)
static const u32 rcc_APB1ENR_TIM14EN = (1 <<  8);  /* TIM14 clock ENable */
#endif
#if defined(FEATURE_TIM13)
static const u32 rcc_APB1ENR_TIM13EN = (1 <<  7);  /* TIM13 clock ENable */
#endif
#if defined(FEATURE_TIM12)
static const u32 rcc_APB1ENR_TIM12EN = (1 <<  6);  /* TIM12 clock ENable */
#endif
#if defined(FEATURE_TIM7)
static const u32 rcc_APB1ENR_TIM7EN  = (1 <<  5);  /* TIM7 clock ENable */
#endif
#if defined(FEATURE_TIM6)
static const u32 rcc_APB1ENR_TIM6EN  = (1 <<  4);  /* TIM6 clock ENable */
#endif
#if defined(FEATURE_TIM5)
static const u32 rcc_APB1ENR_TIM5EN  = (1 <<  3);  /* TIM5 clock ENable */
#endif
#if defined(FEATURE_TIM4)
static const u32 rcc_APB1ENR_TIM4EN  = (1 <<  2);  /* TIM4 clock ENable */
#endif
#if defined(FEATURE_TIM3)
static const u32 rcc_APB1ENR_TIM3EN  = (1 <<  1);  /* TIM3 clock ENable */
#endif
#if defined(FEATURE_TIM2)
static const u32 rcc_APB1ENR_TIM2EN  = (1 <<  0);  /* TIM2 clock ENable */
#endif
/* TODO rcc_APB1ENR bits */

/* RM0008 7.3.9 */
static const u32 rcc_BDCR_RTCEN       = (   1 << 15);  /* Real Time Clock ENable */
/* Real Time Clock clock source SELection */
static const u32 rcc_BDCR_RTCSEL_MASK = (0b11 <<  8);
static const u32 rcc_BDCR_RTCSEL_HSE  = (0b11 <<  8);  /* RTC clock = HSE */
static const u32 rcc_BDCR_RTCSEL_LSI  = (0b10 <<  8);  /* RTC clock = LSI */
static const u32 rcc_BDCR_RTCSEL_LSE  = (0b01 <<  8);  /* RTC clock = LSE */
static const u32 rcc_BDCR_RTCSEL_NONE = (0b00 <<  8);  /* RTC clock = NONE */
static const u32 rcc_BDCR_LSERDY      = (   1 <<  1);  /* Low Speed External oscillator ReaDY */
static const u32 rcc_BDCR_LSEON       = (   1 <<  0);  /* Low Speed External oscillator enable ON */
/* TODO other rcc_BDCR bits */

/* RM0008 table 3 */
static struct rcc * const RCC = (void *)0x40021000;

#endif

