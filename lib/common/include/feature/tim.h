/*
2018 David DiPaola
licensed under CC0 (public domain, see https://creativecommons.org/publicdomain/zero/1.0/)
*/

#ifndef _COMMON_FEATURE_TIM_H
#define _COMMON_FEATURE_TIM_H

/* RM0008 table 1, RM0008 14 */
#if (defined(MCU_LINE_F103) || defined(MCU_LINE_F105) || defined(MCU_LINE_F107))
	#define FEATURE_TIM1 1
#endif

/* RM0008 table 1, RM0008 14 */
#if (defined(MCU_LINE_F103) && (defined(MCU_DENSITY_HIGH) || defined(MCU_DENSITY_XL)))
	#define FEATURE_TIM8 1
#endif

#define FEATURE_TIM2 1

#define FEATURE_TIM3 1

#define FEATURE_TIM4 1

#define FEATURE_TIM5 1

/* RM0008 table 1, RM0008 16 */
#if (defined(MCU_DENSITY_XL))
	#define FEATURE_TIM9 1

	#define FEATURE_TIM10 1

	#define FEATURE_TIM11 1

	#define FEATURE_TIM12 1

	#define FEATURE_TIM13 1

	#define FEATURE_TIM14 1
#endif

/* RM0008 table 1, RM0008 17 */
#if (  \
    ((defined(MCU_LINE_F101) || defined(MCU_LINE_F103)) && (defined(MCU_DENSITY_HIGH) || defined(MCU_DENSITY_XL)))  \
    || defined(MCU_LINE_F105)  \
    || defined(MCU_LINE_F107)  \
)
	#define FEATURE_TIM6 1

	#define FEATURE_TIM7 1
#endif

#endif

