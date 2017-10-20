#include <io/rtc.h>

static void
_configmode_begin(void) {
	/* RM0008, 18.3.4:
		Configuration procedure:
			1. Poll RTOFF, wait until its value goes to '1'
			2. Set the CNF bit to enter configuration mode
			[...]
	*/
	while ((*RTC_CONTROLLOW & RTC_CONTROLLOW_WRITEDONE) == 0) {}
	*RTC_CONTROLLOW |= RTC_CONTROLLOW_CONFIGMODE;
}

static void
_configmode_end(void) {
	/* RM0008, 18.3.4:
		Configuration procedure:
			[...]
			4. Clear the CNF bit to exit configuration mode
			5. Poll RTOFF, wait until its value goes to '1' to check the end of the write operation
	*/
	*RTC_CONTROLLOW &= ~(RTC_CONTROLLOW_CONFIGMODE);
	while ((*RTC_CONTROLLOW & RTC_CONTROLLOW_WRITEDONE) == 0) {}
}

void
rtc_time_set(u32 value) {
	_configmode_begin();

	*RTC_VALUELOW  = value;
	*RTC_VALUEHIGH = value >> 16;

	_configmode_end();
}

u32
rtc_time_get(void) {
	u32 value = 0;

	value |= *RTC_VALUELOW;
	value |= *RTC_VALUEHIGH << 16;

	return value;
}

void
rtc_alarm_set(u32 value) {
	_configmode_begin();

	*RTC_ALARMLOW  = value;
	*RTC_ALARMHIGH = value >> 16;

	_configmode_end();
}

u32
rtc_alarm_get(void) {
	u32 value = 0;

	value |= *RTC_ALARMLOW;
	value |= *RTC_ALARMHIGH << 16;

	return value;
}

