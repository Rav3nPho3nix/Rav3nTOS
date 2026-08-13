#include "scheduler.h"
#include "scheduler_internal.h"
#include "task.h"
#include "task_internal.h"
#include "context.h"
#include "clock.h"
#include "critical.h"

//// Typedef ////

////

//// Global variables ////

// Task that is running
static TaskContainer *current_running_task = NULL;

// Boolean that store if scheduling is enabled
static bool scheduler_started = false;

////

//// Internal functions ////

TaskContainer* _scheduler_find_next() {
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
                // If the current_task is SLEEPING and if his wake up tick number is passed, make it READY without looping to the next one
                if (current_task->task.state == TASK_STATE_SLEEPING &&
                    clock_get_tick() >= current_task->task.wake_up_tick) {
                    // Set it as READY
                    current_task->task.state = TASK_STATE_READY;
                }

                // Else the current_task is neither READY or SLEEPING
                else {
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
            }
            
            // If it found a task
            if (current_task) {
                task_found = true;
                task_set_priority_cursor(i, current_task->next);
            }
        }

        i++;
    }

    // If there is no task
    if (!current_task) {
        return NULL;
    }
    // Return the task
    return current_task;
}

// Idle task function
void _scheduler_idle_task() {
    // Does nothing
    while (1);
}

////

//// Functions implementations ////

// Initialize scheduler with an idle task that does nothing
void scheduler_init() { 
    // Add the idle task
    task_add(&_scheduler_idle_task, NULL, LOWEST_PRIORITY, NULL);
}

void scheduler_start() {
    // Initialize scheduler context
    context_scheduler_init();

    // Find first task
    TaskContainer *task = _scheduler_find_next();

    // If there is no task
    if (!task) {
        return;
    }
    current_running_task = task;

    critical_enter();
    task->task.state = TASK_STATE_RUNNING;
    critical_exit();

    // Start scheduling
    scheduler_started = true;

    // Start first task
    context_set(&task->task);
}

void scheduler_next() {
    // If there is a task currently running
    if (current_running_task) {

        critical_enter();

        // If the task is in RUNNING, set is as READY
        if (current_running_task->task.state == TASK_STATE_RUNNING) {
            // Change his state
            current_running_task->task.state = TASK_STATE_READY;
        }

        // Context switching to scheduler context
        context_switch_to_scheduler(&current_running_task->task);
        
        critical_exit();
    }
}


void scheduler_entry() {
    // Loop indefinitely
    while (1) {
        critical_enter();

        // Find next task
        TaskContainer *next_task = _scheduler_find_next();

        // It there is a next task
        if (next_task) {
            // Change task state
            next_task->task.state = TASK_STATE_RUNNING;
            // Set it as the currently running one
            current_running_task = next_task;

            // Switch from scheduler to the task
            context_switch_from_scheduler(&next_task->task);
        }
        critical_exit();
    }
}

Task* scheduler_get_current_task() {
    if (!current_running_task) {
        return NULL;
    }
    return &current_running_task->task;
}

// Getter to know if the scheduler is started
bool scheduler_is_started() {
    return scheduler_started;
}

////

