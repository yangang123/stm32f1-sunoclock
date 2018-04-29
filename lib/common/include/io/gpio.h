/*
2017 David DiPaola
licensed under CC0 (public domain, see https://creativecommons.org/publicdomain/zero/1.0/)
*/

#ifndef _COMMON_IO_GPIO_H
#define _COMMON_IO_GPIO_H

/* clock source: SYSCLK --> AHB -- > APB2 (72Mhz max) --> GPIO */ /* RM0008 figure 8, figure 11 */

/* RM0008 9.5 */
struct __attribute__ ((__packed__)) gpio {
	/* 0x00 */  volatile u32 CRL;   /* port Configuration Register Low, RM0008 9.2.1 */ /* TODO confirm */
	/* 0x04 */  volatile u32 CRH;   /* port Configuration Register High, RM0008 9.2.2 */
	/* 0x08 */  volatile u32 IDR;   /* port Input Data Register, RM0008 9.2.3 */ /* TODO confirm */
	/* 0x0C */  volatile u32 ODR;   /* port Output Data Register, RM0008 9.2.4 */
	/* 0x10 */  volatile u32 BSRR;  /* port Bit Set/Reset Register, RM0008 9.2.5 */ /* TODO confirm */
	/* 0x14 */  volatile u32 BRR;   /* port Bit Reset Register, RM0008 9.2.6 */ /* TODO confirm */
	/* 0x18 */  volatile u32 LCKR;  /* port configuration LoCK Register, RM0008 9.2.7 */ /* TODO confirm */
};

/* RM0008 9.2.1 */
/* pin 7 */
static const u32 gpio_CRL_CNF7_MASK     = (0b11 << 30);
static const u32 gpio_CRL_CNF7_IN_ANLG  = (0b00 << 30);  /* port CoNFiguration pin 7, INput mode, ANaLoG */
static const u32 gpio_CRL_CNF7_IN_FLT   = (0b01 << 30);  /* port CoNFiguration pin 7, INput mode, FLoaTing */
static const u32 gpio_CRL_CNF7_IN_PUPD  = (0b10 << 30);  /* port CoNFiguration pin 7, INput mode, Pull-Up/Pull-Down */
static const u32 gpio_CRL_CNF7_OUT_GPPP = (0b00 << 30);  /* port CoNFiguration pin 7, OUTput mode, General-Purpose output Push-Pull */
static const u32 gpio_CRL_CNF7_OUT_GPOD = (0b01 << 30);  /* port CoNFiguration pin 7, OUTput mode, General-Purpose output Open Drain */
static const u32 gpio_CRL_CNF7_OUT_AFPP = (0b10 << 30);  /* port CoNFiguration pin 7, OUTput mode, Alternate Function output Push-Pull */
static const u32 gpio_CRL_CNF7_OUT_AFOD = (0b11 << 30);  /* port CoNFiguration pin 7, OUTput mode, Alternate Function output Open Drain */
static const u32 gpio_CRL_MODE7_MASK      = (0b11 << 28);
static const u32 gpio_CRL_MODE7_IN        = (0b00 << 28);  /* port MODE pin 7, INput mode */
static const u32 gpio_CRL_MODE7_OUT_10MHZ = (0b01 << 28);  /* port MODE pin 7, OUTput mode, 10MHZ */
static const u32 gpio_CRL_MODE7_OUT_2MHZ  = (0b10 << 28);  /* port MODE pin 7, OUTput mode, 2MHZ */
static const u32 gpio_CRL_MODE7_OUT_50MHZ = (0b11 << 28);  /* port MODE pin 7, OUTput mode, 50MHZ */
/* pin 6 */
static const u32 gpio_CRL_CNF6_MASK     = (0b11 << 26);
static const u32 gpio_CRL_CNF6_IN_ANLG  = (0b00 << 26);  /* port CoNFiguration pin 6, INput mode, ANaLoG */
static const u32 gpio_CRL_CNF6_IN_FLT   = (0b01 << 26);  /* port CoNFiguration pin 6, INput mode, FLoaTing */
static const u32 gpio_CRL_CNF6_IN_PUPD  = (0b10 << 26);  /* port CoNFiguration pin 6, INput mode, Pull-Up/Pull-Down */
static const u32 gpio_CRL_CNF6_OUT_GPPP = (0b00 << 26);  /* port CoNFiguration pin 6, OUTput mode, General-Purpose output Push-Pull */
static const u32 gpio_CRL_CNF6_OUT_GPOD = (0b01 << 26);  /* port CoNFiguration pin 6, OUTput mode, General-Purpose output Open Drain */
static const u32 gpio_CRL_CNF6_OUT_AFPP = (0b10 << 26);  /* port CoNFiguration pin 6, OUTput mode, Alternate Function output Push-Pull */
static const u32 gpio_CRL_CNF6_OUT_AFOD = (0b11 << 26);  /* port CoNFiguration pin 6, OUTput mode, Alternate Function output Open Drain */
static const u32 gpio_CRL_MODE6_MASK      = (0b11 << 24);
static const u32 gpio_CRL_MODE6_IN        = (0b00 << 24);  /* port MODE pin 6, INput mode */
static const u32 gpio_CRL_MODE6_OUT_10MHZ = (0b01 << 24);  /* port MODE pin 6, OUTput mode, 10MHZ */
static const u32 gpio_CRL_MODE6_OUT_2MHZ  = (0b10 << 24);  /* port MODE pin 6, OUTput mode, 2MHZ */
static const u32 gpio_CRL_MODE6_OUT_50MHZ = (0b11 << 24);  /* port MODE pin 6, OUTput mode, 50MHZ */
/* pin 5 */
static const u32 gpio_CRL_CNF5_MASK     = (0b11 << 22);
static const u32 gpio_CRL_CNF5_IN_ANLG  = (0b00 << 22);  /* port CoNFiguration pin 5, INput mode, ANaLoG */
static const u32 gpio_CRL_CNF5_IN_FLT   = (0b01 << 22);  /* port CoNFiguration pin 5, INput mode, FLoaTing */
static const u32 gpio_CRL_CNF5_IN_PUPD  = (0b10 << 22);  /* port CoNFiguration pin 5, INput mode, Pull-Up/Pull-Down */
static const u32 gpio_CRL_CNF5_OUT_GPPP = (0b00 << 22);  /* port CoNFiguration pin 5, OUTput mode, General-Purpose output Push-Pull */
static const u32 gpio_CRL_CNF5_OUT_GPOD = (0b01 << 22);  /* port CoNFiguration pin 5, OUTput mode, General-Purpose output Open Drain */
static const u32 gpio_CRL_CNF5_OUT_AFPP = (0b10 << 22);  /* port CoNFiguration pin 5, OUTput mode, Alternate Function output Push-Pull */
static const u32 gpio_CRL_CNF5_OUT_AFOD = (0b11 << 22);  /* port CoNFiguration pin 5, OUTput mode, Alternate Function output Open Drain */
static const u32 gpio_CRL_MODE5_MASK      = (0b11 << 20);
static const u32 gpio_CRL_MODE5_IN        = (0b00 << 20);  /* port MODE pin 5, INput mode */
static const u32 gpio_CRL_MODE5_OUT_10MHZ = (0b01 << 20);  /* port MODE pin 5, OUTput mode, 10MHZ */
static const u32 gpio_CRL_MODE5_OUT_2MHZ  = (0b10 << 20);  /* port MODE pin 5, OUTput mode, 2MHZ */
static const u32 gpio_CRL_MODE5_OUT_50MHZ = (0b11 << 20);  /* port MODE pin 5, OUTput mode, 50MHZ */
/* pin 4 */
static const u32 gpio_CRL_CNF4_MASK     = (0b11 << 18);
static const u32 gpio_CRL_CNF4_IN_ANLG  = (0b00 << 18);  /* port CoNFiguration pin 4, INput mode, ANaLoG */
static const u32 gpio_CRL_CNF4_IN_FLT   = (0b01 << 18);  /* port CoNFiguration pin 4, INput mode, FLoaTing */
static const u32 gpio_CRL_CNF4_IN_PUPD  = (0b10 << 18);  /* port CoNFiguration pin 4, INput mode, Pull-Up/Pull-Down */
static const u32 gpio_CRL_CNF4_OUT_GPPP = (0b00 << 18);  /* port CoNFiguration pin 4, OUTput mode, General-Purpose output Push-Pull */
static const u32 gpio_CRL_CNF4_OUT_GPOD = (0b01 << 18);  /* port CoNFiguration pin 4, OUTput mode, General-Purpose output Open Drain */
static const u32 gpio_CRL_CNF4_OUT_AFPP = (0b10 << 18);  /* port CoNFiguration pin 4, OUTput mode, Alternate Function output Push-Pull */
static const u32 gpio_CRL_CNF4_OUT_AFOD = (0b11 << 18);  /* port CoNFiguration pin 4, OUTput mode, Alternate Function output Open Drain */
static const u32 gpio_CRL_MODE4_MASK      = (0b11 << 16);
static const u32 gpio_CRL_MODE4_IN        = (0b00 << 16);  /* port MODE pin 4, INput mode */
static const u32 gpio_CRL_MODE4_OUT_10MHZ = (0b01 << 16);  /* port MODE pin 4, OUTput mode, 10MHZ */
static const u32 gpio_CRL_MODE4_OUT_2MHZ  = (0b10 << 16);  /* port MODE pin 4, OUTput mode, 2MHZ */
static const u32 gpio_CRL_MODE4_OUT_50MHZ = (0b11 << 16);  /* port MODE pin 4, OUTput mode, 50MHZ */
/* pin 3 */
static const u32 gpio_CRL_CNF3_MASK     = (0b11 << 14);
static const u32 gpio_CRL_CNF3_IN_ANLG  = (0b00 << 14);  /* port CoNFiguration pin 3, INput mode, ANaLoG */
static const u32 gpio_CRL_CNF3_IN_FLT   = (0b01 << 14);  /* port CoNFiguration pin 3, INput mode, FLoaTing */
static const u32 gpio_CRL_CNF3_IN_PUPD  = (0b10 << 14);  /* port CoNFiguration pin 3, INput mode, Pull-Up/Pull-Down */
static const u32 gpio_CRL_CNF3_OUT_GPPP = (0b00 << 14);  /* port CoNFiguration pin 3, OUTput mode, General-Purpose output Push-Pull */
static const u32 gpio_CRL_CNF3_OUT_GPOD = (0b01 << 14);  /* port CoNFiguration pin 3, OUTput mode, General-Purpose output Open Drain */
static const u32 gpio_CRL_CNF3_OUT_AFPP = (0b10 << 14);  /* port CoNFiguration pin 3, OUTput mode, Alternate Function output Push-Pull */
static const u32 gpio_CRL_CNF3_OUT_AFOD = (0b11 << 14);  /* port CoNFiguration pin 3, OUTput mode, Alternate Function output Open Drain */
static const u32 gpio_CRL_MODE3_MASK      = (0b11 << 12);
static const u32 gpio_CRL_MODE3_IN        = (0b00 << 12);  /* port MODE pin 3, INput mode */
static const u32 gpio_CRL_MODE3_OUT_10MHZ = (0b01 << 12);  /* port MODE pin 3, OUTput mode, 10MHZ */
static const u32 gpio_CRL_MODE3_OUT_2MHZ  = (0b10 << 12);  /* port MODE pin 3, OUTput mode, 2MHZ */
static const u32 gpio_CRL_MODE3_OUT_50MHZ = (0b11 << 12);  /* port MODE pin 3, OUTput mode, 50MHZ */
/* pin 2 */
static const u32 gpio_CRL_CNF2_MASK     = (0b11 << 10);
static const u32 gpio_CRL_CNF2_IN_ANLG  = (0b00 << 10);  /* port CoNFiguration pin 2, INput mode, ANaLoG */
static const u32 gpio_CRL_CNF2_IN_FLT   = (0b01 << 10);  /* port CoNFiguration pin 2, INput mode, FLoaTing */
static const u32 gpio_CRL_CNF2_IN_PUPD  = (0b10 << 10);  /* port CoNFiguration pin 2, INput mode, Pull-Up/Pull-Down */
static const u32 gpio_CRL_CNF2_OUT_GPPP = (0b00 << 10);  /* port CoNFiguration pin 2, OUTput mode, General-Purpose output Push-Pull */
static const u32 gpio_CRL_CNF2_OUT_GPOD = (0b01 << 10);  /* port CoNFiguration pin 2, OUTput mode, General-Purpose output Open Drain */
static const u32 gpio_CRL_CNF2_OUT_AFPP = (0b10 << 10);  /* port CoNFiguration pin 2, OUTput mode, Alternate Function output Push-Pull */
static const u32 gpio_CRL_CNF2_OUT_AFOD = (0b11 << 10);  /* port CoNFiguration pin 2, OUTput mode, Alternate Function output Open Drain */
static const u32 gpio_CRL_MODE2_MASK      = (0b11 << 8);
static const u32 gpio_CRL_MODE2_IN        = (0b00 << 8);  /* port MODE pin 2, INput mode */
static const u32 gpio_CRL_MODE2_OUT_10MHZ = (0b01 << 8);  /* port MODE pin 2, OUTput mode, 10MHZ */
static const u32 gpio_CRL_MODE2_OUT_2MHZ  = (0b10 << 8);  /* port MODE pin 2, OUTput mode, 2MHZ */
static const u32 gpio_CRL_MODE2_OUT_50MHZ = (0b11 << 8);  /* port MODE pin 2, OUTput mode, 50MHZ */
/* pin 1 */
static const u32 gpio_CRL_CNF1_MASK     = (0b11 << 6);
static const u32 gpio_CRL_CNF1_IN_ANLG  = (0b00 << 6);  /* port CoNFiguration pin 1, INput mode, ANaLoG */
static const u32 gpio_CRL_CNF1_IN_FLT   = (0b01 << 6);  /* port CoNFiguration pin 1, INput mode, FLoaTing */
static const u32 gpio_CRL_CNF1_IN_PUPD  = (0b10 << 6);  /* port CoNFiguration pin 1, INput mode, Pull-Up/Pull-Down */
static const u32 gpio_CRL_CNF1_OUT_GPPP = (0b00 << 6);  /* port CoNFiguration pin 1, OUTput mode, General-Purpose output Push-Pull */
static const u32 gpio_CRL_CNF1_OUT_GPOD = (0b01 << 6);  /* port CoNFiguration pin 1, OUTput mode, General-Purpose output Open Drain */
static const u32 gpio_CRL_CNF1_OUT_AFPP = (0b10 << 6);  /* port CoNFiguration pin 1, OUTput mode, Alternate Function output Push-Pull */
static const u32 gpio_CRL_CNF1_OUT_AFOD = (0b11 << 6);  /* port CoNFiguration pin 1, OUTput mode, Alternate Function output Open Drain */
static const u32 gpio_CRL_MODE1_MASK      = (0b11 << 4);
static const u32 gpio_CRL_MODE1_IN        = (0b00 << 4);  /* port MODE pin 1, INput mode */
static const u32 gpio_CRL_MODE1_OUT_10MHZ = (0b01 << 4);  /* port MODE pin 1, OUTput mode, 10MHZ */
static const u32 gpio_CRL_MODE1_OUT_2MHZ  = (0b10 << 4);  /* port MODE pin 1, OUTput mode, 2MHZ */
static const u32 gpio_CRL_MODE1_OUT_50MHZ = (0b11 << 4);  /* port MODE pin 1, OUTput mode, 50MHZ */
/* pin 0 */
static const u32 gpio_CRL_CNF0_MASK     = (0b11 << 2);
static const u32 gpio_CRL_CNF0_IN_ANLG  = (0b00 << 2);  /* port CoNFiguration pin 0, INput mode, ANaLoG */
static const u32 gpio_CRL_CNF0_IN_FLT   = (0b01 << 2);  /* port CoNFiguration pin 0, INput mode, FLoaTing */
static const u32 gpio_CRL_CNF0_IN_PUPD  = (0b10 << 2);  /* port CoNFiguration pin 0, INput mode, Pull-Up/Pull-Down */
static const u32 gpio_CRL_CNF0_OUT_GPPP = (0b00 << 2);  /* port CoNFiguration pin 0, OUTput mode, General-Purpose output Push-Pull */
static const u32 gpio_CRL_CNF0_OUT_GPOD = (0b01 << 2);  /* port CoNFiguration pin 0, OUTput mode, General-Purpose output Open Drain */
static const u32 gpio_CRL_CNF0_OUT_AFPP = (0b10 << 2);  /* port CoNFiguration pin 0, OUTput mode, Alternate Function output Push-Pull */
static const u32 gpio_CRL_CNF0_OUT_AFOD = (0b11 << 2);  /* port CoNFiguration pin 0, OUTput mode, Alternate Function output Open Drain */
static const u32 gpio_CRL_MODE0_MASK      = (0b11 << 0);
static const u32 gpio_CRL_MODE0_IN        = (0b00 << 0);  /* port MODE pin 0, INput mode */
static const u32 gpio_CRL_MODE0_OUT_10MHZ = (0b01 << 0);  /* port MODE pin 0, OUTput mode, 10MHZ */
static const u32 gpio_CRL_MODE0_OUT_2MHZ  = (0b10 << 0);  /* port MODE pin 0, OUTput mode, 2MHZ */
static const u32 gpio_CRL_MODE0_OUT_50MHZ = (0b11 << 0);  /* port MODE pin 0, OUTput mode, 50MHZ */

/* RM0008 9.2.2 */
/* pin 15 */
static const u32 gpio_CRH_CNF15_MASK     = (0b11 << 30);
static const u32 gpio_CRH_CNF15_IN_ANLG  = (0b00 << 30);  /* port CoNFiguration pin 15, INput mode, ANaLoG */
static const u32 gpio_CRH_CNF15_IN_FLT   = (0b01 << 30);  /* port CoNFiguration pin 15, INput mode, FLoaTing */
static const u32 gpio_CRH_CNF15_IN_PUPD  = (0b10 << 30);  /* port CoNFiguration pin 15, INput mode, Pull-Up/Pull-Down */
static const u32 gpio_CRH_CNF15_OUT_GPPP = (0b00 << 30);  /* port CoNFiguration pin 15, OUTput mode, General-Purpose output Push-Pull */
static const u32 gpio_CRH_CNF15_OUT_GPOD = (0b01 << 30);  /* port CoNFiguration pin 15, OUTput mode, General-Purpose output Open Drain */
static const u32 gpio_CRH_CNF15_OUT_AFPP = (0b10 << 30);  /* port CoNFiguration pin 15, OUTput mode, Alternate Function output Push-Pull */
static const u32 gpio_CRH_CNF15_OUT_AFOD = (0b11 << 30);  /* port CoNFiguration pin 15, OUTput mode, Alternate Function output Open Drain */
static const u32 gpio_CRH_MODE15_MASK      = (0b11 << 28);
static const u32 gpio_CRH_MODE15_IN        = (0b00 << 28);  /* port MODE pin 15, INput mode */
static const u32 gpio_CRH_MODE15_OUT_10MHZ = (0b01 << 28);  /* port MODE pin 15, OUTput mode, 10MHZ */
static const u32 gpio_CRH_MODE15_OUT_2MHZ  = (0b10 << 28);  /* port MODE pin 15, OUTput mode, 2MHZ */
static const u32 gpio_CRH_MODE15_OUT_50MHZ = (0b11 << 28);  /* port MODE pin 15, OUTput mode, 50MHZ */
/* pin 14 */
static const u32 gpio_CRH_CNF14_MASK     = (0b11 << 26);
static const u32 gpio_CRH_CNF14_IN_ANLG  = (0b00 << 26);  /* port CoNFiguration pin 14, INput mode, ANaLoG */
static const u32 gpio_CRH_CNF14_IN_FLT   = (0b01 << 26);  /* port CoNFiguration pin 14, INput mode, FLoaTing */
static const u32 gpio_CRH_CNF14_IN_PUPD  = (0b10 << 26);  /* port CoNFiguration pin 14, INput mode, Pull-Up/Pull-Down */
static const u32 gpio_CRH_CNF14_OUT_GPPP = (0b00 << 26);  /* port CoNFiguration pin 14, OUTput mode, General-Purpose output Push-Pull */
static const u32 gpio_CRH_CNF14_OUT_GPOD = (0b01 << 26);  /* port CoNFiguration pin 14, OUTput mode, General-Purpose output Open Drain */
static const u32 gpio_CRH_CNF14_OUT_AFPP = (0b10 << 26);  /* port CoNFiguration pin 14, OUTput mode, Alternate Function output Push-Pull */
static const u32 gpio_CRH_CNF14_OUT_AFOD = (0b11 << 26);  /* port CoNFiguration pin 14, OUTput mode, Alternate Function output Open Drain */
static const u32 gpio_CRH_MODE14_MASK      = (0b11 << 24);
static const u32 gpio_CRH_MODE14_IN        = (0b00 << 24);  /* port MODE pin 14, INput mode */
static const u32 gpio_CRH_MODE14_OUT_10MHZ = (0b01 << 24);  /* port MODE pin 14, OUTput mode, 10MHZ */
static const u32 gpio_CRH_MODE14_OUT_2MHZ  = (0b10 << 24);  /* port MODE pin 14, OUTput mode, 2MHZ */
static const u32 gpio_CRH_MODE14_OUT_50MHZ = (0b11 << 24);  /* port MODE pin 14, OUTput mode, 50MHZ */
/* pin 13 */
static const u32 gpio_CRH_CNF13_MASK     = (0b11 << 22);
static const u32 gpio_CRH_CNF13_IN_ANLG  = (0b00 << 22);  /* port CoNFiguration pin 13, INput mode, ANaLoG */
static const u32 gpio_CRH_CNF13_IN_FLT   = (0b01 << 22);  /* port CoNFiguration pin 13, INput mode, FLoaTing */
static const u32 gpio_CRH_CNF13_IN_PUPD  = (0b10 << 22);  /* port CoNFiguration pin 13, INput mode, Pull-Up/Pull-Down */
static const u32 gpio_CRH_CNF13_OUT_GPPP = (0b00 << 22);  /* port CoNFiguration pin 13, OUTput mode, General-Purpose output Push-Pull */
static const u32 gpio_CRH_CNF13_OUT_GPOD = (0b01 << 22);  /* port CoNFiguration pin 13, OUTput mode, General-Purpose output Open Drain */
static const u32 gpio_CRH_CNF13_OUT_AFPP = (0b10 << 22);  /* port CoNFiguration pin 13, OUTput mode, Alternate Function output Push-Pull */
static const u32 gpio_CRH_CNF13_OUT_AFOD = (0b11 << 22);  /* port CoNFiguration pin 13, OUTput mode, Alternate Function output Open Drain */
static const u32 gpio_CRH_MODE13_MASK      = (0b11 << 20);
static const u32 gpio_CRH_MODE13_IN        = (0b00 << 20);  /* port MODE pin 13, INput mode */
static const u32 gpio_CRH_MODE13_OUT_10MHZ = (0b01 << 20);  /* port MODE pin 13, OUTput mode, 10MHZ */
static const u32 gpio_CRH_MODE13_OUT_2MHZ  = (0b10 << 20);  /* port MODE pin 13, OUTput mode, 2MHZ */
static const u32 gpio_CRH_MODE13_OUT_50MHZ = (0b11 << 20);  /* port MODE pin 13, OUTput mode, 50MHZ */
/* pin 12 */
static const u32 gpio_CRH_CNF12_MASK     = (0b11 << 18);
static const u32 gpio_CRH_CNF12_IN_ANLG  = (0b00 << 18);  /* port CoNFiguration pin 12, INput mode, ANaLoG */
static const u32 gpio_CRH_CNF12_IN_FLT   = (0b01 << 18);  /* port CoNFiguration pin 12, INput mode, FLoaTing */
static const u32 gpio_CRH_CNF12_IN_PUPD  = (0b10 << 18);  /* port CoNFiguration pin 12, INput mode, Pull-Up/Pull-Down */
static const u32 gpio_CRH_CNF12_OUT_GPPP = (0b00 << 18);  /* port CoNFiguration pin 12, OUTput mode, General-Purpose output Push-Pull */
static const u32 gpio_CRH_CNF12_OUT_GPOD = (0b01 << 18);  /* port CoNFiguration pin 12, OUTput mode, General-Purpose output Open Drain */
static const u32 gpio_CRH_CNF12_OUT_AFPP = (0b10 << 18);  /* port CoNFiguration pin 12, OUTput mode, Alternate Function output Push-Pull */
static const u32 gpio_CRH_CNF12_OUT_AFOD = (0b11 << 18);  /* port CoNFiguration pin 12, OUTput mode, Alternate Function output Open Drain */
static const u32 gpio_CRH_MODE12_MASK      = (0b11 << 16);
static const u32 gpio_CRH_MODE12_IN        = (0b00 << 16);  /* port MODE pin 12, INput mode */
static const u32 gpio_CRH_MODE12_OUT_10MHZ = (0b01 << 16);  /* port MODE pin 12, OUTput mode, 10MHZ */
static const u32 gpio_CRH_MODE12_OUT_2MHZ  = (0b10 << 16);  /* port MODE pin 12, OUTput mode, 2MHZ */
static const u32 gpio_CRH_MODE12_OUT_50MHZ = (0b11 << 16);  /* port MODE pin 12, OUTput mode, 50MHZ */
/* pin 11 */
static const u32 gpio_CRH_CNF11_MASK     = (0b11 << 14);
static const u32 gpio_CRH_CNF11_IN_ANLG  = (0b00 << 14);  /* port CoNFiguration pin 11, INput mode, ANaLoG */
static const u32 gpio_CRH_CNF11_IN_FLT   = (0b01 << 14);  /* port CoNFiguration pin 11, INput mode, FLoaTing */
static const u32 gpio_CRH_CNF11_IN_PUPD  = (0b10 << 14);  /* port CoNFiguration pin 11, INput mode, Pull-Up/Pull-Down */
static const u32 gpio_CRH_CNF11_OUT_GPPP = (0b00 << 14);  /* port CoNFiguration pin 11, OUTput mode, General-Purpose output Push-Pull */
static const u32 gpio_CRH_CNF11_OUT_GPOD = (0b01 << 14);  /* port CoNFiguration pin 11, OUTput mode, General-Purpose output Open Drain */
static const u32 gpio_CRH_CNF11_OUT_AFPP = (0b10 << 14);  /* port CoNFiguration pin 11, OUTput mode, Alternate Function output Push-Pull */
static const u32 gpio_CRH_CNF11_OUT_AFOD = (0b11 << 14);  /* port CoNFiguration pin 11, OUTput mode, Alternate Function output Open Drain */
static const u32 gpio_CRH_MODE11_MASK      = (0b11 << 12);
static const u32 gpio_CRH_MODE11_IN        = (0b00 << 12);  /* port MODE pin 11, INput mode */
static const u32 gpio_CRH_MODE11_OUT_10MHZ = (0b01 << 12);  /* port MODE pin 11, OUTput mode, 10MHZ */
static const u32 gpio_CRH_MODE11_OUT_2MHZ  = (0b10 << 12);  /* port MODE pin 11, OUTput mode, 2MHZ */
static const u32 gpio_CRH_MODE11_OUT_50MHZ = (0b11 << 12);  /* port MODE pin 11, OUTput mode, 50MHZ */
/* pin 10 */
static const u32 gpio_CRH_CNF10_MASK     = (0b11 << 10);
static const u32 gpio_CRH_CNF10_IN_ANLG  = (0b00 << 10);  /* port CoNFiguration pin 10, INput mode, ANaLoG */
static const u32 gpio_CRH_CNF10_IN_FLT   = (0b01 << 10);  /* port CoNFiguration pin 10, INput mode, FLoaTing */
static const u32 gpio_CRH_CNF10_IN_PUPD  = (0b10 << 10);  /* port CoNFiguration pin 10, INput mode, Pull-Up/Pull-Down */
static const u32 gpio_CRH_CNF10_OUT_GPPP = (0b00 << 10);  /* port CoNFiguration pin 10, OUTput mode, General-Purpose output Push-Pull */
static const u32 gpio_CRH_CNF10_OUT_GPOD = (0b01 << 10);  /* port CoNFiguration pin 10, OUTput mode, General-Purpose output Open Drain */
static const u32 gpio_CRH_CNF10_OUT_AFPP = (0b10 << 10);  /* port CoNFiguration pin 10, OUTput mode, Alternate Function output Push-Pull */
static const u32 gpio_CRH_CNF10_OUT_AFOD = (0b11 << 10);  /* port CoNFiguration pin 10, OUTput mode, Alternate Function output Open Drain */
static const u32 gpio_CRH_MODE10_MASK      = (0b11 << 8);
static const u32 gpio_CRH_MODE10_IN        = (0b00 << 8);  /* port MODE pin 10, INput mode */
static const u32 gpio_CRH_MODE10_OUT_10MHZ = (0b01 << 8);  /* port MODE pin 10, OUTput mode, 10MHZ */
static const u32 gpio_CRH_MODE10_OUT_2MHZ  = (0b10 << 8);  /* port MODE pin 10, OUTput mode, 2MHZ */
static const u32 gpio_CRH_MODE10_OUT_50MHZ = (0b11 << 8);  /* port MODE pin 10, OUTput mode, 50MHZ */
/* pin 9 */
static const u32 gpio_CRH_CNF9_MASK     = (0b11 << 6);
static const u32 gpio_CRH_CNF9_IN_ANLG  = (0b00 << 6);  /* port CoNFiguration pin 9, INput mode, ANaLoG */
static const u32 gpio_CRH_CNF9_IN_FLT   = (0b01 << 6);  /* port CoNFiguration pin 9, INput mode, FLoaTing */
static const u32 gpio_CRH_CNF9_IN_PUPD  = (0b10 << 6);  /* port CoNFiguration pin 9, INput mode, Pull-Up/Pull-Down */
static const u32 gpio_CRH_CNF9_OUT_GPPP = (0b00 << 6);  /* port CoNFiguration pin 9, OUTput mode, General-Purpose output Push-Pull */
static const u32 gpio_CRH_CNF9_OUT_GPOD = (0b01 << 6);  /* port CoNFiguration pin 9, OUTput mode, General-Purpose output Open Drain */
static const u32 gpio_CRH_CNF9_OUT_AFPP = (0b10 << 6);  /* port CoNFiguration pin 9, OUTput mode, Alternate Function output Push-Pull */
static const u32 gpio_CRH_CNF9_OUT_AFOD = (0b11 << 6);  /* port CoNFiguration pin 9, OUTput mode, Alternate Function output Open Drain */
static const u32 gpio_CRH_MODE9_MASK      = (0b11 << 4);
static const u32 gpio_CRH_MODE9_IN        = (0b00 << 4);  /* port MODE pin 9, INput mode */
static const u32 gpio_CRH_MODE9_OUT_10MHZ = (0b01 << 4);  /* port MODE pin 9, OUTput mode, 10MHZ */
static const u32 gpio_CRH_MODE9_OUT_2MHZ  = (0b10 << 4);  /* port MODE pin 9, OUTput mode, 2MHZ */
static const u32 gpio_CRH_MODE9_OUT_50MHZ = (0b11 << 4);  /* port MODE pin 9, OUTput mode, 50MHZ */
/* pin 8 */
static const u32 gpio_CRH_CNF8_MASK     = (0b11 << 2);
static const u32 gpio_CRH_CNF8_IN_ANLG  = (0b00 << 2);  /* port CoNFiguration pin 8, INput mode, ANaLoG */
static const u32 gpio_CRH_CNF8_IN_FLT   = (0b01 << 2);  /* port CoNFiguration pin 8, INput mode, FLoaTing */
static const u32 gpio_CRH_CNF8_IN_PUPD  = (0b10 << 2);  /* port CoNFiguration pin 8, INput mode, Pull-Up/Pull-Down */
static const u32 gpio_CRH_CNF8_OUT_GPPP = (0b00 << 2);  /* port CoNFiguration pin 8, OUTput mode, General-Purpose output Push-Pull */
static const u32 gpio_CRH_CNF8_OUT_GPOD = (0b01 << 2);  /* port CoNFiguration pin 8, OUTput mode, General-Purpose output Open Drain */
static const u32 gpio_CRH_CNF8_OUT_AFPP = (0b10 << 2);  /* port CoNFiguration pin 8, OUTput mode, Alternate Function output Push-Pull */
static const u32 gpio_CRH_CNF8_OUT_AFOD = (0b11 << 2);  /* port CoNFiguration pin 8, OUTput mode, Alternate Function output Open Drain */
static const u32 gpio_CRH_MODE8_MASK      = (0b11 << 0);
static const u32 gpio_CRH_MODE8_IN        = (0b00 << 0);  /* port MODE pin 8, INput mode */
static const u32 gpio_CRH_MODE8_OUT_10MHZ = (0b01 << 0);  /* port MODE pin 8, OUTput mode, 10MHZ */
static const u32 gpio_CRH_MODE8_OUT_2MHZ  = (0b10 << 0);  /* port MODE pin 8, OUTput mode, 2MHZ */
static const u32 gpio_CRH_MODE8_OUT_50MHZ = (0b11 << 0);  /* port MODE pin 8, OUTput mode, 50MHZ */

/* TODO IDR bits */

/* TODO ODR bits */

/* TODO BSRR bits */

/* TODO BRR bits */

/* TODO LCKR bits */

/* RM0008 table 3 */
static struct gpio * const GPIOA = (void *)0x40010800;
static struct gpio * const GPIOB = (void *)0x40010C00;
static struct gpio * const GPIOC = (void *)0x40011000;
static struct gpio * const GPIOD = (void *)0x40011400;
static struct gpio * const GPIOE = (void *)0x40011800;
static struct gpio * const GPIOF = (void *)0x40011C00;
static struct gpio * const GPIOG = (void *)0x40012000;

#endif

