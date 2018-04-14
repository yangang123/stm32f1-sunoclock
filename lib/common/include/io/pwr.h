/*
2017 David DiPaola
licensed under CC0 (public domain, see https://creativecommons.org/publicdomain/zero/1.0/)
*/

#ifndef _COMMON_PWR_H
#define _COMMON_PWR_H

/* clock source: SYSCLK --> AHB -- > APB1 (36Mhz max) --> PWR */ /* RM0008 figure 8, figure 11, 7.3.8 */

/* RM0008 5.4.3 */
struct __attribute__ ((__packed__)) pwr {
	/* 0x00 */  volatile u32 CR;   /* power Control Register, RM0008 5.4.1 */
	/* 0x04 */  volatile u32 CSR;  /* power Control/Status Register, RM0008 5.4.2 */
};

/* RM0008 5.4.1 */
static const u32 pwr_CR_DBP = (1 << 8);  /* Disable Backup domain write Protection */
/* TODO other CR bits */

/* TODO CSR bits */

/* RM0008 table 3 */
static struct pwr * const PWR = (void *)0x40007000;

#endif

