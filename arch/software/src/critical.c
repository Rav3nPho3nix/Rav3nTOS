/*
* critical.c
* 
* Implement critical sections enter and exit with <signal.h> by using sigprocmask, support nested calls
*
* Author : CAPITANO Giuliano (@Rav3nPho3nix)
*/

/*----- Includes -----*/
#include "critical.h"
#include "critical_internal.h"
#include "arch_timer.h"
#include "arch_task_context.h"

#include <signal.h>
#include <stdint.h>
/*----------*/

/*----- Defines -----*/

/*----------*/

/*----- Global variables -----*/
// Counter of nested calls
uint32_t nesting_count = 0;
// Mask
sigset_t mask;

// Current critical section state
TaskCritical *current_critical_state = NULL;
// Critical section state for the kernel main loop (outside of any task)
TaskCritical kernel_critical_state;
/*----------*/

/*----- Internal functions -----*/

/*----------*/

/*----- Function implementations -----*/
// Initialize critical section for the kernel
// Necessary to add a task because it call 'critical_enter' and 'critical_exit'
// Must be called first by the kernel
void critical_init() {
    kernel_critical_state.nesting_count = 0;
    current_critical_state = &kernel_critical_state;
}

// Enter critical section and disable interrupts
void critical_enter() {
    // If enter for the first time
    if (current_critical_state->nesting_count == 0) {
        // Construct the first mask
        sigset_t first_mask;
        sigemptyset(&first_mask);
        // Add the signal to block
        sigaddset(&first_mask, TIMER_SIGNAL);
        sigprocmask(SIG_BLOCK, &first_mask, &current_critical_state->mask);
    }

    current_critical_state->nesting_count++;
}

// Exit critical section and enable interrupts
void critical_exit() {    
    // Check if nesting_count is not zero to prevent calling 'critical_exit' without having called before 'critical_enter'
    if (current_critical_state->nesting_count == 0) {
        return;
    }

    current_critical_state->nesting_count--;

    // If the count is zero, it unlock the signal
    if (current_critical_state->nesting_count == 0) {
        sigprocmask(SIG_SETMASK, &current_critical_state->mask, NULL);
    }
}

// Set the new critical section state (contain the nesting counter and the masks)
void critical_set_critical(TaskCritical *critical) {
    current_critical_state = critical;
}
/*----------*/