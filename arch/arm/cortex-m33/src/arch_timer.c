#include "arch_timer.h"
#include "systick.h"

// #include "bsp.h"
#include "arch.h"

uint32_t arch_timer_init(uint32_t ticks) {
    return systick_init(ticks);
}

uint32_t arch_timer_get_tick() {
    return systick_get_tick();
}

void arch_timer_delay(uint32_t n) {
    systick_delay(n);
}