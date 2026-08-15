// // Kernel main function
// #include "critical.h"
// #include "clock.h"
// #include "task.h"
// #include "scheduler.h"

// void main() {
//     critical_init();
//     // Setup clock with 1ms
//     // 1ms = 1 000 000 ns
//     clock_init(1000000);
//     task_init();
//     scheduler_init();
//     scheduler_start();
//     // main function must never return
//     while (1);
// }

/*
This example kernel program show the usage of 'task_sleep'
'task_sleep' put the task into SLEEPING state and give the hand to the scheduler.
Every quantum, it will check if the sleeping time is done. If yes, the task is put to READY and can be selected again by scheduler

This example only run a task that print then sleep for 5s
*/

#include "log.h"
#include "clock.h"
#include "task.h"
#include "scheduler.h"
#include "printf.h"
#include "critical.h"

// Task function
void task_function(TaskArgs args) {
    while (1) {
        printf("TASK OUTPUT\n");

        // put to sleep for 5s
        printf("TASK SLEEP FOR 5s\n");
        task_sleep(5000);
    }
}

int main(void) {
    critical_init();
    // Setup clock with 1ms
    // 1ms = 1 000 000 ns
    clock_init(1000000);
    task_init();
    scheduler_init();

    // Add Task
    if(task_add(&task_function, NULL, HIGHEST_PRIORITY, NULL) != TASK_ADD_STATUS_OK) {
        log_warn("IMPOSSIBLE TO ADD TASK\n");
    }
    log_info("TASK ADDED");

    scheduler_start();

    // Will never reach here
    while (1);
}