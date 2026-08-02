#ifndef ARCH_TMER_H
#define ARCH_TMER_H

#include <stdint.h>
#include "arch.h"

#define TIMER_SIGNAL SIGUSR1

// Initialize timer
void arch_timer_init(uint32_t ticks);

// Get current tick
uint32_t arch_timer_get_tick();

// Delay function
void arch_timer_delay(uint32_t n);

#endif