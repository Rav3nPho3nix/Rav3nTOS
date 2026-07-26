#ifndef CONTEXT_H
#define CONTEXT_H

#include "task_internal.h"

// Initialize context
void context_init(Task *task);

// Switch contexts
void context_switch(Task *current_task, Task *next_task);

#endif