# 2017 David DiPaola
# licensed under CC0 (public domain, see https://creativecommons.org/publicdomain/zero/1.0/)

COMMON_MCU_LINE ?= 
COMMON_MCU_DENSITY ?= 
COMMON_DIR ?= .
COMMON_SRC_S   ?= $(COMMON_DIR)/start.s
COMMON_SRC_C   ?=
COMMON_SRC_LDS ?= $(COMMON_DIR)/layout.lds

PREFIX ?= arm-none-eabi-

OPENOCD_INTERFACE ?= interface/ftdi/dp_busblaster.cfg
OPENOCD_TARGET    ?= target/stm32f1x.cfg

OBJ = $(COMMON_SRC_S:.s=.o) $(COMMON_SRC_C:.s=.o) $(SRC_S:.s=.o) $(SRC_C:.c=.o)
BIN = rom.elf

GCC ?= $(PREFIX)gcc
GCC_FLAGS = \
	-std=c99 -fwrapv \
	-mcpu=cortex-m3 -mthumb -mthumb-interwork \
	-ffreestanding -nostdinc -include $(COMMON_DIR)/include/common.h -I $(COMMON_DIR)/include/ \
	-ffunction-sections -fdata-sections \
	-Os \
	-g \
	-DMCU_LINE_$(COMMON_MCU_LINE) -DMCU_DENSITY_$(COMMON_MCU_DENSITY) \
	$(CPP_FLAGS_DEBUG)

GLD ?= $(PREFIX)ld
GLD_FLAGS = \
	-static -nostdlib \
	-O1 --gc-sections \
	$(GLD_FLAGS_DEBUG)

GDB ?= $(PREFIX)gdb
GDB_FLAGS = \
	-tui \
	-quiet

OBJDUMP ?= $(PREFIX)objdump
SIZE ?= $(PREFIX)size
STRIP ?= $(PREFIX)strip

OPENOCD ?= openocd
OPENOCD_FLAGS ?= \
	--file $(OPENOCD_INTERFACE) \
	--file $(OPENOCD_TARGET)

.PHONY: all
all: $(BIN)

.PHONY: debug
debug:
	@$(MAKE) CPP_FLAGS_DEBUG="-D DEBUG" GLD_FLAGS_DEBUG="--print-map --print-gc-sections --print-memory-usage"

.PHONY: dump
dump: $(BIN)
	@$(OBJDUMP) --disassemble $^
	@echo [OBJDUMP] $^

.PHONY: size
size: $(BIN)
	@$(SIZE) --format=SysV $^
	@echo [SIZE] $^

.PHONY: flash
flash: $(BIN)
	@$(OPENOCD) $(OPENOCD_FLAGS) --command "program $< verify reset exit"
	@echo [FLASH] $<

.PHONY: run-debug-server
run-debug-server:
	@$(OPENOCD) $(OPENOCD_FLAGS)
	@echo [DEBUG-SERVER]

.PHONY: run-debug-client
run-debug-client: $(COMMON_DIR)/gdbinit $(BIN)
	@$(GDB) $(GDB_FLAGS) -x $(COMMON_DIR)/gdbinit $(BIN)
	@echo [DEBUG-CLIENT] $(BIN)

.PHONY: clean
clean:
	@rm -rf $(OBJ) $(BIN)
	@echo [RM] $(OBJ) $(BIN)

.s.o:
	@$(GCC) $(GCC_FLAGS) -o $@ -c $<
	@echo [CC] $<

.c.o:
	@$(GCC) $(GCC_FLAGS) -o $@ -c $<
	@echo [CC] $<

$(BIN): $(COMMON_SRC_LDS) $(OBJ)
	@$(GLD) $(GLD_FLAGS) -T $(COMMON_SRC_LDS) -o $@ $(OBJ)
	@echo [LD] -o $@ $(OBJ)

