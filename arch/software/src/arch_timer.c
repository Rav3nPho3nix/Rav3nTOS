// Clock implementation using time.h and signal.h

#include "arch_timer.h"

#include <time.h>
#include <signal.h>
#include <string.h>
#include <stdatomic.h>
#include <unistd.h>
#include <stdbool.h>

#define TIMER_SIGNAL SIGUSR1

static _Atomic uint32_t tick_count = 0;
static timer_t timer;
static bool initialized = false;

// Signal handler
void signal_handler(int signal) {
    if (signal == TIMER_SIGNAL) {
        // Increment tick counter
        atomic_fetch_add_explicit(&tick_count, 1, memory_order_relaxed);
    }
}

// Initialize timer
uint32_t arch_timer_init(uint32_t ticks) {
    // If the clock is already initialized
    if (initialized) {
        return 1;
    }

    // Initialisation of signal handler
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = signal_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    if (sigaction(TIMER_SIGNAL, &action, NULL) == -1) {
        return 1;
    }

    struct sigevent event;
    memset(&event, 0, sizeof(event));
    event.sigev_notify = SIGEV_SIGNAL;
    event.sigev_signo = TIMER_SIGNAL;
    event.sigev_value.sival_ptr = &timer;

    // Create the timer
    if (timer_create(CLOCK_MONOTONIC, &event, &timer) == -1) {
        return 1;
    }

    // Set the time
    struct itimerspec timer_spec;
    timer_spec.it_value.tv_sec = ticks / 1000000000UL;
    timer_spec.it_value.tv_nsec = ticks % 1000000000UL;
    timer_spec.it_interval = timer_spec.it_value;

    // Start the timer
    if (timer_settime(timer, 0, &timer_spec, NULL) == -1) {
        return 1;
    }

    atomic_store_explicit(&tick_count, 0, memory_order_relaxed);
    initialized = true;

    return 0;
}

// Get current tick
uint32_t arch_timer_get_tick() {
    return atomic_load_explicit(&tick_count, memory_order_relaxed);
}

// Delay function
void arch_timer_delay(uint32_t n) {
    uint32_t start = arch_timer_get_tick();
    while (arch_timer_get_tick() - start < n) {
        // Pausing CPU
        pause();
    }
}