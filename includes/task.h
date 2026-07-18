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

/*
Here i set up 255 tasks (values from 0 to 254) to have the value 256 as an illegal value
*/
// #define NUMBER_OF_TASKS 256
#define NUMBER_OF_TASKS 3
#define ILLEGAL_TASK_ID NUMBER_OF_TASKS

//// Typedefs and structs ////

// Struct that define a task content
typedef struct {
    // Pointer to the task function
    void (*function) (void *args);
    // Priority
    uint8_t priority;
} TaskContent;
//

// Struct that contain a task
// Implementing a circular doubly link list
typedef struct TaskContainer_s TaskContainer;

struct TaskContainer_s {
    // Task content
    TaskContent task;
    // Pointer to next and to previous tasks containers
    TaskContainer *next, *previous;
};
//

// Struct that manage the tasks
typedef struct TaskManager_s {
    // Array of TaskContainers
    TaskContainer tasks[NUMBER_OF_TASKS];
    // Array of TaskContainers pointers for each priority
    // Will also be used for scheduling by modifying the pointer value
    TaskContainer *priorities[NUMBER_OF_PRIORITIES];
    // Next available TaskContainer
    TaskContainer *available;
} TaskManager;
//

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

////

//// Global variable ////

extern TaskManager task_manager;

////

//// Functions signatures ////

// Initialize tasks
TaskManager* task_init();

// Add a new task
// Take function pointer, priority
// Modify 'task_id' argument
// Return status value
TaskAddStatus task_add(void (*function) (void *args), uint8_t priority, uint32_t *task_id);

// Remove a task by taking is id
TaskRemoveStatus task_remove(uint32_t task_id);

#endif