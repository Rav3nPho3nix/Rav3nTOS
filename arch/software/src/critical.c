/*
* critical.c
* 
* Implement critical sections enter and exit with <signal.h> by using sigprocmask, support nested calls
*
* Author : CAPITANO Giuliano (@Rav3nPho3nix)
*/

/*----- Includes -----*/
#include "critical.h"
#include "arch_timer.h"

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
/*----------*/

/*----- Internal functions -----*/

/*----------*/

/*----- Function implementations -----*/
// Enter critical section and disable interrupts
void critical_enter() {
    // If enter for the first time
    if (nesting_count == 0) {
        // Construct the first mask
        sigset_t first_mask;
        sigemptyset(&first_mask);
        // Add the signal to block
        sigaddset(&first_mask, TIMER_SIGNAL);
        sigprocmask(SIG_BLOCK, &first_mask, &mask);
    }

    nesting_count++;
}

// Exit critical section and enable interrupts
void critical_exit() {
    // Check if nesting_count is not zero to prevent calling 'critical_exit' without having called before 'critical_enter'
    if (nesting_count == 0) {
        return;
    }

    nesting_count--;

    // If the count is zero, it unlock the signal
    if (nesting_count == 0) {
        sigprocmask(SIG_SETMASK, &mask, NULL);
    }
}
/*----------*/