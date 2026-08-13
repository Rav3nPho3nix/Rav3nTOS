#ifndef TASK_H
#define TASK_H

#include <stdint.h>
#include <stddef.h>
#include "config.h"

/*
Priorities :
0 to (NUMBER_OF_PRIORITIES -1) : 0 = highest
*/
#define HIGHEST_PRIORITY 0
#define LOWEST_PRIORITY (NUMBER_OF_PRIORITIES - 1)

//// Typedefs and structs ////

// Typedef for TaskId
typedef struct {
    uint8_t id;
} TaskId;

// Typedef that define the function parameters
// Containing at minimal the id of the task itself and others optional arguments
typedef struct {
    // Id of the task itself
    TaskId self_id;
    // Optional arguments
    void *optional_args;
} TaskArgs;

// Typedef that define the function of the task
// TaskArgs is passed by value (not by pointer) so the task cannot change the self_id or the optional_args pointer stored internally.
// Note: this does NOT protect the data pointed to by optional_args itself.
typedef void (*TaskFunction) (TaskArgs args);

// Enum that defines task state
typedef enum {
    TASK_STATE_READY = 0,
    TASK_STATE_RUNNING = 1,
    TASK_STATE_SLEEPING = 2,
    TASK_STATE_PAUSED = 3,
    TASK_STATE_UNUSED = 4,
} TaskState;

// Enum for status values when adding a task
typedef enum {
    TASK_ADD_STATUS_OK = 0,
    TASK_ADD_STATUS_ILLEGAL_PRIORITY = 1,
    TASK_ADD_STATUS_NO_AVAILABLE_TASK = 2
} TaskAddStatus;

// Enum for status values when removing a task
typedef enum {
    TASK_REMOVE_STATUS_OK = 0,
    TASK_REMOVE_STATUS_ILLEGAL_ID = 1,
} TaskRemoveStatus;

// Enum for status values when pausing a task
typedef enum {
    TASK_PAUSE_STATUS_OK = 0,
    TASK_PAUSE_STATUS_ILLEGAL_ID = 1,
    TASK_PAUSE_STATUS_ALREADY_PAUSED = 2,
} TaskPauseStatus;

// Enum for status values when unpausing a task
typedef enum {
    TASK_UNPAUSE_STATUS_OK = 0,
    TASK_UNPAUSE_STATUS_ILLEGAL_ID = 1,
    TASK_UNPAUSE_STATUS_NOT_PAUSED = 2,
} TaskUnpauseStatus;

////

//// Functions signatures ////

// Initialize tasks
void task_init();

// Add a new task
// Take function pointer, priority
// Modify 'task_id' argument
// Return status value
TaskAddStatus task_add(TaskFunction function, void *args, uint8_t priority, TaskId *task_id);

// Remove a task by taking is id
TaskRemoveStatus task_remove(TaskId task_id);

// Put the current task to sleep for n ticks
void task_sleep(uint32_t n);

// Pause the task by taking is id
TaskPauseStatus task_pause(TaskId task_id);

// Unpause the task by taking is id
TaskUnpauseStatus task_unpause(TaskId task_id);

// Give up the current task to the scheduler
void task_yield();

#endif