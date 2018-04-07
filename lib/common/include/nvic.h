#ifndef _STM32F1COMMON_NVIC_H
#define _STM32F1COMMON_NVIC_H

/* PM0056 4.3.11 */
struct __attribute__ ((__packed__)) nvic {
	/* 0x00 */  volatile u32 ISER0;  /* Interrupt Set-Enable Register 0, PM0056 4.3.2 */ /* for interrupts  0-31, PM0056 table 41 */
	/* 0x04 */  volatile u32 ISER1;  /* Interrupt Set-Enable Register 1, PM0056 4.3.2 */ /* for interrupts 32-63, PM0056 table 41 */
	/* TODO other NVIC registers */
};

/* converts interrupt numbers to register bits */
#define _INTNO_TO_BIT(regno,intno) (1 << ((intno)-(32*(regno))))

/* TODO nvic_ISER0 bits */

static const u32 nvic_ISER1_SETENA41, nvic_ISER1_RTCALARM = _INTNO_TO_BIT(1, 41);  /* SET-ENAble interrupt 41, PM0056 4.3.11 */ /* set-enable RTC ALARM through EXTI line interrupt, RM0008 table 61 position 41 */
/* TODO other nvic_ISER1 bits */

#undef _INTNO_TO_BIT

/* PM0056 4.3.11 */
static struct nvic * const NVIC = (void *)0xE000E100;

#endif

