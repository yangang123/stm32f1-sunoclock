/*
2017 David DiPaola
licensed under CC0 (public domain, see https://creativecommons.org/publicdomain/zero/1.0/)
*/

#include <cortexm.h>
#include <nvic.h>
#include <io/rcc.h>
#include <io/exti.h>
#include <io/pwr.h>
#include <io/gpio.h>
#include <io/tim.h>
#include <io/rtc.h>
#include <io/usart.h>

#include "lib/rtc/rtc.h"
#include "lib/usart/usart.h"

static const size
	SYSCLK_FREQ,
	AHB_FREQ,
	APB1_FREQ,
	APB2_FREQ
= 8000000;

static const size USART1_BAUD = 300;

static void
_setup_clock(void) {
	/* see RM0008 figure 8 for clock tree diagram */

	RCC->CR |= rcc_CR_HSEON;
	while ((RCC->CR & rcc_CR_HSERDY) == 0) {}

	RCC->CFGR = (RCC->CFGR & ~(rcc_CFGR_SW_MASK)) | rcc_CFGR_SW_HSE;
	while ((RCC->CFGR & rcc_CFGR_SWS_MASK) != rcc_CFGR_SWS_HSE) {}

	RCC->CR &= ~(rcc_CR_HSION);

	u32 cfgr = RCC->CFGR;
	cfgr = (cfgr & ~(rcc_CFGR_PPRE2_MASK)) | rcc_CFGR_PPRE2_DIV1;  /* APB2 */
	cfgr = (cfgr & ~(rcc_CFGR_PPRE1_MASK)) | rcc_CFGR_PPRE1_DIV1;  /* APB1 */
	cfgr = (cfgr & ~(rcc_CFGR_HPRE_MASK )) | rcc_CFGR_HPRE_DIV1;   /* AHB */
	RCC->CR = cfgr;
}

/* depends on _setup_clock() */
static void
_setup_led(void) {
	RCC->APB2ENR |= rcc_APB2ENR_IOPCEN;  /* see RM0008 figure 8 for clock tree diagram */

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
	RCC->APB2ENR |= (rcc_APB2ENR_TIM1EN | rcc_APB2ENR_IOPAEN | rcc_APB2ENR_AFIOEN);  /* see RM0008, figure 8 for clock tree diagram */

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

static void
_rtc_alarm_handler(void) {
	GPIOC->ODR ^= (1 << 13);

	u32 time = rtc_time_get();
	rtc_alarm_set(time + 1);
}

void
main(void) {
	_setup_clock();
	_setup_led();
	/*_setup_pwm_timer1();*/
	rtc_init(rtc_clksrc_LSE);
	rtc_alarm_handler_set(&_rtc_alarm_handler);
	usart_init_USART1(APB2_FREQ, USART1_BAUD);
	cortexm_interrupt_enable();
	usart_write_str_nl(USART1, "init complete");

	_rtc_alarm_handler();

	for (;;) {
		cortexm_interrupt_wait();

		usart_write_str(USART1, "time: ");
		u32 time = rtc_time_get();
		usart_write_hex_u32(USART1, time);
		usart_write_str_nl(USART1, NULL);
	}

	/*
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
	*/
}

