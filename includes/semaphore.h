/*
* semaphore.h
* 
* Semaphores header file
* A semaphore is a simple data structure to guarantee a multi tasks access of a ressource
* It uses a counter : the task can only acces the ressource if the semaphore is strictly superior at zero
*
* Author : CAPITANO Giuliano (@Rav3nPho3nix)
*/

/*----- Include guards -----*/
#ifndef SEMAPHORE_H
#define SEMAPHORE_H
/*----------*/

/*----- Includes -----*/
#include <stdint.h>
/*----------*/

/*----- Defines -----*/

/*----------*/

/*----- Typedefs, structs and enums -----*/
// Enum for status values when incrementing the semaphore
typedef enum {
    SEMAPHORE_V_STATUS_OK = 0,
    SEMAPHORE_V_STATUS_ILLEGAL_ID = 1,
} SemaphoreVStatus;

// Enum for status values when decrementing the semaphore
typedef enum {
    SEMAPHORE_P_STATUS_OK = 0,
    SEMAPHORE_P_STATUS_ILLEGAL_ID = 1,
} SemaphorePStatus;
/*----------*/

/*----- Function signatures -----*/
// V operation for semaphore of given id
// Increment the semaphore by value n
SemaphoreVStatus semaphore_V(uint32_t id, uint32_t n);

// P operation for semaphore of given id
// Try to decrease the semaphore by 1
// If the semaphore is already to zero, it wait until it can decrement it
SemaphorePStatus semaphore_P(uint32_t id);
/*----------*/

/*----- End of include guards -----*/
#endif
/*----------*/