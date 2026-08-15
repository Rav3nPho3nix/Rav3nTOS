#ifndef CONFIG_H
#define CONFIG_H

// Must fit in 8 bits
// Maximum value of 255
#define NUMBER_OF_TASKS 255

// Number of priorities for tasks
// To do a priority-free scheduling, just set it as 1
// Must fit in 8 bits
#define NUMBER_OF_PRIORITIES 32

// Number of semaphores
#define NUMBER_OF_SEMAPHORES 32

// Quantum tick value
// Must fit in 16 bits. This give a maximum of 65535 ticks for a quantum cycle, that is long enough ;)
#define QUANTUM_TICK_LENGTH 100

#endif