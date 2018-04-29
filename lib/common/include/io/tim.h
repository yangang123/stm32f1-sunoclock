/*
2017 David DiPaola
licensed under CC0 (public domain, see https://creativecommons.org/publicdomain/zero/1.0/)
*/

#ifndef _COMMON_IO_TIM_H
#define _COMMON_IO_TIM_H

#include <feature/tim.h>

/* RM0008 figure 8, figure 11 */ 
/*
clock sources:
	TIM2/3/4/5/6/7/12/13/14: SYSCLK --> AHB --> APB1 (36Mhz max) --> timer prescaler --> TIMx
	TIM1/8/9/10/11:          SYSCLK --> AHB --> APB2 (72Mhz max) --> timer prescaler --> TIMx
timer prescaler: (APBx prescaler == /1) ? *1 : *2
*/

/* NOTE ?basic timer is subset of general purpose timer is subset of advanced control timer? */

/* HACK advanced control timer, general purpose timer, and basic timer register structures are almost identical */
#define _TIM_STRUCT_ISADV
#include "./_tim_struct.h"
#undef _TIM_STRUCT_ISADV
#define _TIM_STRUCT_ISGP
#include "./_tim_struct.h"
#undef _TIM_STRUCT_ISGP
#define _TIM_STRUCT_ISBAS
#include "./_tim_struct.h"
#undef _TIM_STRUCT_ISBAS

/* RM0008 14.4.1 */
static const u32 tim_CR1_ARPE = (1 << 7);  /* Auto Reload Preload Enable */
static const u32 tim_CR1_OPM  = (1 << 3);  /* One Pulse Mode */
static const u32 tim_CR1_URS  = (1 << 2);  /* Update Request Source */
static const u32 tim_CR1_UDIS = (1 << 1);  /* Update DISable */
static const u32 tim_CR1_CEN  = (1 << 0);  /* Counter ENable */
/* TODO other CR1 bits */

/* RM0008 14.4.5 */
static const u32 tim_SR_UIF = (1 << 0);  /* Update Interrupt Flag */
/* TODO other status bits */

/* RM0008 14.4.6 */
static const u32 tim_EGR_UG = (1 << 0);  /* Update Generation */
/* TODO other event bits */

/* RM0008 14.4.7 */
static const u32 tim_CCMR1_OC2M_MASK     = (0b111 << 12);  /* Output Compare 2 Mode mask */
static const u32 tim_CCMR1_OC2M_PWMMODE1 = (0b110 << 12);  /* ... */
static const u32 tim_CCMR1_OC2PE         = (    1 << 11);  /* Output Compare 2 Preload Enable */
static const u32 tim_CCMR1_CC2S_MASK     = ( 0b11 <<  8);  /* Capture/Compare 2 Selection */
static const u32 tim_CCMR1_CC2S_OUTPUT   = ( 0b00 <<  8);  /* ... */
/* TODO other CCMR1 bits */

/* RM0008 14.4.9 */
static const u32 tim_CCER_CC2P = (1 <<  5);  /* Capture/Compare 2 output Polarity */
static const u32 tim_CCER_CC2E = (1 <<  4);  /* Capture/Compare 2 output Enable */
/* TODO other CCER bits */

/* RM0008 14.4.18 */
static const u32 tim_BDTR_MOE = (1 << 15);  /* Main Output Enable */
/* TODO other BDTR bits */

/* RM0008 table 3 */
#if defined(FEATURE_TIM1)
static struct tim_adv * const tim_TIM1  = (void *)0x40012C00;
#endif
#if defined(FEATURE_TIM8)
static struct tim_adv * const tim_TIM8  = (void *)0x40013400;  /* TODO confirm */
#endif
#if defined(FEATURE_TIM2)
static struct tim_gp  * const tim_TIM2  = (void *)0x40000000;  /* TODO confirm */
#endif
#if defined(FEATURE_TIM3)
static struct tim_gp  * const tim_TIM3  = (void *)0x40000400;  /* TODO confirm */
#endif
#if defined(FEATURE_TIM4)
static struct tim_gp  * const tim_TIM4  = (void *)0x40000800;  /* TODO confirm */
#endif
#if defined(FEATURE_TIM5)
static struct tim_gp  * const tim_TIM5  = (void *)0x40000C00;  /* TODO confirm */
#endif
#if defined(FEATURE_TIM9)
static struct tim_gp  * const tim_TIM9  = (void *)0x40014C00;  /* TODO confirm */
#endif
#if defined(FEATURE_TIM10)
static struct tim_gp  * const tim_TIM10 = (void *)0x40015000;  /* TODO confirm */
#endif
#if defined(FEATURE_TIM11)
static struct tim_gp  * const tim_TIM11 = (void *)0x40015400;  /* TODO confirm */
#endif
#if defined(FEATURE_TIM12)
static struct tim_gp  * const tim_TIM12 = (void *)0x40001800;  /* TODO confirm */
#endif
#if defined(FEATURE_TIM13)
static struct tim_gp  * const tim_TIM13 = (void *)0x40001C00;  /* TODO confirm */
#endif
#if defined(FEATURE_TIM14)
static struct tim_gp  * const tim_TIM14 = (void *)0x40002000;  /* TODO confirm */
#endif
#if defined(FEATURE_TIM6)
static struct tim_bas * const tim_TIM6  = (void *)0x40001000;  /* TODO confirm */
#endif
#if defined(FEATURE_TIM7)
static struct tim_bas * const tim_TIM7  = (void *)0x40001400;  /* TODO confirm */
#endif

#endif

