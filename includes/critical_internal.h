/*
* critical_internal.h
* 
* Internal content for critical.c implementation
*
* Author : CAPITANO Giuliano (@Rav3nPho3nix)
*/

/*----- Include guards -----*/
#ifndef CRITICAL_INTERNAL_H
#define CRITICAL_INTERNAL_H
/*----------*/

/*----- Includes -----*/
#include "task_internal.h"
/*----------*/

/*----- Defines -----*/

/*----------*/

/*----- Typedefs, structs and enums -----*/

/*----------*/

/*----- Function signatures -----*/
// Set the new critical section state (contain the nesting counter and the masks)
void critical_set_critical(TaskCritical *critical);
/*----------*/

/*----- End of include guards -----*/
#endif
/*----------*/