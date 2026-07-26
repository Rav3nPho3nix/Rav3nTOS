#ifndef ARCH_TASK_CONTEXT
#define ARCH_TASK_CONTEXT

#include "arch.h"

#define STACK_SIZE (64 * 1024)

// Context using <ucontext.h>
typedef ucontext_t TaskContext;

#endif