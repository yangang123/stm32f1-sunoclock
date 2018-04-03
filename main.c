#include <cortexm.h>
#include <nvic.h>
#include <io/rcc.h>
#include <io/exti.h>
#include <io/power.h>
#include <io/gpio.h>
#include <io/tim.h>
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

	u32 crh = GPIOC->CRH;
	crh = (crh & ~(gpio_CRH_CNF13_MASK )) | gpio_CRH_CNF13_OUT_GPPP;
	crh = (crh & ~(gpio_CRH_MODE13_MASK)) | gpio_CRH_MODE13_OUT_2MHZ;
	GPIOC->CRH = crh;

	GPIOC->ODR &= ~(1 << 13);
}

/* depends on _setup_pwm_timer1() */
static void
_pwm_timer1_set(u8 red, u8 green, u8 blue) {
	/* PWM duty cycle */ /* see RM0008, 14.3.10 */
	tim_TIM1->CCR2 = (  red << 8) | (  red << 0);
	/* 
	tim_TIM1->CCR3 = (green << 8) | (green << 0);
	tim_TIM1->CCR4 = ( blue << 8) | ( blue << 0);
	*/
}


/* depends on _setup_clock() */
static void
_setup_pwm_timer1(void) {
	*RCC_APB2ENABLE |= (RCC_APB2ENABLE_TIMER1 | RCC_APB2ENABLE_GPIOA | RCC_APB2ENABLE_ALTERNATEFUNCTIONIO);  /* see RM0008, figure 8 for clock tree diagram */

	u32 crh = GPIOA->CRH;
	/* timer1 channel2 pin init */
	crh = (crh & ~(gpio_CRH_CNF9_MASK )) | gpio_CRH_CNF9_OUT_AFPP;
	crh = (crh & ~(gpio_CRH_MODE9_MASK)) | gpio_CRH_MODE9_OUT_2MHZ;
	/* TODO timer1 channel3 pin init */
	/* TODO timer1 channel4 pin init */
	GPIOA->CRH = crh;

	/* see RM0008 14.3.10 */
	u32 ccmr1 = tim_TIM1->CCMR1;
	/* timer1 channel2 PWM mode init */
	ccmr1 = (ccmr1 & ~(tim_CCMR1_OC2M_MASK)) | tim_CCMR1_OC2M_PWMMODE1;
	ccmr1 = (ccmr1 & ~(tim_CCMR1_CC2S_MASK)) | tim_CCMR1_CC2S_OUTPUT;
	ccmr1 |= tim_CCMR1_OC2PE;
	/* TODO timer1 channel3 PWM mode init */
	/* TODO timer1 channel4 PWM mode init */
	tim_TIM1->CCMR1 = ccmr1;

	u32 ccer = tim_TIM1->CCER;
	ccer |= tim_CCER_CC2P;
	ccer |= tim_CCER_CC2E;
	tim_TIM1->CCER = ccer;

	tim_TIM1->BDTR |= tim_BDTR_MOE;  /* see RM0008, table 83 */

	tim_TIM1->CR1 |= tim_CR1_ARPE;  /* see RM0008, 14.3.10 */

	tim_TIM1->PSC = 0;

	tim_TIM1->ARR = 0xFFFF;  /* PWM frequency */ /* see RM0008, 14.3.10 */

	_pwm_timer1_set(0, 0, 0);

	tim_TIM1->CNT = 0;

	tim_TIM1->EGR |= tim_EGR_UG;  /* see RM0008, 14.3.10 */

	tim_TIM1->CR1 |= tim_CR1_CEN;
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
	NVIC->ISER1 = nvic_ISER1_RTCALARM;
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

	GPIOC->ODR ^= (1 << 13);

	u32 time = rtc_time_get();
	rtc_alarm_set(time + 3);
}

void
main(void) {
	_setup_clock();
	_setup_led();
	_setup_pwm_timer1();
	_setup_rtc();
	cortexm_interrupt_enable();

	/*
	u8f alarm_hour;
	u8f alarm_minute;
	_alarm_get(&alarm_hour, &alarm_minute);
	_alarm_arm(alarm_hour, alarm_minute);
	*/

	/*
	u32 time = rtc_time_get();
	rtc_alarm_set(time + 3);
	*/

	for (;;) {
		for (i32 i=0; i<0xFF; i++) {
			for (size j=0; j<0x2000; j++) { cortexm_noop(); }
			_pwm_timer1_set(i, 0, 0);
		}
		for (i32 i=0xFF; i>=0; i--) {
			for (size j=0; j<0x2000; j++) { cortexm_noop(); }
			_pwm_timer1_set(i, 0, 0);
		}
	}
}

