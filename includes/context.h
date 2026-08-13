#ifndef CONTEXT_H
#define CONTEXT_H

#include "task_internal.h"

// Initialize context
void context_init(Task *task);

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

#endif