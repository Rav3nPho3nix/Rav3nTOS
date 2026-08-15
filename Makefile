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

###### TO CHANGE DEPENDING ON TARGET PLATFORM ######
# Output file extension
EXTENSION = out
# Output file
OUTPUT = $(TARGET).$(EXTENSION)

# Architecture directory
ARCH_DIR = arch/software
ARCH_INCLUDE_DIR = $(ARCH_DIR)/include
ARCH_SRC_DIR = $(ARCH_DIR)/src

# Board support package directory
BSP_DIR = bsp/software
BSP_INCLUDE_DIR = $(BSP_DIR)/include
BSP_SRC_DIR = $(BSP_DIR)/src

# Compiler
CC = gcc

# Linker
LD = gcc

# Added flags depending on target architecture
# ADD_CFLAGS = -g -ffreestanding -nostdlib -mcpu=cortex-m33 -mthumb
# ADD_LDFLAGS = -nostdlib -T $(BSP_SRC_DIR)/linker.ld
ADD_CFLAGS =
ADD_LDFLAGS =
# ADD_CFLAGS = -fsanitize=address -fno-omit-frame-pointer -g
# ADD_LDFLAGS = -fsanitize=address

# Default flags
CFLAGS = -O0 $(ADD_CFLAGS) $(INCLUDES)
LDFLAGS = $(ADD_LDFLAGS)
######

# Sources files
SRCS = \
	kernel/main.c \
	kernel/clock.c \
	kernel/task.c \
	kernel/scheduler.c \
	kernel/printf.c \
	kernel/semaphore.c \
	\
	$(ARCH_SRC_DIR)/arch_timer.c \
	$(ARCH_SRC_DIR)/context.c \
	$(ARCH_SRC_DIR)/critical.c \
	\
	$(BSP_SRC_DIR)/putchar.c \
	\
	services/log/log.c

# Includes
INCLUDES = \
	-Iincludes \
	-I$(BSP_INCLUDE_DIR) \
	-I$(ARCH_INCLUDE_DIR) \
	-Ikernel

# Default target
.DEFAULT_GOAL := compilation

# Objects files
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)
OBJS := $(OBJS:%.s=$(BUILD_DIR)/%.o)

# Compilation
compilation: $(BUILD_DIR)/$(OUTPUT)
	@echo "> Build OK"

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(OUTPUT): $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $@
	@echo "> Link OK"

# Clean build dir
clean:
	rm -rf $(BUILD_DIR)
	@echo "> Clean OK"

endif