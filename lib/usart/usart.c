/*
2018 David DiPaola
licensed under CC0 (public domain, see https://creativecommons.org/publicdomain/zero/1.0/)
*/

#include <io/rcc.h>
#include <io/gpio.h>
#include <io/usart.h>

void
usart_init(struct usart * urt, size clkspd, size baud) {
	if (urt == USART1) {
		/* RM0008 figure 1, figure 8, figure 11 */
		RCC->APB2ENR |= (rcc_APB2ENR_USART1EN | rcc_APB2ENR_IOPAEN | rcc_APB2ENR_AFIOEN);

		/* RM0008 table 24, table 54 */
		u32 crh = GPIOA->CRH;
		u32 odr = GPIOA->ODR;
		/* set TX pin to alternate function push-pull at 2Mhz */ /* RM0008 table 54 */
		crh = (crh & ~(gpio_CRH_CNF9_MASK )) | gpio_CRH_CNF9_OUT_AFPP;
		crh = (crh & ~(gpio_CRH_MODE9_MASK)) | gpio_CRH_MODE9_OUT_2MHZ;
		/* set RX pin to input with pull-up */ /* RM0008 table 54 */
		crh = (crh & ~(gpio_CRH_CNF10_MASK )) | gpio_CRH_CNF10_IN_PUPD;
		crh = (crh & ~(gpio_CRH_MODE10_MASK)) | gpio_CRH_MODE10_IN;
		odr |= (1 << 10);
		/* done */
		GPIOA->CRH = crh;
		GPIOA->ODR = odr;
	}
	/* TODO other USARTs */

	urt->BRR = usart_BRR_MACRO(clkspd, baud);

	urt->CR1 |= (usart_CR1_UE | usart_CR1_TE | usart_CR1_RE);
}

void
usart_write_chr(struct usart * urt, u8 chr) {
	while ((urt->SR & usart_SR_TC) == 0) {}
	urt->DR = chr;
}

void
usart_write_hex_u4(struct usart * urt, u8 hex) {
	hex &= 0b1111;

	if (hex <= 0x9) {
		usart_write_chr(urt, '0'+(hex-0x0));
	}
	else {
		usart_write_chr(urt, 'A'+(hex-0xA));
	}
}

void
usart_write_hex_u8(struct usart * urt, u8 hex) {
	usart_write_hex_u4(urt, hex >> 4);
	usart_write_hex_u4(urt, hex >> 0);
}

void
usart_write_hex_u16(struct usart * urt, u16 hex) {
	usart_write_hex_u8(urt, hex >> 8);
	usart_write_hex_u8(urt, hex >> 0);
}

void
usart_write_hex_u32(struct usart * urt, u32 hex) {
	usart_write_hex_u16(urt, hex >> 16);
	usart_write_hex_u16(urt, hex >>  0);
}

void
usart_write_str(struct usart * urt, const u8 * str) {
	if (str == NULL) {
		return;
	}

	for (size i=0; str[i]!='\0'; i++) {
		usart_write_chr(urt, str[i]);
	}
}

void
usart_write_str_nl(struct usart * urt, const u8 * str) {
	usart_write_str(urt, str);
	usart_write_str(urt, "\r\n");
}

