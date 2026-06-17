help:
	@echo "Usage: docker compose run --rm [build|clean|enter]"
	@echo "This Makefile need to be run inside a Docker container."

ifndef DOCKER_ENV
%:
	@$(MAKE) help
	@exit 1
else

# Build
TARGET = rav3ntos
BUILD_DIR = build
ELF = $(TARGET).elf

###### TO CHANGE DEPENDING ON TARGET PLATFORM ######
# Architecture directory
ARCH_DIR = arch/arm/cortex-m33

# Board support package directory
BSP_DIR = bsp/stm32h533

# Cross compiler
CC = arm-none-eabi-gcc

# Linker
LD = arm-none-eabi-gcc

# Added flags depending on target architecture
ADD_CFLAGS = -mcpu=cortex-m33 -mthumb
######

# Sources files
SRCS = \
	kernel/main.c \
	kernel/clock.c \
\
	$(ARCH_DIR)/startup.s \
	$(ARCH_DIR)/systick.c \
	$(ARCH_DIR)/arch_timer.c \
\
	$(BSP_DIR)/platform.c \
	$(BSP_DIR)/usart.c \
\
	services/debug/debug.c \
	services/log/log.c

# Includes
INCLUDES = \
	-Iincludes \
	-Iincludes/cmsis/core \
	-Iincludes/cmsis/device \
	-I$(BSP_DIR) \
	-I$(ARCH_DIR) \
	-Idrivers/usart \
	-Ikernel

# Defaults flags
CFLAGS = -O0 -g -ffreestanding -nostdlib $(ADD_CFLAGS) $(INCLUDES)
LDFLAGS = -nostdlib -T $(BSP_DIR)/linker.ld

# Default target
.DEFAULT_GOAL := compilation

# Objects files
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)
OBJS := $(OBJS:%.s=$(BUILD_DIR)/%.o)

# Compilation
compilation: $(BUILD_DIR)/$(ELF)
	@echo "> Build OK"

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(ELF): $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $@
	@echo "> Link OK"

# Clean build dir
clean:
	rm -rf $(BUILD_DIR)
	@echo "> Clean OK"

endif