#ifndef TASK_INTERNAL_H
#define TASK_INTERNAL_H

#include "task.h"
#include "arch_task_context.h"

// Struct that define a task
struct Task_s {
    // Stack
    uint8_t stack[STACK_SIZE];
    // Pointer to the task function
    TaskFunction function;
    // Task arguments
    TaskArgs args;
    // Priority
    uint8_t priority;
    // Context
    TaskContext context;
    // State
    TaskState state;
    // Tick value to wake up after a call to 'task_sleep'
    uint32_t wake_up_tick;
    // Critical state
    TaskCritical critical;
};
//

// Struct that contain a task
// Implementing a circular doubly link list
typedef struct TaskContainer_s TaskContainer;

struct TaskContainer_s {
    // Task content
    Task task;
    // Pointer to next and to previous tasks containers
    TaskContainer *next, *previous;
};
//

// Struct that manage the tasks
typedef struct {
    // Array of TaskContainers
    TaskContainer tasks[NUMBER_OF_TASKS];
    // Array of TaskContainers pointers for each priority
    // Will also be used for scheduling by modifying the pointer value
    TaskContainer *priorities[NUMBER_OF_PRIORITIES];
    // Next available TaskContainer
    TaskContainer *available;
} TaskManager;
//

// Return the pointed task for a priority
// Seing from scheduler point of view, it leads to the next task that will be running
TaskContainer* task_get_priority_cursor(uint8_t priority);

// Set the pointed task for a priority
void task_set_priority_cursor(uint8_t priority, TaskContainer *task);

#endif