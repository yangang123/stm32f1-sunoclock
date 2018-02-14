#include <cortexm.h>
#include <nvic.h>
#include <io/rcc.h>
#include <io/exti.h>
#include <io/power.h>
#include <io/gpio.h>
#include <io/timer1.h>
#include <io/timer6.h>
#include <io/rtc.h>

#include "rtc.h"

static const size HSE_FREQ = 8000000;  /* aka HSE OSC */
static const size LSE_FREQ =   32768;  /* aka LSE OSC */

static void
_setup_clock(void) {
	/* see RM0008, figure 11 for clock tree diagram */

	*RCC_CLOCK |= RCC_CLOCK_HSE_ENABLE;
	while ((*RCC_CLOCK & RCC_CLOCK_HSE_READY) == 0) {}

	*RCC_CONFIG = (*RCC_CONFIG & ~(RCC_CONFIG_SYSCLK_MASK)) | RCC_CONFIG_SYSCLK_HSE;
	while ((*RCC_CONFIG & RCC_CONFIG_SYSCLK_STATUS_MASK) != RCC_CONFIG_SYSCLK_STATUS_HSE) {}

	*RCC_CLOCK &= ~(RCC_CLOCK_HSI_ENABLE);

	u32 config = *RCC_CONFIG;
	config = (config & ~(RCC_CONFIG_APB2_MASK)) | RCC_CONFIG_APB2_DIV1;
	config = (config & ~(RCC_CONFIG_APB1_MASK)) | RCC_CONFIG_APB1_DIV1;
	config = (config & ~(RCC_CONFIG_AHB_MASK )) | RCC_CONFIG_AHB_DIV1;
	*RCC_CONFIG = config;
}

/* depends on _setup_clock() */
static void
_setup_led(void) {
	*RCC_APB2ENABLE |= RCC_APB2ENABLE_GPIOC;  /* see RM0008, figure 8 for clock tree diagram */

	u32 config = *GPIOC_CONFIGHIGH;
	config = (config & ~(GPIOC_CONFIGHIGH_13CONFIG_MASK)) | GPIOC_CONFIGHIGH_13CONFIG_GENERALPUSHPULL;
	config = (config & ~(GPIOC_CONFIGHIGH_13MODE_MASK  )) | GPIOC_CONFIGHIGH_13MODE_OUTPUT2MHZ;
	*GPIOC_CONFIGHIGH = config;

	*GPIOC_OUTPUT &= ~(1 << 13);
}

/* depends on _setup_clock() */
static void
_setup_pwm_timer1(void) {
	*RCC_APB2ENABLE |= (RCC_APB2ENABLE_TIMER1 | RCC_APB2ENABLE_GPIOA | RCC_APB2ENABLE_ALTERNATEFUNCTIONIO);  /* see RM0008, figure 8 for clock tree diagram */

	u32 gac = *GPIOA_CONFIGHIGH;
	/* timer1 channel2 pin init */
	gac = (gac & ~(GPIOA_CONFIGHIGH_9CONFIG_MASK)) | GPIOA_CONFIGHIGH_9CONFIG_OUTPUTALTERNATEPUSHPULL;
	gac = (gac & ~(GPIOA_CONFIGHIGH_9MODE_MASK  )) | GPIOA_CONFIGHIGH_9MODE_OUTPUT2MHZ;
	/* TODO timer1 channel3 pin init */
	/* TODO timer1 channel4 pin init */
	*GPIOA_CONFIGHIGH = gac;

	/* see RM0008, 14.3.10 */
	u16 t1ccm1 = *TIMER1_CAPTURECOMPAREMODE1;
	/* timer1 channel2 PWM mode init */
	t1ccm1 = (t1ccm1 & ~(TIMER1_CAPTURECOMPAREMODE1_2MODE_MASK     )) | TIMER1_CAPTURECOMPAREMODE1_2MODE_PWMMODE1;
	t1ccm1 = (t1ccm1 & ~(TIMER1_CAPTURECOMPAREMODE1_2SELECTION_MASK)) | TIMER1_CAPTURECOMPAREMODE1_2SELECTION_OUTPUT;
	t1ccm1 |= TIMER1_CAPTURECOMPAREMODE1_2PRELOADENABLE;
	/* TODO timer1 channel3 PWM mode init */
	/* TODO timer1 channel4 PWM mode init */
	*TIMER1_CAPTURECOMPAREMODE1 = t1ccm1;

	*TIMER1_CAPTURECOMPAREENABLE |= TIMER1_CAPTURECOMPAREENABLE_2OUTPUTPOLARITY;
	*TIMER1_CAPTURECOMPAREENABLE |= TIMER1_CAPTURECOMPAREENABLE_2OUTPUTENABLE;

	*TIMER1_BREAKANDDEADTIME |= TIMER1_BREAKANDDEADTIME_MAINOUTPUTENABLE;  /* see RM0008, table 83 */

	*TIMER1_CONTROL1 |= TIMER1_CONTROL1_RELOADPRELOADENABLE;  /* see RM0008, 14.3.10 */

	*TIMER1_PRESCALER = 7999;

	*TIMER1_RELOAD = 0xFFFF;  /* PWM frequency */ /* see RM0008, 14.3.10 */

	*TIMER1_CAPTURECOMPARE2 = 0x8000;  /* PWM duty cycle */ /* see RM0008, 14.3.10 */
	/* TODO timer1 channel3 compare init */
	/* TODO timer1 channel4 compare init */

	*TIMER1_VALUE = 0;

	*TIMER1_EVENT |= TIMER1_EVENT_UPDATE;  /* see RM0008, 14.3.10 */

	*TIMER1_CONTROL1 |= TIMER1_CONTROL1_ENABLE;
}

/* depends on _setup_clock() */
static void
_setup_timer6(void) {
	*RCC_APB1ENABLE |= RCC_APB1ENABLE_TIMER6;  /* see RM0008, figure 11 for clock tree diagram */

	*TIMER6_PRESCALER = 23999;

	*TIMER6_RELOAD = 10000;

	*TIMER6_VALUE = 0;

	*TIMER6_EVENT |= TIMER6_EVENT_UPDATE;

	/* TODO remove these */
	//TIMER6_CONTROL1 = (TIMER6_CONTROL1_UPDATEEVENTDISABLE | TIMER6_CONTROL1_ENABLE);
	//TIMER6_CONTROL1 |= (TIMER6_CONTROL1_ONEPULSEMODE | TIMER6_CONTROL1_ENABLE);
	*TIMER6_CONTROL1 |= (TIMER6_CONTROL1_ENABLE);
}

/* depends on _setup_clock() */
static void
_setup_rtc(void) {
	/* RM0008, 18.1:
		To enable access to the Backup registers and the RTC, proceed as follows:
			* enable the power and backup interface clocks by setting the PWREN and BKPEN bits in the RCC_APB1ENR register
			* set the DBP bit the Power Control Register (PWR_CR) to enable access to the Backup registers and RTC
	*/
	*RCC_APB1ENABLE |= (RCC_APB1ENABLE_POWER | RCC_APB1ENABLE_BACKUP);
	*POWER_CONTROL |= POWER_CONTROL_BACKUPWRITEENABLE;

	if ((*RCC_BACKUPCONTROL & RCC_BACKUPCONTROL_LSEREADY) == 0) {
		*RCC_BACKUPCONTROL |= RCC_BACKUPCONTROL_LSEENABLE;
		while ((*RCC_BACKUPCONTROL & RCC_BACKUPCONTROL_LSEREADY) == 0) {}
	}

	u32 control = *RCC_BACKUPCONTROL;
	control |= RCC_BACKUPCONTROL_RTCCLOCKENABLE;
	control = (control & ~(RCC_BACKUPCONTROL_RTCCLOCKSELECT_MASK)) | RCC_BACKUPCONTROL_RTCCLOCKSELECT_LSE;
	*RCC_BACKUPCONTROL = control;

	*RTC_CONTROLHIGH |= RTC_CONTROLHIGH_ALARMINTERRUPTENABLE;

	*EXTI_RISINGTRIGGER |= EXTI_RISINGTRIGGER_RTCALARM;
	*EXTI_INTERRUPTMASK |= EXTI_INTERRUPTMASK_RTCALARM;
	*NVIC_ENABLE32TO63_SET = NVIC_ENABLE32TO63_SET_EXTIRTCALARM;
}

const u32 TIME_MINUTE = 60;
const u32 TIME_HOUR   = 60 * 60;
const u32 TIME_DAY    = 60 * 60 * 24;

static void
_alarm_get(u8f *out_alarm_hour, u8f *out_alarm_minute) {
	u32 alarm = rtc_alarm_get();

	u32 alarm_offset = alarm % TIME_DAY;
	*out_alarm_hour   = alarm_offset / TIME_HOUR;
	*out_alarm_minute = alarm_offset % TIME_MINUTE;
}

static void
_alarm_arm(u8f alarm_hour, u8f alarm_minute) {
	u32 time = rtc_time_get();

	u32 alarm_offset = (alarm_hour * TIME_HOUR) + (alarm_minute * TIME_MINUTE);
	u32 today_start = time - (time % TIME_DAY);
	u32 today_alarm = today_start + alarm_offset;
	if (time < today_alarm) {
		rtc_alarm_set(today_alarm);
	}
	else {
		u32 tomorrow_start = today_start + TIME_DAY;
		u32 tomorrow_alarm = tomorrow_start + alarm_offset;
		rtc_alarm_set(tomorrow_alarm);
	}
}

__attribute__((__interrupt__))
void
isr_exti_rtcalarm(void) {
	*EXTI_PENDING |= EXTI_PENDING_RTCALARM;
	*RTC_CONTROLLOW &= ~(RTC_CONTROLLOW_ALARMFLAG);

	*GPIOC_OUTPUT ^= (1 << 13);

	u32 time = rtc_time_get();
	rtc_alarm_set(time + 3);
}

void
main(void) {
	_setup_clock();
	_setup_led();
	_setup_pwm_timer1();
	_setup_timer6();
	_setup_rtc();
	cortexm_interrupt_enable();

	/*
	u8f alarm_hour;
	u8f alarm_minute;
	_alarm_get(&alarm_hour, &alarm_minute);
	_alarm_arm(alarm_hour, alarm_minute);
	*/

	*TIMER1_CAPTURECOMPARE2 = 0x8000;

	u32 time = rtc_time_get();
	rtc_alarm_set(time + 3);

	for (;;) {
		cortexm_interrupt_wait();
	}
}

