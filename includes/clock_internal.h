/*
* clock_internal.h
* 
* Internal API functions for clock
*
* Author : CAPITANO Giuliano (@Rav3nPho3nix)
*/

/*----- Include guards -----*/
#ifndef CLOCK_INTERNAL_H
#define CLOCK_INTERNAL_H
/*----------*/

/*----- Includes -----*/

/*----------*/

/*----- Defines -----*/

/*----------*/

/*----- Typedefs, structs and enums -----*/

/*----------*/

/*----- Function signatures -----*/
// Start the next quantum cycle
// Usefull because tasks can pass to the scheduler without waiting to the quantum cycle (with task_sleep, task_yield or task_remove)
void clock_start_quantum();
/*----------*/

/*----- End of include guards -----*/
#endif
/*----------*/