#include <stdint.h>

extern uint32_t _estack;

void Reset_Handler(void);
void Default_Handler(void);

__attribute__((section(".isr_vector")))
void (* const vector_table[])(void) = {
    (void (*)(void))(&_estack),
    Reset_Handler,

    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,
    Default_Handler,

    0,
    0,
    0,
    0,

    Default_Handler,
    Default_Handler,
    0,
    Default_Handler,
    Default_Handler
};

void Default_Handler(void) {
    while (1) {}
}