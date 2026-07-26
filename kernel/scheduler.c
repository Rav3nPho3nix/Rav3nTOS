#include "scheduler.h"
#include "scheduler_internal.h"
#include "task.h"
#include "task_internal.h"
#include "context.h"

//// Typedef ////

////

//// Global variables ////

// Task that is running
static TaskContainer *current_running_task = NULL;

// Boolean that store if scheduling is enabled
bool scheduler_started = false;

////

//// Internal functions ////

Task* _scheduler_find_next() {
    bool task_found = false;
    unsigned i = 0;
    // Store the current task to check
    TaskContainer *current_task = NULL;

    // Looping while there is no found task and check for out of bounds with the index
    while (!task_found && i <= LOWEST_PRIORITY) {
        current_task = task_get_priority_cursor(i);

        // If there is at least one task for this priority
        if (current_task) {
            
            // Store the first task for this priority (to check if we achieve a loop due to task linking)
            TaskContainer *first_task = current_task;

            // Loop while current_task is not null (if so, there is no task) and if the task is not READY
            while (current_task && current_task->task.state != TASK_STATE_READY) {
                // If the next task is the first task, there is no READY task for this priority 
                if (current_task->next == first_task) {
                    // Set to NULL to exit while loop
                    current_task = NULL;
                }
                // Else we loop to the next one
                else {
                    current_task = current_task->next;
                }
            }
            
            // If it found a task
            if (current_task) {
                task_found = true;
                task_set_priority_cursor(i, current_task->next);
                
                // Set the state of the current running task to READY
                if (current_running_task) {
                    current_running_task->task.state = TASK_STATE_READY;
                }

                // Set the state of the next task on running
                current_task->task.state = TASK_STATE_RUNNING;
                // Update new task
                current_running_task = current_task;
            }
        }

        i++;
    }
    
    // If there is no task
    if (!current_task) {
        return NULL;
    }
    // Return the task
    return &current_task->task;
}

////

//// Functions implementations ////

void scheduler_init() {
    // 
}

void scheduler_start() {
    // Start scheduling
    scheduler_started = true;

    // Task *task = _scheduler_find_next();

    // if (task) {
        // printf("Task found : P = %u, FN = %p\n", task->priority, task->function);
    // }
    // else {
        // printf("No task found\n");
    // }
}

void scheduler_next() {
    // Find next task
    Task *task = _scheduler_find_next();

#include <stdio.h>
    printf("Next\n");

    // If there is a task
    if (task) {
        context_switch(&current_running_task->task, task);
    }
}

////

