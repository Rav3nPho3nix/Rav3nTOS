/*
* semaphore_internal.h
* 
* Description
*
* Author : CAPITANO Giuliano (@Rav3nPho3nix)
*/

/*----- Include guards -----*/
#ifndef SEMAPHORE_INTERNAL_H
#define SEMAPHORE_INTERNAL_H
/*----------*/

/*----- Includes -----*/
#include <stdint.h>
/*----------*/

/*----- Defines -----*/

/*----------*/

/*----- Typedefs, structs and enums -----*/
// Typedef for a semaphore
// Contains a counter
typedef struct {
    uint32_t _Atomic counter;
} Semaphore;
/*----------*/

/*----- Function signatures -----*/

/*----------*/

/*----- End of include guards -----*/
#endif
/*----------*/