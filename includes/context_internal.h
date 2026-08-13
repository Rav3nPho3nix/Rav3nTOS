/*
* context_internal.h
* 
* Internal functions headers for context switches
*
* Author : CAPITANO Giuliano (@Rav3nPho3nix)
*/

/*----- Include guards -----*/
#ifndef CONTEXT_INTERNAL_H
#define CONTEXT_INTERNAL_H
/*----------*/

/*----- Includes -----*/

/*----------*/

/*----- Defines -----*/

/*----------*/

/*----- Typedefs, structs and enums -----*/

/*----------*/

/*----- Function signatures -----*/
// Initialize context for scheduler
void context_scheduler_init();

// Switch contexts
// If 'next_task' is NULL, it's switching to the scheduler context
void context_switch(Task *current_task, Task *next_task);

// Switch to the scheduler context from current task
void context_switch_to_scheduler(Task *current_task);

// Switch from scheduler context to the next task
void context_switch_from_scheduler(Task *next_task);

// Set context
void context_set(Task *task);

// Save the context of the current interrupted task then preempt
void context_preempt(Task *task, TaskContext *context);
/*----------*/

/*----- End of include guards -----*/
#endif
/*----------*/