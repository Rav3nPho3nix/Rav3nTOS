/*
* semaphore.c
* 
* Semaphore implementation
*
* Author : CAPITANO Giuliano (@Rav3nPho3nix)
*/

/*----- Includes -----*/
#include "semaphore.h"
#include "semaphore_internal.h"
#include "critical.h"
#include "config.h"
#include "task.h"
/*----------*/

/*----- Defines -----*/
#define ILLEGAL_SEMAPHORE_ID NUMBER_OF_SEMAPHORES
/*----------*/

/*----- Global variables -----*/
// As static to fill it with zeros
static Semaphore semaphores[NUMBER_OF_SEMAPHORES];
/*----------*/

/*----- Internal functions -----*/

/*----------*/

/*----- Function implementations -----*/
// V operation for semaphore of given id
// Increment the semaphore by value n
SemaphoreVStatus semaphore_v(uint32_t id, uint32_t n) {
    // If the id is illegal
    if (id > ILLEGAL_SEMAPHORE_ID) {
        return SEMAPHORE_V_STATUS_ILLEGAL_ID;
    }

    critical_enter();
    // Increment the counter
    semaphores[id].counter += n;
    critical_exit();

    return SEMAPHORE_V_STATUS_OK;
}

// P operation for semaphore of given id
// Try to decrease the semaphore by 1
// If the semaphore is already to zero, it wait until it can decrement it
SemaphorePStatus semaphore_p(uint32_t id) {
    // If the id is illegal
    if (id > ILLEGAL_SEMAPHORE_ID) {
        return SEMAPHORE_P_STATUS_ILLEGAL_ID;
    }

    critical_enter();
    // Give the hand to the scheduler if the counter is zero
    while (semaphores[id].counter == 0) {
        critical_exit();
        task_check_preemption();
        critical_enter();
    }

    // Decrement the counter
    semaphores[id].counter--;
    critical_exit();

    return SEMAPHORE_P_STATUS_OK;
}
/*----------*/