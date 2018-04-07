#ifndef _STM32F1COMMON_GPIO_H
#define _STM32F1COMMON_GPIO_H

/* clock source: SYSCLK --> AHB -- > APB2 (72Mhz max) --> GPIO */ /* RM0008 figure 8, figure 11 */

/* RM0008 9.5 */
struct __attribute__ ((__packed__)) gpio {
	/* 0x00 */  volatile u32 CRL;   /* port Configuration Register Low, RM0008 9.2.1 */ /* TODO confirm */
	/* 0x04 */  volatile u32 CRH;   /* port Configuration Register High, RM0008 9.2.2 */
	/* 0x08 */  volatile u32 IDR;   /* port Input Data Register, RM0008 9.2.3 */ /* TODO confirm */
	/* 0x0C */  volatile u32 ODR;   /* port Output Data Register, RM0008 9.2.4 */
	/* 0x10 */  volatile u32 BSRR;  /* port Bit Set/Reset Register, RM0008 9.2.5 */ /* TODO confirm */
	/* 0x14 */  volatile u32 BRR;   /* port Bit Reset Register, RM0008 9.2.6 */ /* TODO confirm */
	/* 0x18 */  volatile u32 LCKR;  /* port configuration LoCK Register, RM0008 9.2.7 */ /* TODO confirm */
};

/* RM0008 9.2.2 */
/* pin 13 */
static const u32 gpio_CRH_CNF13_MASK       = (0b11 << 22);
static const u32 gpio_CRH_CNF13_OUT_GPPP   = (0b00 << 22);  /* port CoNFiguration pin 13, OUTput mode, General-Purpose output Push-Pull */
static const u32 gpio_CRH_MODE13_MASK      = (0b11 << 20);
static const u32 gpio_CRH_MODE13_OUT_2MHZ  = (0b10 << 20);  /* port MODE pin 13, OUTput mode, 2MHZ */
/* pin 10 */
static const u32 gpio_CRH_CNF10_MASK       = (0b11 << 10);
static const u32 gpio_CRH_CNF10_IN_PUPD    = (0b10 << 10);  /* port CoNFiguration pin 10, INput mode, Pull-Up/Pull-Down */
static const u32 gpio_CRH_MODE10_MASK      = (0b11 <<  8);
static const u32 gpio_CRH_MODE10_IN        = (0b00 <<  8);  /* port MODE pin 10, INput mode */
/* pin 9 */
static const u32 gpio_CRH_CNF9_MASK        = (0b11 <<  6);
static const u32 gpio_CRH_CNF9_OUT_AFPP    = (0b10 <<  6);  /* port CoNFiguration pin 9, OUTput mode, Alternate Function output Push-Pull */
static const u32 gpio_CRH_MODE9_MASK       = (0b11 <<  4);
static const u32 gpio_CRH_MODE9_OUT_2MHZ   = (0b10 <<  4);  /* port MODE pin 9, OUTput mode, 2MHZ */
/* TODO other GPIOx_CRH bits */

/* RM0008 table 3 */
static struct gpio * const GPIOA = (void *)0x40010800;
static struct gpio * const GPIOB = (void *)0x40010C00;
static struct gpio * const GPIOC = (void *)0x40011000;
static struct gpio * const GPIOD = (void *)0x40011400;
static struct gpio * const GPIOE = (void *)0x40011800;
static struct gpio * const GPIOF = (void *)0x40011C00;
static struct gpio * const GPIOG = (void *)0x40012000;

#endif

