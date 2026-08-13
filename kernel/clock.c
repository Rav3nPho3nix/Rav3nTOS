#include "clock.h"
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

// Start the next quantum cycle
// Usefull because tasks can pass to the scheduler without waiting to the quantum cycle (with task_sleep, task_yield or task_remove)
void clock_start_quantum() {
    arch_timer_start_quantum();
}