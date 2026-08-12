#ifndef ARCH_TASK_CONTEXT
#define ARCH_TASK_CONTEXT

#include "arch.h"

#define STACK_SIZE (64 * 1024)

// Context using <ucontext.h>
typedef ucontext_t TaskContext;

// Task critical section state for keeping track of nested call for critical_enter and critical_exit
typedef struct {
    uint32_t nesting_count;
    sigset_t mask;
} TaskCritical;

#endif