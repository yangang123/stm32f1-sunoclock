/*
2017 David DiPaola
licensed under CC0 (public domain, see https://creativecommons.org/publicdomain/zero/1.0/)
*/

#ifndef _COMMON_CORTEXM_H
#define _COMMON_CORTEXM_H

#define cortexm_barrier_datasync() __asm("dsb")

#define cortexm_interrupt_disable() __asm("cpsid f")
#define cortexm_interrupt_enable()  __asm("cpsie f")
#define cortexm_interrupt_wait()    __asm("wfi")

#define cortexm_noop() __asm("nop")

#endif

