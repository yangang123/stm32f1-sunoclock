/*
2018 David DiPaola
licensed under CC0 (public domain, see https://creativecommons.org/publicdomain/zero/1.0/)
*/

/*
params:
	_TIM_STRUCT_ISADV: if defined: declare advanced control timer registers
	_TIM_STRUCT_ISGP: if defined: declare general purpose timer registers
	_TIM_STRUCT_ISBAS: if defined: declare basic timer registers
*/

struct __attribute__ ((__packed__))
#if (defined(_TIM_STRUCT_ISADV))
tim_adv
#elif (defined(_TIM_STRUCT_ISGP))
tim_gp
#elif (defined(_TIM_STRUCT_ISBAS))
tim_bas
#else
#error "unknown timer type"
#endif
{
	/* 0x00 */  volatile u32 CR1;    /* Control Register 1 aka TIMx_CR1, RM0008 14.4.1 and 17.4.1 */

	/* 0x04 */  volatile u32 CR2;    /* Control Register 2, RM0008 14.4.2, aka TIMx_CR2 */ /* TODO confirm */

	/* 0x08 */  volatile u32         /* Slave Mode Control Register, RM0008 14.4.3, aka TIMx_SMCR */ /* TODO confirm */
#if (defined(_TIM_STRUCT_ISADV) || defined(_TIM_STRUCT_ISGP))  /* RM0008 14.4.21 and 15.4.9 */
	SMCR;
#else  /* RM0008 17.4.9 */
	__SMCR;
#endif

	/* 0x0C */  volatile u32 DIER;   /* Dma and Interrupt Enable Register, RM0008 14.4.4, aka TIMx_DIER */ /* TODO confirm */

	/* 0x10 */  volatile u32 SR;     /* Status Register, RM0008 14.4.5, aka TIMx_SR */ /* TODO confirm */

	/* 0x14 */  volatile u32 EGR;    /* Event Generation Register, RM0008 14.4.6, aka TIMx_EGR */

	/* 0x18 */  volatile u32         /* Capture/Compare Mode Register 1, RM0008 14.4.7, aka TIMx_CCMR1 */
#if (defined(_TIM_STRUCT_ISADV) || defined(_TIM_STRUCT_ISGP))  /* RM0008 14.4.21 and 15.4.9 */
	CCMR1;
#else  /* RM0008 17.4.9 */
	__CCMR1;
#endif

	/* 0x1C */  volatile u32         /* Capture/Compare Mode Register 2, RM0008 14.4.8, aka TIMx_CCMR2 */
#if (defined(_TIM_STRUCT_ISADV) || defined(_TIM_STRUCT_ISGP))  /* RM0008 14.4.21 and 15.4.9 */
	CCMR2;
#else  /* RM0008 17.4.9 */
	__CCMR2;
#endif

	/* 0x20 */  volatile u32         /* Capture/Compare Enable Register, RM0008 14.4.9, aka TIMx_CCER */
#if (defined(_TIM_STRUCT_ISADV) || defined(_TIM_STRUCT_ISGP))  /* RM0008 14.4.21 and 15.4.9 */
	CCER;
#else  /* RM0008 17.4.9 */
	__CCER;
#endif

	/* 0x24 */  volatile u32 CNT;    /* CouNTer aka TIMx_CNT, RM0008 14.4.10 */

	/* 0x28 */  volatile u32 PSC;    /* PreSCaler aka TIMx_PSC, RM0008 14.4.11 */

	/* 0x2C */  volatile u32 ARR;    /* Auto-Reload Register aka TIMx_ARR, RM0008 14.4.12 */

#if (defined(_TIM_STRUCT_ISADV) || defined(_TIM_STRUCT_ISGP))  /* RM0008 17.4.9 */

	/* 0x30 */  volatile u32         /* Repetition Counter Register aka TIMx_RCR, RM0008 14.4.13 */ /* TODO confirm */
#if (defined(_TIM_STRUCT_ISADV))  /* RM0008 14.4.21 */
	RCR;
#else  /* RM0008 15.4.19 and 17.4.9 */
	__RCR;
#endif

	/* 0x34 */  volatile u32 CCR1;   /* Capture/Compare Register 1 aka TIMx_CCR1, RM0008 14.4.14 */ /* TODO confirm */

	/* 0x38 */  volatile u32 CCR2;   /* Capture/Compare Register 2 aka TIMx_CCR2, RM0008 14.4.15 */ /* TODO confirm */

	/* 0x3C */  volatile u32 CCR3;   /* Capture/Compare Register 3 aka TIMx_CCR3, RM0008 14.4.16 */ /* TODO confirm */

	/* 0x40 */  volatile u32 CCR4;   /* Capture/Compare Register 4 aka TIMx_CCR4, RM0008 14.4.17 */ /* TODO confirm */

	/* 0x44 */  volatile u32         /* Break and Dead Time Register aka TIMx_BDTR, RM0008 14.4.18 */
#if (defined(_TIM_STRUCT_ISADV))  /* RM0008 14.4.21 */
	BDTR;
#else  /* RM0008 15.4.19 and 17.4.9 */
	__BDTR;
#endif

	/* 0x48 */  volatile u32 DCR;    /* Dma Control Register, RM0008 14.4.19 */

	/* 0x4C */  volatile u32 DMAR;   /* DMa Address for full transfeR, RM0008 14.4.20 */

#endif

};

