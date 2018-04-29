/*
2018 David DiPaola
licensed under CC0 (public domain, see https://creativecommons.org/publicdomain/zero/1.0/)
*/

#ifndef _COMMON_IO_SPI_H
#define _COMMON_IO_SPI_H

/* clock sources:
	SYSCLK --> AHB -- > APB2 (72Mhz max) --> SPI1    (RM0008 figure 1, figure 8, figure 11)
	SYSCLK --> AHB -- > APB1 (36Mhz max) --> SPI2/3  (RM0008 figure 1, figure 8, figure 11)
*/

/* RM0008 25.5.10 */
struct __attribute__ ((__packed__)) spi {
	/* 0x00 */  volatile u32 CR1;      /* spi Control Register 1, RM0008 25.5.1 */ /* TODO confirm */
	/* 0x04 */  volatile u32 CR2;      /* spi Control Register 2, RM0008 25.5.2 */ /* TODO confirm */
	/* 0x08 */  volatile u32 SR;       /* spi Status Register, RM0008 25.5.3 */ /* TODO confirm */
	/* 0x0C */  volatile u32 DR;       /* spi Data Register, RM0008 25.5.4 */ /* TODO confirm */
	/* 0x10 */  volatile u32 CRCPR;    /* spi CRC Polynomial Register, RM0008 25.5.5 */ /* TODO confirm */
	/* 0x14 */  volatile u32 RXCRCR;   /* spi RX CRC Register, RM0008 25.5.6 */ /* TODO confirm */
	/* 0x18 */  volatile u32 TXCRCR;   /* spi TX CRC Register, RM0008 25.5.7 */ /* TODO confirm */
	/* 0x1C */  volatile u32 I2SCFGR;  /* spi/I2S ConFiGuration Register, RM0008 25.5.8 */ /* TODO confirm */
};

/* RM0008 25.5.1 */
static const u32 spi_CR1_BIDIMODE  = (    1 << 15);  /* BIDIrectional data MODe Enable */
static const u32 spi_CR1_BIDIOE    = (    1 << 14);  /* BIDIrectional data mode Output Enable */
static const u32 spi_CR1_CRCEN     = (    1 << 13);  /* Cyclic Redundancy Check calculation ENable */
static const u32 spi_CR1_CRCNEXT   = (    1 << 12);  /* Cyclic Redundancy Check transfer NEXT */
static const u32 spi_CR1_DFF       = (    1 << 11);  /* Data Frame Format, 0=8bit, 1=16bit */
static const u32 spi_CR1_RXONLY    = (    1 << 10);  /* RX ONLY */
static const u32 spi_CR1_SSM       = (    1 <<  9);  /* Software Slave Management */
static const u32 spi_CR1_SSI       = (    1 <<  8);  /* Slave Select Internal */
static const u32 spi_CR1_LSBFIRST  = (    1 <<  7);  /* Least Significant Bit FIRST */
static const u32 spi_CR1_SPE       = (    1 <<  6);  /* SPi Enable */
static const u32 spi_CR1_BR_MASK   = (0b111 <<  3);
static const u32 spi_CR1_BR_DIV2   = (0b000 <<  3);  /* spi clock = input clock / 2 */
static const u32 spi_CR1_BR_DIV4   = (0b001 <<  3);  /* spi clock = input clock / 4 */
static const u32 spi_CR1_BR_DIV8   = (0b010 <<  3);  /* spi clock = input clock / 8 */
static const u32 spi_CR1_BR_DIV16  = (0b011 <<  3);  /* spi clock = input clock / 16 */
static const u32 spi_CR1_BR_DIV32  = (0b100 <<  3);  /* spi clock = input clock / 32 */
static const u32 spi_CR1_BR_DIV64  = (0b101 <<  3);  /* spi clock = input clock / 64 */
static const u32 spi_CR1_BR_DIV128 = (0b110 <<  3);  /* spi clock = input clock / 128 */
static const u32 spi_CR1_BR_DIV256 = (0b111 <<  3);  /* spi clock = input clock / 256 */
static const u32 spi_CR1_MSTR      = (    1 <<  2);  /* MaSTeR mode */
static const u32 spi_CR1_CPOL      = (    1 <<  1);  /* Clock POLarity */
static const u32 spi_CR1_CPHA      = (    1 <<  0);  /* Clock PHAse */

/* RM0008 25.5.2 */
static const u32 spi_CR2_TXEIE   = (1 << 7);  /* TX buffer Empty Interrupt Enable */
static const u32 spi_CR2_RXNEIE  = (1 << 6);  /* RX buffer Not Empty Interrupt Enable */
static const u32 spi_CR2_ERRIE   = (1 << 5);  /* ERRor Interrupt Enable */
static const u32 spi_CR2_SSOE    = (1 << 2);  /* Slave Select Output Enable */
static const u32 spi_CR2_TXDMAEN = (1 << 1);  /* TX buffer Direct Memory Access ENable */
static const u32 spi_CR2_RXDMAEN = (1 << 0);  /* RX buffer Direct Memory Access ENable */

/* RM0008 25.5.3 */
static const u32 spi_SR_BSY    = (1 << 7);  /* BuSY flag */
static const u32 spi_SR_OVR    = (1 << 6);  /* OVeRrun flag */
static const u32 spi_SR_MODF   = (1 << 5);  /* MODe Fault */
static const u32 spi_SR_CRCERR = (1 << 4);  /* Cyclic Redundancy Check ERRor flag */
static const u32 spi_SR_UDR    = (1 << 3);  /* UnDeRrun flag */
static const u32 spi_SR_TXE    = (1 << 1);  /* TX buffer Empty flag */
static const u32 spi_SR_RXNE   = (1 << 0);  /* RX buffer Not Empty flag */

/* TODO other register bits */

/* RM0008 25.5.8 */
static const u32 spi_I2SCFGR_I2SMOD = (1 << 11);  /* I2S MODe selection */
/* NOTE all other bits in this register are only valid in I2S mode so they will not be defined in spi.h */

/* RM0008 3.3 */
static struct spi * const SPI1 = (void *)0x40013000;
static struct spi * const SPI2 = (void *)0x40003800;
static struct spi * const SPI3 = (void *)0x40003C00;  /* NOTE pins shared with JTAG, RM0008 25.1 */

#endif

