#include "clock.h"
#include "arch_timer.h"

uint32_t clock_init(uint32_t ticks) {
    return arch_timer_init(ticks);
}

uint32_t clock_get_tick() {
    return arch_timer_get_tick();
}

void clock_wait(uint32_t n) {
    arch_timer_delay(n);
}