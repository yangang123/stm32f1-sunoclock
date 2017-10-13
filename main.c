#include <cortexm.h>
#include <io/rcc.h>
#include <io/gpio.h>

#define HSE_FREQ 8000000  /* aka HSE OSC */
#define LSE_FREQ   32768  /* aka LSE OSC */

static void
_setup_clock(void) {
	/* see RM0008, figure 11 for clock tree diagram */

	RCC_CLOCK |= RCC_CLOCK_HSE_ENABLE;
	while ((RCC_CLOCK & RCC_CLOCK_HSE_READY) == 0) {}

	RCC_CONFIG = (RCC_CONFIG & ~(RCC_CONFIG_SYSCLK_MASK)) | RCC_CONFIG_SYSCLK_HSE;
	while ((RCC_CONFIG & RCC_CONFIG_SYSCLK_STATUS_MASK) != RCC_CONFIG_SYSCLK_STATUS_HSE) {}

	RCC_CLOCK &= ~(RCC_CLOCK_HSI_ENABLE);

	u32f config = RCC_CONFIG;
	config = (config & ~(RCC_CONFIG_APB2_MASK)) | RCC_CONFIG_APB2_DIV1;
	config = (config & ~(RCC_CONFIG_APB1_MASK)) | RCC_CONFIG_APB1_DIV1;
	config = (config & ~(RCC_CONFIG_AHB_MASK )) | RCC_CONFIG_AHB_DIV1;
	RCC_CONFIG = config;
}

static void
_setup_led(void) {
	RCC_APB2ENABLE |= RCC_APB2ENABLE_GPIOC;  /* see RM0008, figure 8 for clock tree diagram */

	u32f config = GPIOC_CRH;
	config = (config & ~(GPIOC_CRH_CNF_13_MASK )) | GPIOC_CRH_CNF_13_GENERAL_PUSHPULL;
	config = (config & ~(GPIOC_CRH_MODE_13_MASK)) | GPIOC_CRH_MODE_13_OUTPUT_2MHZ;
	GPIOC_CRH = config;

	GPIOC_ODR &= ~(1 << 13);
}



#define TIMER6 0x40001000  /* RM0008, table 3 */ /* aka TIM6 */

#define TIMER6_CONTROL1 IO_u16(TIMER6 + 0x00)  /* RM0008, 17.4.1 */ /* aka TIM6_CR1 */
#define TIMER6_CONTROL1_RELOADPRELOADENABLE (1 << 7)  /* aka ARPE */
#define TIMER6_CONTROL1_ONEPULSEMODE        (1 << 3)  /* aka OPM */
#define TIMER6_CONTROL1_UPDATEEVENTSOURCE   (1 << 2)  /* aka URS */
#define TIMER6_CONTROL1_UPDATEEVENTDISABLE  (1 << 1)  /* aka UDIS */
#define TIMER6_CONTROL1_ENABLE              (1 << 0)  /* aka CEN */

#define TIMER6_STATUS IO_u16(TIMER6 + 0x10)  /* RM0008, 17.4.4 */ /* aka TIM6_SR */
#define TIMER6_STATUS_UPDATEEVENTFLAG (1 << 0)  /* aka UIF */

#define TIMER6_EVENT IO_u16(TIMER6 + 0x14)  /* RM0008, 17.4.5 */ /* aka TIM6_EGR */
#define TIMER6_EVENT_UPDATE (1 << 0)  /* aka UG */

#define TIMER6_VALUE IO_u16(TIMER6 + 0x24)  /* RM0008, 17.4.6 */ /* aka TIM6_CNT */

#define TIMER6_PRESCALER IO_u16(TIMER6 + 0x28)  /* RM0008, 17.4.7 */ /* aka TIM6_PSC */

#define TIMER6_RELOAD IO_u16(TIMER6 + 0x2C)  /* RM0008, 17.4.8 */ /* aka TIM6_ARR */

static void
_setup_timer6(void) {
	RCC_APB1ENABLE |= RCC_APB1ENABLE_TIMER6;  /* see RM0008, figure 11 for clock tree diagram */

	TIMER6_PRESCALER = 23999;

	TIMER6_RELOAD = 10000;

	TIMER6_VALUE = 0;

	TIMER6_EVENT |= TIMER6_EVENT_UPDATE;

	/* TODO remove these */
	//TIMER6_CONTROL1 = (TIMER6_CONTROL1_UPDATEEVENTDISABLE | TIMER6_CONTROL1_ENABLE);
	//TIMER6_CONTROL1 |= (TIMER6_CONTROL1_ONEPULSEMODE | TIMER6_CONTROL1_ENABLE);
	TIMER6_CONTROL1 |= (TIMER6_CONTROL1_ENABLE);
}

void
main(void) {
	_setup_clock();
	_setup_led();
	_setup_timer6();

	GPIOC_ODR &= ~(1 << 13);
	for (size i=0; i<100000; i++) cortexm_noop();
	GPIOC_ODR |= (1 << 13);
	for (size i=0; i<100000; i++) cortexm_noop();

	while (TIMER6_CONTROL1 & TIMER6_CONTROL1_ENABLE) {};
	GPIOC_ODR &= ~(1 << 13);
}

