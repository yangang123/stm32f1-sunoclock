#ifndef _RTC_H
#define _RTC_H

enum rtc_clksrc {
	rtc_clksrc_LSE,
	rtc_clksrc_LSI,
	rtc_clksrc_HSE,
};

void
rtc_init(enum rtc_clksrc clksrc);

void
rtc_time_set(u32 value);

u32
rtc_time_get(void);

void
rtc_alarm_set(u32 value);

u32
rtc_alarm_get(void);

void
rtc_alarm_handler_set(void (*handler)(void));

#endif

