#include <stdbool.h>

#include "task.h"
#include "task_internal.h"
#include "context.h"

//// Global variables ////

TaskManager task_manager;

////

//// Internal functions ////

// Make task available
void _task_make_available(TaskContainer *ptr_task) {
    // Set priority to illegal value
    ptr_task->task.priority = ILLEGAL_PRIORITY;
    // Clear function pointer
    ptr_task->task.function = NULL;

    // Clear double linking pointers
    ptr_task->next = NULL;
    ptr_task->previous = NULL;
}

// Find next available task
uint32_t _task_find_next_available() {
    uint32_t i=0;
    // Loop while the next task pointer is not NULL
    while (i < NUMBER_OF_TASKS && task_manager.tasks[i].next != NULL) {
        i++;
    }
    return i;
}

// Update next available task pointer
void _task_update_next_available() {
    // Find next available task id
    uint32_t next_available = _task_find_next_available();

    // If the returned id is illegal
    if (next_available == ILLEGAL_TASK_ID) {
        task_manager.available = NULL;
        return;
    }

    // Set next available task pointer
    task_manager.available = &task_manager.tasks[next_available];
    return;
}

////

//// Functions implementations ////

void task_init() {
    // Make all tasks availables
    for (uint32_t i=0; i<NUMBER_OF_TASKS; i++) {
        _task_make_available(&task_manager.tasks[i]);
    }
    
    // Set next available task pointer to the first TaskContainer
    task_manager.available = task_manager.tasks;

    // Clear all pointers for each priorities
    for (uint8_t i=0; i<NUMBER_OF_PRIORITIES; i++) {
        task_manager.priorities[i] = NULL;
    }
}

TaskAddStatus task_add(void (*function) (void *args), uint8_t priority, TaskId *task_id) {
    // If the priority is illegal
    if (priority > LOWEST_PRIORITY) {
        return TASK_ADD_STATUS_ILLEGAL_PRIORITY;
    }

    // If there is no next available task
    if (!task_manager.available) {
        // return error value
        return TASK_ADD_STATUS_NO_AVAILABLE_TASK;
    }

    // Get available task
    // Point to the current added task
    TaskContainer *task = task_manager.available;

    // Fill task
    task->task.function = function;
    task->task.priority = priority;

    // If there is not other task for this priority
    if (!task_manager.priorities[priority]) {
        // Connect to the priorities array
        task_manager.priorities[priority] = task;

        // Connect to itself for double linked array
        task->next = task;
        task->previous = task;
    }
    // Connect to already existing tasks for this priority
    else {
        // Pointed task from priorities array
        TaskContainer *current_priority_pointed_task = task_manager.priorities[priority];
        // Previous pointed task from priorities array
        TaskContainer *current_priority_previous_pointed_task = current_priority_pointed_task->previous;

        // Fill 'previous' pointer of current added task
        task->previous = current_priority_previous_pointed_task;
        // Fill 'next" pointer of current added task
        task->next = current_priority_pointed_task;

        // Update 'next' of previous pointed task to the current added task
        current_priority_previous_pointed_task->next = task;
        // Update 'previous' of pointed task to the current added task
        current_priority_pointed_task->previous = task;
    }

    // Update next available task pointer
    _task_update_next_available();

    // Initialize his context
    context_init(&task->task);

    // Calculate the task id
    task_id->id = (uint32_t) (task - task_manager.tasks);
    return TASK_ADD_STATUS_OK;
}

TaskRemoveStatus task_remove(TaskId task_id) {
    // If the id is illegal
    if (task_id.id > LOWEST_PRIORITY) {
        return TASK_REMOVE_STATUS_ILLEGAL_ID;
    }

    // Current task to remove
    TaskContainer *current_task = &task_manager.tasks[task_id.id];

    // If the task is the only one of this priority
    if (current_task->next == current_task) {
        task_manager.priorities[current_task->task.priority] = NULL;
    }
    // Else rearrange the double linked list
    else {
        // Next task of current task
        TaskContainer *next_task = current_task->next;

        // Previous task of current task
        TaskContainer *previous_task = current_task->previous;
    
        // Set 'next' of previous task to next task
        previous_task->next = next_task;

        // Set 'previous' of next task to previous task
        next_task->previous = previous_task;

        // If priority array point to current task to remove, modify priority array value to next task
        if (task_manager.priorities[current_task->task.priority] == current_task) {
            task_manager.priorities[current_task->task.priority] = next_task;
        }
    }
    
    // Make the current task available
    _task_make_available(current_task);
}

// Return the pointed task for a priority
TaskContainer* task_get_priority_cursor(uint8_t priority) {
    // Only for internal usage so i don't check for priority value out of bounds access
    return task_manager.priorities[priority];
}

// Set the pointed task for a priority
void task_set_priority_cursor(uint8_t priority, TaskContainer *task) {
    task_manager.priorities[priority] = task;
}

////