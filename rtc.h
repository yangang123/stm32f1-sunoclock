#ifndef _RTC_H
#define _RTC_H

void
rtc_time_set(u32 value);

u32
rtc_time_get(void);

void
rtc_alarm_set(u32 value);

u32
rtc_alarm_get(void);

#endif

