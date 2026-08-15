/*
This example kernel program show the usage of semaphores

Each task has 3 sections in my example and will remove itself at the end
These tasks sections needs to be runned in a specific order
Here is the following order :
1. Task 2.1
2. Task 3.1
3. Task 2.2
4. Task 1.1
5. Task 2.3
6. Task 1.2
7. Task 3.2
8. Task 1.3
9. Task 3.3

To simplify things, i will use one semaphore for each switch between two sections. That give a total of 8 semaphores
However I could have use less semaphores by using multiples times the same semaphores

Each task will only print his section. For example the task 1 will print "TASK 1 : 1" for his first section
*/

#include <stdint.h>

#include "log.h"
#include "clock.h"
#include "task.h"
#include "scheduler.h"
#include "printf.h"
#include "critical.h"
#include "semaphore.h"

// Here i defined the ID's of the 8 semaphores that i will use
#define SEM__T2_1__T3_1 0
#define SEM__T3_1__T2_2 1
#define SEM__T2_2__T1_1 2
#define SEM__T1_1__T2_3 3
#define SEM__T2_3__T1_2 4
#define SEM__T1_2__T3_2 5
#define SEM__T3_2__T1_3 6
#define SEM__T1_3__T3_3 7

void task1_function(TaskArgs args) {
    while (1) {
        semaphore_P(SEM__T2_2__T1_1);

        // Task 1.1
        printf("TASK %u : %u\n", 1, 1);

        semaphore_V(SEM__T1_1__T2_3, 1);

        semaphore_P(SEM__T2_3__T1_2);

        // Task 1.2
        printf("TASK %u : %u\n", 1, 2);

        semaphore_V(SEM__T1_2__T3_2, 1);

        semaphore_P(SEM__T3_2__T1_3);

        // Task 1.3
        printf("TASK %u : %u\n", 1, 3);

        semaphore_V(SEM__T1_3__T3_3, 1);

        // Remove itself
        task_remove(args.self_id);
    }
}

void task2_function(TaskArgs args) {
    while (1) {
        // Task 2.1
        printf("TASK %u : %u\n", 2, 1);
        
        semaphore_V(SEM__T2_1__T3_1, 1);

        semaphore_P(SEM__T3_1__T2_2);

        // Task 2.2
        printf("TASK %u : %u\n", 2, 2);

        semaphore_V(SEM__T2_2__T1_1, 1);

        semaphore_P(SEM__T1_1__T2_3);

        // Task 2.3
        printf("TASK %u : %u\n", 2, 3);

        semaphore_V(SEM__T2_3__T1_2, 1);

        // Remove itself
        task_remove(args.self_id);
    }
}

void task3_function(TaskArgs args) {
    while (1) {
        semaphore_P(SEM__T2_1__T3_1);

        // Task 3.1
        printf("TASK %u : %u\n", 3, 1);
        
        semaphore_V(SEM__T3_1__T2_2, 1);

        semaphore_P(SEM__T1_2__T3_2);

        // Task 3.2
        printf("TASK %u : %u\n", 3, 2);

        semaphore_V(SEM__T3_2__T1_3, 1);
        
        semaphore_P(SEM__T1_3__T3_3);

        // Task 3.3
        printf("TASK %u : %u\n", 3, 3);
    
        // Remove itself
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

    // Add Task 1
    if(task_add(&task1_function, NULL, HIGHEST_PRIORITY, NULL) != TASK_ADD_STATUS_OK) {
        log_warn("IMPOSSIBLE TO ADD TASK 1");
    }
    log_info("TASK 1 ADDED");

    // Add Task 2
    if(task_add(&task2_function, NULL, HIGHEST_PRIORITY, NULL) != TASK_ADD_STATUS_OK) {
        log_warn("IMPOSSIBLE TO ADD TASK 2");
    }
    log_info("TASK 2 ADDED");

    // Add Task 3
    if(task_add(&task3_function, NULL, HIGHEST_PRIORITY, NULL) != TASK_ADD_STATUS_OK) {
        log_warn("IMPOSSIBLE TO ADD TASK 3");
    }
    log_info("TASK 3 ADDED");

    scheduler_start();

    // Will never reach here
    while (1);
}