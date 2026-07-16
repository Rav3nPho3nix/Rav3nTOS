#ifndef TASK_H
#define TASK_H

#include <stdint.h>
#include <stddef.h>

/*
Define tasks using priorities.
Priorities :
0 to 30 : 0 = highest & 30 = lowest
31 : illegal value for available task
*/

#define NUMBER_OF_PRIORITIES 31
#define HIGHEST_PRIORITY 0
#define LOWEST_PRIORITY (NUMBER_OF_PRIORITIES - 1)
#define ILLEGAL_PRIORITY NUMBER_OF_PRIORITIES

// Struct for status values when adding a task
typedef enum {
    TASK_ADD_STATUS_OK = 0,
    TASK_ADD_STATUS_ILLEGAL_PRIORITY = 1,
    TASK_ADD_STATUS_NO_AVAILABLE_TASK = 2
} TaskAddStatus;

// Struct for status values when removing a task
typedef enum {
    TASK_REMOVE_STATUS_OK = 0,
    TASK_REMOVE_STATUS_ILLEGAL_ID = 1,
} TaskRemoveStatus;

//// Functions signatures ////

// Initialize tasks
void task_init();

// Add a new task
// Take function pointer, priority
// Modify 'task_id' argument
// Return status value
TaskAddStatus task_add(void (*function) (void *args), uint8_t priority, uint32_t *task_id);

// Remove a task by taking is id
TaskRemoveStatus task_remove(uint32_t task_id);

#endif