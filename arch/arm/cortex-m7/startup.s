.syntax unified
.cpu cortex-m7
.thumb

.global Reset_Handler

.extern main

.extern _sidata
.extern _sdata
.extern _edata

.extern _sbss
.extern _ebss

.section .text.Reset_Handler

Reset_Handler:

    ldr r0, =_sidata
    ldr r1, =_sdata
    ldr r2, =_edata

copy_data:
    cmp r1, r2
    bge clear_bss

    ldr r3, [r0], #4
    str r3, [r1], #4

    b copy_data

clear_bss:

    ldr r1, =_sbss
    ldr r2, =_ebss

    movs r3, #0

zero_bss:
    cmp r1, r2
    bge call_main

    str r3, [r1], #4

    b zero_bss

call_main:

    bl main

hang:
    b hang