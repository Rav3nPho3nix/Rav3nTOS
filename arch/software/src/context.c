/*
* context.c
*
* Author : CAPITANO Giuliano (@Rav3nPho3nix)
*/

/*----- Includes -----*/
#include "context.h"
#include "task_internal.h"

#include <ucontext.h>
/*----------*/

/*----- Defines -----*/

/*----------*/

/*----- Global variables -----*/
// Context of the scheduler
ucontext_t scheduler_context;
/*----------*/

/*----- Internal functions -----*/

/*----------*/

/*----- Function implementations -----*/
// Initialize task context
void context_init(Task *task) {
    getcontext(&task->context);

    task->context.uc_stack.ss_sp = task->stack;
    task->context.uc_stack.ss_size = STACK_SIZE;
    task->context.uc_link = &scheduler_context;

    makecontext(&task->context, task->function, 0);
}

// Switch contexts
void context_switch(Task *current_task, Task *next_task) {
    swapcontext(&current_task->context, &next_task->context);
}
/*----------*/