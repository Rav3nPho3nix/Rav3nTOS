#ifndef CLOCK_H
#define CLOCK_H

#include <stdint.h>

// Initialize clock
uint32_t clock_init(uint32_t ticks);

// Get current tick value
uint32_t clock_get_tick();

// Wait n milliseconds
void clock_wait(uint32_t n);

#endif