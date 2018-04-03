#include <io/rtc.h>

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

