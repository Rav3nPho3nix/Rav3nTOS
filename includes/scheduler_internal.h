/*
* scheduler_internal.h
*
* Author : CAPITANO Giuliano (@Rav3nPho3nix)
*/

/*----- Include guards -----*/
#ifndef SCHEDULER_INTERNAL_H
#define SCHEDULER_INTERNAL_H
/*----------*/

/*----- Includes -----*/
#include "task_internal.h"
#include <stdbool.h>
/*----------*/

/*----- Defines -----*/

/*----------*/

/*----- Typedefs, structs and enums -----*/

/*----------*/

/*----- Function signatures -----*/
// Find next task to execute
void scheduler_next();

// Entry point of scheduler
void scheduler_entry();

// Getter for the current task
Task* scheduler_get_current_task();

// Getter to know if the scheduler is started
bool scheduler_is_started();
/*----------*/

/*----- End of include guards -----*/
#endif
/*----------*/