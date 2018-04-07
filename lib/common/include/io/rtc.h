#ifndef _STM32F1COMMON_RTC_H
#define _STM32F1COMMON_RTC_H

/* clock source: HSE /128 or LSE or LSI (selected by RCC BDCR) --> gated by RCC BDCR --> RTC */ /* RM0008 figure 8, figure 11, 18.1, 7.3.9 */

/* RM0008 18.4.7 */
struct __attribute__ ((__packed__)) rtc {
	/* access: u16 or u32, RM0008 18.4 */
	/* 0x00 */  volatile u32 CRH;   /* rtc Control Register High, RM0008 18.4.1 */
	/* 0x04 */  volatile u32 CRL;   /* rtc Control Register Low, RM0008 18.4.2 */
	/* 0x08 */  volatile u32 PRLH;  /* rtc PRescaler Load register High, RM0008 18.4.3 */
	/* 0x0C */  volatile u32 PRLL;  /* rtc PRescaler Load register Low, RM0008 18.4.3 */
	/* 0x10 */  volatile u32 DIVH;  /* rtc prescaler DIVider register High, RM0008 18.4.4 */
	/* 0x14 */  volatile u32 DIVL;  /* rtc prescaler DIVider register Low, RM0008 18.4.4 */
	/* 0x18 */  volatile u32 CNTH;  /* rtc CouNTer register High, RM0008 18.4.5 */
	/* 0x1C */  volatile u32 CNTL;  /* rtc CouNTer register Low, RM0008 18.4.5 */
	/* 0x20 */  volatile u32 ALRH;  /* rtc ALaRm register High, RM0008 18.4.6 */
	/* 0x24 */  volatile u32 ALRL;  /* rtc ALaRm register Low, RM0008 18.4.6 */
};

/* RM0008 18.4.1 */
static const u32 rtc_CRH_OWIE  = (1 << 2);  /* OverfloW Interrupt Enable */
static const u32 rtc_CRH_ALRIE = (1 << 1);  /* ALaRm Interrupt Enable */
static const u32 rtc_CRH_SECIE = (1 << 0);  /* SECond Interrupt Enable */

/* RM0008 18.4.2 */
static const u32 rtc_CRL_RTOFF = (1 << 5);  /* RTc operation OFF (write operation complete flag) */
static const u32 rtc_CRL_CNF   = (1 << 4);  /* CoNfiguration Flag */
static const u32 rtc_CRL_RSF   = (1 << 3);  /* Registers Synchronized Flag */
static const u32 rtc_CRL_OWF   = (1 << 2);  /* OverfloW Flag */
static const u32 rtc_CRL_ALRF  = (1 << 1);  /* ALaRm Flag */
static const u32 rtc_CRL_SECF  = (1 << 0);  /* SECond Flag */

/* RM0008 table 3 */
static struct rtc * const RTC = (void *)0x40002800;

#endif

