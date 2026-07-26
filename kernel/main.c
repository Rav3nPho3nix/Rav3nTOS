#include <stdint.h>

// #include "platform.h"
// #include "log.h"
// #include "clock.h"
// #include "task.h"

// #define CLOCK_FREQUENCY 32000000
// #define TICK_FREQUENCY 1000

#include "log.h"
#include "clock.h"
#include "task.h"
#include "scheduler.h"

#include <stdio.h>
#include <stdbool.h>

void _1() {
    while (1)
        printf("TASK 1 RUNNING\n");
}
void _2() {
    while (1)
        printf("TASK 2 RUNNING\n");
}

void _3() {
    while (1)
        printf("TASK 3 RUNNING\n");
}

int main(void) {
    // platform_init();

    // // Init clock
    // if (clock_init(CLOCK_FREQUENCY / TICK_FREQUENCY) != 0U) {
    //     while(1);
    // }
    
    // TaskManager *tm;
    // // Init tasks
    // tm = task_init();

    // // Kernel body
    // while(1) {
    //     TaskAddStatus status;
    //     uint32_t task_id;

    //     log_info("Adding a task");
    //     status = task_add(&none, 1, &task_id);

    //     if (status == TASK_ADD_STATUS_OK) {
    //         log_warn("\t>> OK !");
    //     }
    //     else if (status == TASK_ADD_STATUS_ILLEGAL_PRIORITY) {
    //         log_warn("\t>> Illegal priority !");
    //     }
    //     else {
            // log_warn("\t>> No other available tasks !");
    //     }

    //     clock_wait(1000);
    // }

    // Setup clock with 1ms
    // 1ms = 1 000 000 ns
    clock_init(1000000);

    task_init();
    scheduler_init();

    TaskId task_id;
    TaskAddStatus task_st;

    if(task_add(&_1, 0, &task_id) == TASK_ADD_STATUS_OK) {
        printf("ADDED TASK : id = %u, fn = %p\n", task_id.id, &_1);
    }
    if(task_add(&_2, 0, &task_id) == TASK_ADD_STATUS_OK) {
        printf("ADDED TASK : id = %u, fn = %p\n", task_id.id, &_2);
    }
    if(task_add(&_3, 0, &task_id) == TASK_ADD_STATUS_OK) {
        printf("ADDED TASK : id = %u, fn = %p\n", task_id.id, &_3);
    }
    
    scheduler_start();
    while (1) {}
}