#ifndef CONFIG_H
#define CONFIG_H

// Here i set up 256 tasks (values from 0 to 255) to have the value 256 as an illegal value
#define NUMBER_OF_TASKS 256

// Number of priorities for tasks
// To do a priority-free scheduling, just set it as 1
#define NUMBER_OF_PRIORITIES 32

// Number of semaphores
#define NUMBER_OF_SEMAPHORES 31

// Quantum value
#define QUANTUM_VALUE 100

#endif