/*
2017 David DiPaola
licensed under CC0 (public domain, see https://creativecommons.org/publicdomain/zero/1.0/)
*/

#ifndef _COMMON_EXTI_H
#define _COMMON_EXTI_H

/* RM0008 10.3.7 */
struct __attribute__ ((__packed__)) exti {
	/* 0x00 */  volatile u32 IMR;    /* Interrupt Mask Register, RM0008 10.3.1 */
	/* 0x04 */  volatile u32 EMR;    /* Event Mask Register, RM0008 10.3.2 */ /* TODO confirm */
	/* 0x08 */  volatile u32 RTSR;   /* Rising Trigger Selection Register, RM0008 10.3.3 */
	/* 0x0C */  volatile u32 FTSR;   /* Falling Trigger Selection Register, RM0008 10.3.4 */ /* TODO confirm */
	/* 0x10 */  volatile u32 SWIER;  /* SoftWare Interrupt Event Register, RM0008 10.3.5 */ /* TODO confirm */
	/* 0x14 */  volatile u32 PR;     /* Pending Register, RM0008 10.3.6 */
};

/* RM0008 10.3.1 */
static const u32 exti_IMR_MR17, exti_IMR_RTCALARM = (1 << 17);  /* Mask Request 17 */ /* RM0008 figure 21 */
/* TODO other IMR bits */

/* RM0008 10.3.3 */
static const u32 exti_RTSR_TR17, exti_RTSR_RTCALARM = (1 << 17);  /* Rising trigger for Request 17 */ /* RM0008 figure 21 */
/* TODO other RTSR bits */

/* RM0008 10.3.6 */
static const u32 exti_PR_PR17, exti_PR_RTCALARM = (1 << 17);  /* Pending Request 17 */ /* RM0008 figure 21 */
/* TODO other PR bits */

/* RM0008 table 3 */
static struct exti * const EXTI = (void *)0x40010400;

#endif

