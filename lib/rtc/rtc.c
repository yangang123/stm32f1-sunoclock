/*
2018 David DiPaola
licensed under CC0 (public domain, see https://creativecommons.org/publicdomain/zero/1.0/)
*/

#include <io/rtc.h>
#include <io/rcc.h>
#include <io/pwr.h>
#include <io/exti.h>
#include <nvic.h>

#include "rtc.h"

#define NULL 0

static void (*_handler_alarm)(void) = NULL;

__attribute__((__interrupt__))
void
isr_exti_rtcalarm(void) {
	EXTI->PR |= exti_PR_RTCALARM;
	RTC->CRL &= ~(rtc_CRL_ALRF);

	if (_handler_alarm != NULL) {
		_handler_alarm();
	}
}

void
rtc_init(enum rtc_clksrc clksrc) {
	/* RM0008 18.1:
		To enable access to the Backup registers and the RTC, proceed as follows:
			* enable the power and backup interface clocks by setting the PWREN and BKPEN bits in the RCC_APB1ENR register
			* set the DBP bit the Power Control Register (PWR_CR) to enable access to the Backup registers and RTC
	*/
	RCC->APB1ENR |= (rcc_APB1ENR_PWREN | rcc_APB1ENR_BKPEN);
	PWR->CR |= pwr_CR_DBP;

	if (clksrc == rtc_clksrc_LSE) {
		if ((RCC->BDCR & rcc_BDCR_LSERDY) == 0) {
			RCC->BDCR |= rcc_BDCR_LSEON;
			while ((RCC->BDCR & rcc_BDCR_LSERDY) == 0) {}
		}

		u32 bdcr = RCC->BDCR;
		bdcr |= rcc_BDCR_RTCEN;
		bdcr = (bdcr & ~(rcc_BDCR_RTCSEL_MASK)) | rcc_BDCR_RTCSEL_LSE;
		RCC->BDCR = bdcr;
	}
	/* TODO other clock sources */
}

static void
_configmode_begin(void) {
	/* RM0008 18.3.4:
		Configuration procedure:
			1. Poll RTOFF, wait until its value goes to '1'
			2. Set the CNF bit to enter configuration mode
			[...]
	*/
	while ((RTC->CRL & rtc_CRL_RTOFF) == 0) {}
	RTC->CRL |= rtc_CRL_CNF;
}

static void
_configmode_end(void) {
	/* RM0008 18.3.4:
		Configuration procedure:
			[...]
			4. Clear the CNF bit to exit configuration mode
			5. Poll RTOFF, wait until its value goes to '1' to check the end of the write operation
	*/
	RTC->CRL &= ~(rtc_CRL_CNF);
	while ((RTC->CRL & rtc_CRL_RTOFF) == 0) {}
}

void
rtc_time_set(u32 value) {
	_configmode_begin();

	RTC->CNTL = value;
	RTC->CNTH = value >> 16;

	_configmode_end();
}

u32
rtc_time_get(void) {
	u32 value = 0;

	value |= RTC->CNTL;
	value |= RTC->CNTH << 16;

	return value;
}

void
rtc_alarm_set(u32 value) {
	_configmode_begin();

	RTC->ALRL = value;
	RTC->ALRH = value >> 16;

	_configmode_end();
}

u32
rtc_alarm_get(void) {
	u32 value = 0;

	value |= RTC->ALRL;
	value |= RTC->ALRH << 16;

	return value;
}

void
rtc_alarm_handler_set(void (*handler)(void)) {
	_handler_alarm = handler;

	if (_handler_alarm != NULL) {
		RTC->CRH |= rtc_CRH_ALRIE;

		EXTI->RTSR |= exti_RTSR_RTCALARM;
		EXTI->IMR |= exti_IMR_RTCALARM;
		NVIC->ISER1 = nvic_ISER1_RTCALARM;
	}
	else {
		/* TODO test this */
		RTC->CRH &= ~(rtc_CRH_ALRIE);
	}
}

