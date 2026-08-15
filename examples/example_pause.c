/*
This example kernel program show the usage of 'task_pause'
The 'Task 3' pauses and unpauses 'Task 1' and 'Task 2'
*/

#include <stdint.h>

#include "log.h"
#include "clock.h"
#include "task.h"
#include "scheduler.h"
#include "printf.h"
#include "critical.h"

// Arguments for task 1
struct task1_args {
    uint8_t x;
};

// Arguments for task 2
struct task2_args {
    uint8_t x;
    uint8_t y;
};

// Arguments for task 3
struct task3_args {
    TaskId task1_id;
    TaskId task2_id;
};

// Task 1 : print one unsigned
void task1_function(TaskArgs args) {
    struct task1_args *a = (struct task1_args*) args.optional_args;
    while (1) {
        printf("TASK %u : x = %u\n", args.self_id, a->x);
        task_sleep(100);
    }
}

// Task 2 : print two unsigned
void task2_function(TaskArgs args) {
    struct task2_args *a = (struct task2_args*) args.optional_args;
    while (1) {
        printf("TASK %u : x = %u, y = %u\n", args.self_id, a->x, a->y);
        task_sleep(100);
    }
}

// Task 3 : pause the two tasks, sleep 5s, unpause them, sleep 10s
void task3_function(TaskArgs args) {
    struct task3_args *a = (struct task3_args*) args.optional_args;
    while (1) {
        printf("TASK %u : Pause Task 1 and Task 2\n", args.self_id);
        task_pause(a->task1_id);
        task_pause(a->task2_id);

        printf("TASK %u : Sleep 5s\n", args.self_id);
        task_sleep(5000);

        printf("TASK %u : Unpause sleep Task 1 and Task 2\n", args.self_id);
        task_unpause(a->task1_id);
        task_unpause(a->task2_id);

        printf("TASK %u : Sleep 10s\n", args.self_id);
        task_sleep(10000);
    }
}

int main(void) {
    critical_init();
    // Setup clock with 1ms
    // 1ms = 1 000 000 ns
    clock_init(1000000);
    task_init();
    scheduler_init();

    // TaskId variable to store the id of Task 1 then Task 2 to fill the args of Task 3
    TaskId task_id;

    // Args of Task 1
    struct task1_args t1_args = {.x = 101};
    // Args of Task 2
    struct task2_args t2_args = {.x = 201, .y = 202};
    // Args of Task 3
    struct task3_args t3_args = {
        // Default values here
        .task1_id = (TaskId) {.id = 0},
        .task2_id = (TaskId) {.id = 0},
    };

    // Add Task 1
    if(task_add(&task1_function, &t1_args, HIGHEST_PRIORITY, &task_id) != TASK_ADD_STATUS_OK) {
        log_warn("IMPOSSIBLE TO ADD TASK 1");
    }
    log_info("TASK 1 ADDED");

    // Fill one of Task 3 argument
    t3_args.task1_id.id = task_id.id;

    // Add Task 2
    if(task_add(&task2_function, &t2_args, HIGHEST_PRIORITY, &task_id) != TASK_ADD_STATUS_OK) {
        log_warn("IMPOSSIBLE TO ADD TASK 2");
    }
    log_info("TASK 2 ADDED");

    // Fill the other Task 3 argument
    t3_args.task2_id.id = task_id.id;

    // Add Task 3
    if(task_add(&task3_function, &t3_args, HIGHEST_PRIORITY, NULL) != TASK_ADD_STATUS_OK) {
        log_warn("IMPOSSIBLE TO ADD TASK 3");
    }
    log_info("TASK 3 ADDED");

    scheduler_start();

    // Will never reach here
    while (1);
}