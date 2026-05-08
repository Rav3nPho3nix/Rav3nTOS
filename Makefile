help:
	@echo "Usage: docker compose run --rm [build|clean|enter]"
	@echo "This Makefile need to be run inside a Docker container."

ifndef DOCKER_ENV
%:
	@$(MAKE) help
	@exit 1
else


### TO CHANGE DEPENDING ON TARGET PLATFORM ###
# Architecture directory
ARCH_DIR = arch/arm/cortex-m7

# Board support package directory
BSP_DIR = bsp/renode_stm32h743

# Cross compiler
CC = arm-none-eabi-gcc

# Linker
LD = arm-none-eabi-gcc

# Added flags depending on target architecture
ADD_CFLAGS = -mcpu=cortex-m7 -mthumb
###

# Defaults flags
CFLAGS = -O0 -g -ffreestanding -nostdlib $(ADD_CFLAGS)
LDFLAGS = -nostdlib -T $(BSP_DIR)/linker.ld

TARGET = rav3ntos
BUILD_DIR = build

# Default target
.DEFAULT_GOAL := compilation

# Sources files
SRCS = \
	kernel/main.c \
	$(ARCH_DIR)/vectors.c \
	$(ARCH_DIR)/startup.s


# Objects files
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)
OBJS := $(OBJS:%.s=$(BUILD_DIR)/%.o)

# Compilation
compilation: $(BUILD_DIR)/$(TARGET).elf
	@echo "> Build OK"

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.s | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $@
	@echo "> Link OK"

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/kernel
	mkdir -p $(BUILD_DIR)/$(ARCH_DIR)

# Clean build dir
clean:
	rm -rf $(BUILD_DIR)
	@echo "> Clean OK"

endif