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
/*----------*/

/*----- End of include guards -----*/
#endif
/*----------*/