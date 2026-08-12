#include "clock.h"
#include "clock_internal.h"
#include "arch_timer.h"

void clock_init(uint32_t ticks) {
    arch_timer_init(ticks);
}

uint32_t clock_get_tick() {
    return arch_timer_get_tick();
}

void clock_wait(uint32_t n) {
    arch_timer_delay(n);
}

// Consume the preemption flag
bool clock_consume_preemption_flag() {
    return arch_timer_consume_preemption_flag();
}