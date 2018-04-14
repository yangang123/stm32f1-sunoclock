/*
2017 David DiPaola
licensed under CC0 (public domain, see https://creativecommons.org/publicdomain/zero/1.0/)
*/

/* interrupt and event handlers (RM0008 table 63) */
.org 0x00000000
	.word stack_top  /* initial SP value (RM0008 Figure 11) */
.org 0x00000004
	.word isr_reset  /* reset handler */
.org 0x00000008
	.word _trap      /* TODO interrupt/event handler 2 */
.org 0x0000000C
	.word _trap      /* TODO interrupt/event handler 3 */
.org 0x00000010
	.word _trap      /* TODO interrupt/event handler 4 */
.org 0x00000014
	.word _trap      /* TODO interrupt/event handler 5 */
.org 0x00000018
	.word _trap      /* TODO interrupt/event handler 6 */
.org 0x0000001C
	.word _trap      /* TODO interrupt/event handler 7 */
.org 0x00000020
	.word _trap      /* TODO interrupt/event handler 8 */
.org 0x00000024
	.word _trap      /* TODO interrupt/event handler 9 */
.org 0x00000028
	.word _trap      /* TODO interrupt/event handler 10 */
.org 0x0000002C
	.word _trap      /* TODO interrupt/event handler 11 */
.org 0x00000030
	.word _trap      /* TODO interrupt/event handler 12 */
.org 0x00000034
	.word _trap      /* TODO interrupt/event handler 13 */
.org 0x00000038
	.word _trap      /* TODO interrupt/event handler 14 */
.org 0x0000003C
	.word _trap      /* TODO interrupt/event handler 15 */
.org 0x00000040
	.word _trap      /* TODO interrupt/event handler 16 */
.org 0x00000044
	.word _trap      /* TODO interrupt/event handler 17 */
.org 0x00000048
	.word _trap      /* TODO interrupt/event handler 18 */
.org 0x0000004C
	.word isr_rtc    /* RTC interrupt handler */
.org 0x00000050
	.word _trap      /* TODO interrupt/event handler 20 */
.org 0x00000054
	.word _trap      /* TODO interrupt/event handler 21 */
.org 0x00000058
	.word _trap      /* TODO interrupt/event handler 22 */
.org 0x0000005C
	.word _trap      /* TODO interrupt/event handler 23 */
.org 0x00000060
	.word _trap      /* TODO interrupt/event handler 24 */
.org 0x00000064
	.word _trap      /* TODO interrupt/event handler 25 */
.org 0x00000068
	.word _trap      /* TODO interrupt/event handler 26 */
.org 0x0000006C
	.word _trap      /* TODO interrupt/event handler 27 */
.org 0x00000070
	.word _trap      /* TODO interrupt/event handler 28 */
.org 0x00000074
	.word _trap      /* TODO interrupt/event handler 29 */
.org 0x00000078
	.word _trap      /* TODO interrupt/event handler 30 */
.org 0x0000007C
	.word _trap      /* TODO interrupt/event handler 31 */
.org 0x00000080
	.word _trap      /* TODO interrupt/event handler 32 */
.org 0x00000084
	.word _trap      /* TODO interrupt/event handler 33 */
.org 0x00000088
	.word _trap      /* TODO interrupt/event handler 34 */
.org 0x0000008C
	.word _trap      /* TODO interrupt/event handler 35 */
.org 0x00000090
	.word _trap      /* TODO interrupt/event handler 36 */
.org 0x00000094
	.word _trap      /* TODO interrupt/event handler 37 */
.org 0x00000098
	.word _trap      /* TODO interrupt/event handler 38 */
.org 0x0000009C
	.word _trap      /* TODO interrupt/event handler 39 */
.org 0x000000A0
	.word _trap      /* TODO interrupt/event handler 40 */
.org 0x000000A4
	.word _trap      /* TODO interrupt/event handler 41 */
.org 0x000000A8
	.word _trap      /* TODO interrupt/event handler 42 */
.org 0x000000AC
	.word _trap      /* TODO interrupt/event handler 43 */
.org 0x000000B0
	.word _trap      /* TODO interrupt/event handler 44 */
.org 0x000000B4
	.word _trap      /* TODO interrupt/event handler 45 */
.org 0x000000B8
	.word _trap      /* TODO interrupt/event handler 46 */
.org 0x000000BC
	.word _trap      /* TODO interrupt/event handler 47 */
.org 0x000000C0
	.word _trap      /* TODO interrupt/event handler 48 */
.org 0x000000C4
	.word _trap      /* TODO interrupt/event handler 49 */
.org 0x000000C8
	.word _trap      /* TODO interrupt/event handler 50 */
.org 0x000000CC
	.word _trap      /* TODO interrupt/event handler 51 */
.org 0x000000D0
	.word _trap      /* TODO interrupt/event handler 52 */
.org 0x000000D4
	.word _trap      /* TODO interrupt/event handler 53 */
.org 0x000000D8
	.word _trap      /* TODO interrupt/event handler 54 */
.org 0x000000DC
	.word _trap      /* TODO interrupt/event handler 55 */
.org 0x000000E0
	.word _trap      /* TODO interrupt/event handler 56 */
.org 0x000000E4
	.word isr_exti_rtcalarm  /* EXTI RTC alarm interrupt handler */
.org 0x000000E8
	.word _trap      /* TODO interrupt/event handler 58 */
.org 0x000000EC
	.word _trap      /* TODO interrupt/event handler 59 */
.org 0x000000F0
	.word _trap      /* TODO interrupt/event handler 60 */
.org 0x000000F4
	.word _trap      /* TODO interrupt/event handler 61 */
.org 0x000000F8
	.word _trap      /* TODO interrupt/event handler 62 */
.org 0x000000FC
	.word _trap      /* TODO interrupt/event handler 63 */
.org 0x00000100
	.word _trap      /* TODO interrupt/event handler 64 */
.org 0x00000104
	.word _trap      /* TODO interrupt/event handler 65 */
.org 0x00000108
	.word _trap      /* TODO interrupt/event handler 66 */
.org 0x0000010C
	.word _trap      /* TODO interrupt/event handler 67 */
.org 0x00000110
	.word _trap      /* TODO interrupt/event handler 68 */
.org 0x00000114
	.word _trap      /* TODO interrupt/event handler 69 */
.org 0x00000118
	.word _trap      /* TODO interrupt/event handler 70 */
.org 0x0000011C
	.word _trap      /* TODO interrupt/event handler 71 */
.org 0x00000120
	.word _trap      /* TODO interrupt/event handler 72 */
.org 0x00000124
	.word _trap      /* TODO interrupt/event handler 73 */
.org 0x00000128
	.word _trap      /* TODO interrupt/event handler 74 */
.org 0x0000012C
	.word _trap      /* TODO interrupt/event handler 75 */

.global isr_reset
.thumb_func
isr_reset:
	bl main
	b .

.weak isr_rtc
.thumb_func
isr_rtc:
	ldr r0, =(0xF0000000 | 0x04C)
	b .

.weak isr_exti_rtcalarm
.thumb_func
isr_exti_rtcalarm:
	ldr r0, =(0xF0000000 | 0x0E4)
	b .

.thumb_func
_trap:
	ldr r0, =(0xF0000000 | 0xFFF)
	b .

