# stm32f1-common
minimal support code for ST Microelectronics' F1-series microcontrollers

[GitHub](https://github.com/DavidDiPaola/stm32f1-common)

## dependencies
  - make
  - ARM gcc
  - ARM binutils
  - ARM gdb
      - if using `gdb-multiarch`, see `GDB` config override example
  - OpenOCD

## how to use
  1. create project directory
    - example: `project/`
  2. `git clone` or `git submodule add` into a subdirectory of project directory
    - example: `project/stm32f1-common/`
  3. write project code
    - example: `project/foo.c`
  4. write Makefile:
    - example: `project/Makefile`

how to write project Makefile:
  1. define `SRC_C`
  2. define `COMMON_MCU_LINE`. values are:
    - `F101`
    - `F102`
    - `F103`
    - `F105`
    - `F107`
  3. define `COMMON_MCU_DENSITY`. values are:
    - `LOW` (32KB or less flash)
    - `MEDIUM` (64KB to 128KB flash)
    - `HIGH` (256KB to 512KB flash)
    - `XL` (more than 512KB flash)
  4. define `COMMON_DIR`
  5. include stm32f1-common Makefile

example:

```
SRC_C = foo.c

# for STM32F103C8
COMMON_MCU_LINE = F103
COMMON_MCU_DENSITY = MEDIUM
COMMON_DIR = stm32f1-common
include $(COMMON_DIR)/Makefile
```

## build targets
  - `flash` -- flashes the program to the chip
  - `run-debug-server` -- starts the debugging server
  - `run-debug-client` -- starts `gdb` and attaches it to the debugging server
  - `all` -- builds the program binary
  - `dump` -- shows assembler code in the program binary

## build config
  - `PREFIX` -- prefix for ARM tools
    - default: `arm-none-eabi-`
    - override example: `make PREFIX="arm-linux-gnueabi-" all`
  - `GDB` -- ARM debugger
    - default: `$(PREFIX)gdb`
    - override example: `make GDB="gdb-multiarch" run-debug-client`
  - check Makefile for more (look for `?=`)

## supported MCU models
  - all -- _incomplete_ support: TIM1/8, TIM2/3/4/5, TIM9/10/11/12/13/14, TIM6/7
  - STM32F103C8T6 -- _incomplete_ support: EXTI, GPIOA, GPIOC, PWR, RCC, RTC, TIM1, TIM2/3/4/5

