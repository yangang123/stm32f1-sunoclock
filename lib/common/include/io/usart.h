#ifndef _STM32F1COMMON_USART_H
#define _STM32F1COMMON_USART_H

/* RM0008 figure 1, figure 8, figure 11 */
/*
clock sources:
	USART2/3/4/5: SYSCLK --> AHB -- > APB1 (36Mhz max) --> USARTx
	USART1:       SYSCLK --> AHB -- > APB2 (72Mhz max) --> USART1
*/

/* RM0008 27.6.8 */
struct __attribute__ ((__packed__)) usart {
	/* 0x00 */  volatile u32 SR;    /* Status Register, RM0008 27.6.1 */
	/* 0x04 */  volatile u32 DR;    /* Data Register, RM0008 27.6.2 */
	/* 0x08 */  volatile u32 BRR;   /* Baud Rate Register, RM0008 27.6.3 */
	/* 0x0C */  volatile u32 CR1;   /* Control Register 1, RM0008 27.6.4 */
	/* 0x10 */  volatile u32 CR2;   /* Control Register 2, RM0008 27.6.5 */
	/* 0x14 */  volatile u32 CR3;   /* Control Register 3, RM0008 27.6.6 */
	/* 0x18 */  volatile u32 GTPR;  /* Guard Time and Prescaler Register, RM0008 27.6.7 */
};

/* RM0008 27.6.1 */
static const u32 usart_SR_CTS  = (1 << 9);  /* Clear To Send flag */
static const u32 usart_SR_LBD  = (1 << 8);  /* Lin Break Detection flag */
static const u32 usart_SR_TXE  = (1 << 7);  /* Transmit data register Empty, read only */
static const u32 usart_SR_TC   = (1 << 6);  /* Transmission Complete */
static const u32 usart_SR_RXNE = (1 << 5);  /* Receive data register Not Empty */
static const u32 usart_SR_IDLE = (1 << 4);  /* IDLE line detected, read only */
static const u32 usart_SR_ORE  = (1 << 3);  /* OveRrun Error, read only */
static const u32 usart_SR_NE   = (1 << 2);  /* Noise Error, read only */
static const u32 usart_SR_FE   = (1 << 1);  /* Framing Error, read only */
static const u32 usart_SR_PE   = (1 << 0);  /* Parity Error, read only */

/* RM0008 27.6.3 */
/*
baud --> register formula:
	USART divider value = clock in / (16 * baud)
USART divider register formula (RM0008 27.3.4):
	USART divider register = mantissa + (fraction / 16)
register --> baud formula (RM0008 27.3.4):
	baud = clock in / (16 * USART divider)
mantissa: the integer part of the USART divider value
fraction: the "decimal" part of the USART divider value but as a fraction of 16 not 1
example: 8Mhz APB2, 300baud
	divisor: 1666.67
		because: 8000000hz / (16 * 300baud) = 1666.67
	mantissa: 1666
		because: floor(divisor) = floor(1666.67) = 1666
	fraction: 10
		because: floor((divisor - mantissa) * 16) = floor(0.67 * 16) = 10
*/
#define usart_BRR_MANTISSA_MACRO(usartclock, baud) \
	((usartclock) / ((baud) * 16))
#define usart_BRR_FRACTION_MACRO(usartclock, baud) \
	(((usart_BRR_MANTISSA_MACRO((usartclock * 100), baud) - (usart_BRR_MANTISSA_MACRO(usartclock, baud) * 100)) * 16) / 100)
#define usart_BRR_MACRO(usartclock, baud) \
	((usart_BRR_MANTISSA_MACRO(usartclock, baud) << 4) | usart_BRR_FRACTION_MACRO(usartclock, baud))
static const u32 usart_BRR_MANTISSA_MASK  = 0b111111111111;
static const u32 usart_BRR_MANTISSA_SHIFT =              4;
static const u32 usart_BRR_FRACTION_MASK  =         0b1111;
static const u32 usart_BRR_FRACTION_SHIFT =              0;

/* RM0008 27.6.4 */
static const u32 usart_CR1_UE     = (1 << 13);  /* Usart Enable */
static const u32 usart_CR1_M      = (1 << 12);  /* word length, 1=9bit, 0=8bit */
static const u32 usart_CR1_WAKE   = (1 << 11);  /* WAKEup method, 1=address mark, 0=idle line */
static const u32 usart_CR1_PCE    = (1 << 10);  /* Parity Control Enable */
static const u32 usart_CR1_PS     = (1 <<  9);  /* Parity Selection, 1=odd, 0=even */
static const u32 usart_CR1_PEIE   = (1 <<  8);  /* PE Interrupt Enable */
static const u32 usart_CR1_TXEIE  = (1 <<  7);  /* TXE Interrupt Enable */
static const u32 usart_CR1_TCIE   = (1 <<  6);  /* Transmission Complete Interrupt Enable */
static const u32 usart_CR1_RXNEIE = (1 <<  5);  /* RXNE Interrupt Enable */
static const u32 usart_CR1_IDLEIE = (1 <<  4);  /* IDLE Interrupt Enable */
static const u32 usart_CR1_TE     = (1 <<  3);  /* Transmitter Enable */
static const u32 usart_CR1_RE     = (1 <<  2);  /* Receiver Enable */
static const u32 usart_CR1_RWU    = (1 <<  1);  /* Receiver WakeUp */
static const u32 usart_CR1_SBK    = (1 <<  0);  /* Send BreaK */

/* TODO usart_CR2 bits */

/* TODO usart_CR3 bits */

/* TODO usart_GDPR bits */

/* RM0008 table 3 */
static struct usart * const USART1 = (void *)0x40013800;
static struct usart * const USART2 = (void *)0x40004400;
static struct usart * const USART3 = (void *)0x40004800;
static struct usart * const UART4  = (void *)0x40004C00;  /* does not support all features, RM0008 27.5 */
static struct usart * const UART5  = (void *)0x40005000;  /* does not support all features, RM0008 27.5 */

#endif

