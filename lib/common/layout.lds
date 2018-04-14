/*
2017 David DiPaola
licensed under CC0 (public domain, see https://creativecommons.org/publicdomain/zero/1.0/)
*/

/* code entry point */
ENTRY(isr_reset)

/* memory regions */
MEMORY {
	FLASH : ORIGIN = 0x08000000, LENGTH = 65536  /* RM0008 table 5 */
	RAM   : ORIGIN = 0x20000000, LENGTH = 20480  /* RM0008 3.3.1 */
}

stack_top = ORIGIN(RAM) + LENGTH(RAM);  /* Cortex-M decrements SP before writing */

/* ELF binary sections */
SECTIONS {
	/* NOTE `SUBALIGN` is used with the `gcc` flags `-ffunction-sections` and `-fdata-sections` to ensure each function and piece of data are properly aligned */

	/* initialized data */
	.data ORIGIN(RAM) + 0 : SUBALIGN(4) {
		*(.data)
	} >RAM

	/* uninitialized data */
	.bss ORIGIN(RAM) + SIZEOF(.data) : SUBALIGN(4) {
		*(.bss)
	} >RAM

	/* code and read-only data */
	.text ORIGIN(FLASH) + 0 : SUBALIGN(2) {
		*/start.o(.text)
		*(.text)
		*(.rodata)
	} >FLASH
}

