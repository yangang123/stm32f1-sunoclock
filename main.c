#include <cortexm.h>
#include <io/rcc.h>
#include <io/gpio.h>
#include <io/timer6.h>
#include <io/power.h>

static const size HSE_FREQ = 8000000;  /* aka HSE OSC */
static const size LSE_FREQ =   32768;  /* aka LSE OSC */

static void
_setup_clock(void) {
	/* see RM0008, figure 11 for clock tree diagram */

	RCC_CLOCK |= RCC_CLOCK_HSE_ENABLE;
	while ((RCC_CLOCK & RCC_CLOCK_HSE_READY) == 0) {}

	RCC_CONFIG = (RCC_CONFIG & ~(RCC_CONFIG_SYSCLK_MASK)) | RCC_CONFIG_SYSCLK_HSE;
	while ((RCC_CONFIG & RCC_CONFIG_SYSCLK_STATUS_MASK) != RCC_CONFIG_SYSCLK_STATUS_HSE) {}

	RCC_CLOCK &= ~(RCC_CLOCK_HSI_ENABLE);
	
	u32 config = RCC_CONFIG;
	config = (config & ~(RCC_CONFIG_APB2_MASK)) | RCC_CONFIG_APB2_DIV1;
	config = (config & ~(RCC_CONFIG_APB1_MASK)) | RCC_CONFIG_APB1_DIV1;
	config = (config & ~(RCC_CONFIG_AHB_MASK )) | RCC_CONFIG_AHB_DIV1;
	RCC_CONFIG = config;
}

/* depends on _setup_clock() */
static void
_setup_led(void) {
	RCC_APB2ENABLE |= RCC_APB2ENABLE_GPIOC;  /* see RM0008, figure 8 for clock tree diagram */

	u32 config = *GPIOC_CONFIGHIGH;
	config = (config & ~(GPIOC_CONFIGHIGH_13CONFIG_MASK)) | GPIOC_CONFIGHIGH_13CONFIG_GENERALPUSHPULL;
	config = (config & ~(GPIOC_CONFIGHIGH_13MODE_MASK  )) | GPIOC_CONFIGHIGH_13MODE_OUTPUT2MHZ;
	*GPIOC_CONFIGHIGH = config;

	*GPIOC_OUTPUT &= ~(1 << 13);
}

/* depends on _setup_clock() */
static void
_setup_timer6(void) {
	RCC_APB1ENABLE |= RCC_APB1ENABLE_TIMER6;  /* see RM0008, figure 11 for clock tree diagram */

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
		* enable the power and backup interface clocks by setting the PWREN and BKPEN bits in the RCC_APB1ENR register
		* set the DBP bit the Power Control Register (PWR_CR) to enable access to the Backup registers and RTC
	*/
	RCC_APB1ENABLE |= (RCC_APB1ENABLE_POWER | RCC_APB1ENABLE_BACKUP);
	*POWER_CONTROL |= POWER_CONTROL_BACKUPWRITEENABLE;

	RCC_BACKUPCONTROL |= RCC_BACKUPCONTROL_LSEENABLE;
	while ((RCC_BACKUPCONTROL & RCC_BACKUPCONTROL_LSEREADY) == 0) {}

	u32 control = RCC_BACKUPCONTROL;
	control |= RCC_BACKUPCONTROL_RTCCLOCKENABLE;
	control = (control & ~(RCC_BACKUPCONTROL_RTCCLOCKSELECT_MASK)) | RCC_BACKUPCONTROL_RTCCLOCKSELECT_LSE;
	RCC_BACKUPCONTROL = control;
}

void
main(void) {
	_setup_clock();
	_setup_led();
	_setup_timer6();
	_setup_rtc();

	*GPIOC_OUTPUT &= ~(1 << 13);
	for (size i=0; i<100000; i++) cortexm_noop();
	*GPIOC_OUTPUT |= (1 << 13);
	for (size i=0; i<100000; i++) cortexm_noop();

	while (*TIMER6_CONTROL1 & TIMER6_CONTROL1_ENABLE) {};
	*GPIOC_OUTPUT &= ~(1 << 13);
}

