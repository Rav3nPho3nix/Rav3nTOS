/*
* context.c
*
* Author : CAPITANO Giuliano (@Rav3nPho3nix)
*/

/*----- Includes -----*/
#include "context.h"
#include "task_internal.h"
#include "scheduler_internal.h"

#include "arch.h"
/*----------*/

/*----- Defines -----*/

/*----------*/

/*----- Global variables -----*/
// Context of the scheduler
ucontext_t scheduler_context;
// Stack of the scheduler
uint8_t scheduler_stack[STACK_SIZE];
/*----------*/

/*----- Internal functions -----*/
void _context_task_entry() {
    Task *task = scheduler_get_current_task();
    if (task) {
        task->function(task->args);
    }
}
/*----------*/

/*----- Function implementations -----*/
// Initialize task context
void context_init(Task *task) {
    getcontext(&task->context);

    task->context.uc_stack.ss_sp = task->stack;
    task->context.uc_stack.ss_size = STACK_SIZE;
    task->context.uc_link = &scheduler_context;

    makecontext(&task->context, _context_task_entry, 0);
}

// Initialize context for scheduler
void context_scheduler_init() {
    getcontext(&scheduler_context);
    scheduler_context.uc_stack.ss_sp = scheduler_stack;
    scheduler_context.uc_stack.ss_size = STACK_SIZE;
    scheduler_context.uc_link = NULL;
    makecontext(&scheduler_context, scheduler_entry, 0);
}

// Switch contexts
void context_switch(Task *current_task, Task *next_task) {
    swapcontext(&current_task->context, &next_task->context);
}

// Switch to the scheduler context from current task
void context_switch_to_scheduler(Task *current_task) {
    swapcontext(&current_task->context, &scheduler_context);
}

// Switch from scheduler context to the next task
void context_switch_from_scheduler(Task *next_task) {
    swapcontext(&scheduler_context, &next_task->context);
}

// Set context
void context_set(Task *task) {
    setcontext(&task->context);
}
/*----------*/