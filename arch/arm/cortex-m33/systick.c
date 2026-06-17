#include "systick.h"

static volatile uint32_t systick_ticks = 0;

// Define SysTick_Handler
// Increment systick_ticks
void SysTick_Handler() {
    systick_ticks++;
}

// Just call SysTick_Config and return its value
uint32_t systick_init(uint32_t ticks) {
    return SysTick_Config(ticks);
}

// Return current tick
uint32_t systick_get_tick() {
    return systick_ticks;
}

// Wait n ms
void systick_delay(uint32_t n) {
    uint32_t start = systick_ticks;
    while (systick_ticks - start < n) {
        // Only wait
        __WFI();
    }
}