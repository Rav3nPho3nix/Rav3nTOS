#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>
#include "arch.h"

// Initialize systick (only call SysTick_Config from CMSIS header file)
uint32_t systick_init(uint32_t ticks);

// Get current tick
uint32_t systick_get_tick();

// Delay function
void systick_delay(uint32_t n);

#endif