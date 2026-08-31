/*
* config_internal.h
* 
* Check config.h file #define
*
* Author : CAPITANO Giuliano (@Rav3nPho3nix)
*/

/*----- Include guards -----*/
#ifndef CONFIG_INTERNAL_H
#define CONFIG_INTERNAL_H
/*----------*/

/*----- Includes -----*/
#include "config.h"
#include <assert.h>
/*----------*/

/*----- Assertions -----*/

// TASKS
static_assert(NUMBER_OF_TASKS > 1, "Number of priorities must be 1 or higher");
static_assert(NUMBER_OF_TASKS <= 254, "Number of tasks must be 254 or lower");

// PRIORITIES
static_assert(NUMBER_OF_PRIORITIES > 0, "Number of priorities must be 1 or higher");
static_assert(NUMBER_OF_PRIORITIES <= 256, "Number of priorities must be 256 or lower");

// SEMAPHORES
static_assert(NUMBER_OF_SEMAPHORES <= 256, "Number of priorities must be 256 or lower");

// QUANTUM TICK VALUE
static_assert(QUANTUM_TICK_LENGTH <= 65535, "Quantum tick value must be 65535 or lower");
/*----------*/

/*----- End of include guards -----*/
#endif
/*----------*/