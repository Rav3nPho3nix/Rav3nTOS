/*
* context.c
*
* Author : CAPITANO Giuliano (@Rav3nPho3nix)
*/

/*----- Includes -----*/
#include "task_internal.h"
#include "context.h"
#include "context_internal.h"
#include "critical_internal.h"
#include "scheduler_internal.h"
#include "arch_timer.h"

#include "arch.h"
/*----------*/

/*----- Defines -----*/

/*----------*/

/*----- Global variables -----*/
// Context of the scheduler
static ucontext_t scheduler_context;
// Stack of the scheduler
static uint8_t scheduler_stack[STACK_SIZE];
// Critical section state of the scheduler
static TaskCritical scheduler_critical;
/*----------*/

/*----- Internal functions -----*/
// Entry point for any task
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

    // Context section
    task->context.uc_stack.ss_sp = task->stack;
    task->context.uc_stack.ss_size = STACK_SIZE;
    task->context.uc_link = &scheduler_context;

    sigemptyset(&task->context.uc_sigmask);
    // Critical section
    task->critical.nesting_count = 0;
    sigemptyset(&task->critical.mask);

    makecontext(&task->context, _context_task_entry, 0);
}

// Initialize context for scheduler
void context_scheduler_init() {
    getcontext(&scheduler_context);
    scheduler_context.uc_stack.ss_sp = scheduler_stack;
    scheduler_context.uc_stack.ss_size = STACK_SIZE;
    scheduler_context.uc_link = NULL;
    
    sigemptyset(&scheduler_context.uc_sigmask);
    scheduler_critical.nesting_count = 0;
    sigemptyset(&scheduler_critical.mask);

    makecontext(&scheduler_context, scheduler_entry, 0);
}

// Switch contexts
void context_switch(Task *current_task, Task *next_task) {
    critical_set_critical(&next_task->critical);
    swapcontext(&current_task->context, &next_task->context);
}

// Switch to the scheduler context from current task
void context_switch_to_scheduler(Task *current_task) {
    critical_set_critical(&scheduler_critical);
    swapcontext(&current_task->context, &scheduler_context);
}

// Switch from scheduler context to the next task
void context_switch_from_scheduler(Task *next_task) {
    critical_set_critical(&next_task->critical);
    swapcontext(&scheduler_context, &next_task->context);
}

// Set context
void context_set(Task *task) {
    critical_set_critical(&task->critical);
    setcontext(&task->context);
}

// Save the context of the current interrupted task then preempt
void context_preempt(Task *task, TaskContext *context) {
    critical_set_critical(&scheduler_critical);
    swapcontext(&task->context, &scheduler_context);
}
/*----------*/