/*
This example kernel program show the usage of 'task_remove'
'task_remove' remove the task by taking an id (either the task itself or another task)

This example run two tasks :
- Task 1 : print indefinitely
- Task 2 : print 5 times before removing Task 1 then itself
*/

#include "log.h"
#include "clock.h"
#include "task.h"
#include "scheduler.h"
#include "printf.h"
#include "critical.h"

// Struct to take as optional args the TaskId of Task 1
struct task2_args {
    TaskId task1_id;
};

// Task 1 : print forever
void task1_function(TaskArgs args) {
    while (1) {
        printf("TASK 1\n");
    }
}

// Task 2 : loop and print 5 times then remove Task 1 and Task 2
void task2_function(TaskArgs args) {
    // Get his args
    struct task2_args *a = (struct task2_args*) args.optional_args;
    uint8_t x;

    while (1) {
        // Loop 5 times
        for (x = 0; x < 5; x++) {
            printf("TASK 2 : counter = %u\n", x);
        }

        printf("TASK 2 : REMOVE TASK 1\n");
        task_remove(a->task1_id);

        printf("TASK 2 : REMOVE TASK 2 (itself)\n");
        task_remove(args.self_id);
    }
}

int main(void) {
    critical_init();
    // Setup clock with 1ms
    // 1ms = 1 000 000 ns
    clock_init(1000000);
    task_init();
    scheduler_init();

    // TaskId to store the id of Task 1
    TaskId task_id;

    // Args of Task 2
    struct task2_args t2_args = {
        // Default value here
        .task1_id = (TaskId) {.id = 0},
    };

    // Add Task 1
    if(task_add(&task1_function, NULL, HIGHEST_PRIORITY, &task_id) != TASK_ADD_STATUS_OK) {
        log_warn("IMPOSSIBLE TO ADD TASK 1\n");
    }
    log_info("TASK 1 ADDED");

    // Fill Task 2 args
    t2_args.task1_id = task_id;

    // Add Task 2
    if(task_add(&task2_function, &t2_args, HIGHEST_PRIORITY, NULL) != TASK_ADD_STATUS_OK) {
        log_warn("IMPOSSIBLE TO ADD TASK 2\n");
    }
    log_info("TASK 2 ADDED");

    scheduler_start();

    // Will never reach here
    while (1);
}