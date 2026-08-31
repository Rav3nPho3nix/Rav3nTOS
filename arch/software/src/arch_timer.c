// Clock implementation using time.h and signal.h

#include "arch_timer.h"
#include "scheduler.h"
#include "scheduler_internal.h"
#include "critical.h"
#include "context.h"
#include "context_internal.h"
#include "task.h"
#include "config.h"

#include "arch.h"

// Tick counter
static _Atomic uint32_t tick_count = 0;
static timer_t timer;
static bool initialized = false;
// Next quantum tick
static uint32_t next_quantum_tick = 0;

// Signal handler
void signal_handler(int signal, siginfo_t *info, void *raw_context) {
    if (signal != TIMER_SIGNAL) {
        return;
    }

    // Increment tick counter
    atomic_fetch_add_explicit(&tick_count, 1, memory_order_relaxed);

    // If the scheduler is not started
    if (!scheduler_is_started()) {
        return;
    }

    // If quantum is NOT done
    if (tick_count < next_quantum_tick) {
        return;
    }

    // Currently running task
    Task *current_task = scheduler_get_current_task();

    // If there is no running task
    if (!current_task) {
        return;
    }

    // Set as READY the task
    current_task->state = TASK_STATE_READY;

    // Preempt
    context_preempt(current_task, (ucontext_t*) raw_context);
}

// Initialize timer
void arch_timer_init(uint32_t ticks) {
    // If the clock is already initialized
    if (initialized) {
        return;
    }

    // Initialisation of signal handler
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_sigaction = signal_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_SIGINFO;

    if (sigaction(TIMER_SIGNAL, &action, NULL) == -1) {
        return;
    }

    struct sigevent event;
    memset(&event, 0, sizeof(event));
    event.sigev_notify = SIGEV_SIGNAL;
    event.sigev_signo = TIMER_SIGNAL;
    event.sigev_value.sival_ptr = &timer;

    // Create the timer
    if (timer_create(CLOCK_MONOTONIC, &event, &timer) == -1) {
        return;
    }

    // Set the time
    struct itimerspec timer_spec;
    timer_spec.it_value.tv_sec = ticks / 1000000000UL;
    timer_spec.it_value.tv_nsec = ticks % 1000000000UL;
    timer_spec.it_interval = timer_spec.it_value;

    // Start the timer
    if (timer_settime(timer, 0, &timer_spec, NULL) == -1) {
        return;
    }

    atomic_store_explicit(&tick_count, 0, memory_order_relaxed);
    initialized = true;
}

// Get current tick
uint32_t arch_timer_get_tick() {
    return atomic_load_explicit(&tick_count, memory_order_relaxed);
}

// Delay function
void arch_timer_delay(uint32_t n) {
    uint32_t start = arch_timer_get_tick();
    while (arch_timer_get_tick() - start < n);
}

// Start the next quantum cycle
// Usefull because tasks can pass to the scheduler without waiting to the quantum cycle (with task_sleep, task_yield or task_remove)
void arch_timer_start_quantum() {
    next_quantum_tick = tick_count + QUANTUM_TICK_LENGTH;
}