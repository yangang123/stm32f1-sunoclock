#include <cortexm.h>
#include <io/rcc.h>
#include <io/gpio.h>
#include <io/timer6.h>

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

static void
_setup_led(void) {
	RCC_APB2ENABLE |= RCC_APB2ENABLE_GPIOC;  /* see RM0008, figure 8 for clock tree diagram */

	u32 config = *GPIOC_CONFIGHIGH;
	config = (config & ~(GPIOC_CONFIGHIGH_13CONFIG_MASK)) | GPIOC_CONFIGHIGH_13CONFIG_GENERALPUSHPULL;
	config = (config & ~(GPIOC_CONFIGHIGH_13MODE_MASK  )) | GPIOC_CONFIGHIGH_13MODE_OUTPUT2MHZ;
	*GPIOC_CONFIGHIGH = config;

	*GPIOC_OUTPUT &= ~(1 << 13);
}

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

void
main(void) {
	_setup_clock();
	_setup_led();
	_setup_timer6();

	*GPIOC_OUTPUT &= ~(1 << 13);
	for (size i=0; i<100000; i++) cortexm_noop();
	*GPIOC_OUTPUT |= (1 << 13);
	for (size i=0; i<100000; i++) cortexm_noop();

	while (*TIMER6_CONTROL1 & TIMER6_CONTROL1_ENABLE) {};
	*GPIOC_OUTPUT &= ~(1 << 13);
}

