/*
* critical.h
* 
* Critical sections header file to enable and disable interrupts
*
* Author : CAPITANO Giuliano (@Rav3nPho3nix)
*/

/*----- Include guards -----*/
#ifndef CRITICAL_H
#define CRITICAL_H
/*----------*/

/*----- Includes -----*/

/*----------*/

/*----- Defines -----*/

/*----------*/

/*----- Typedefs, structs and enums -----*/

/*----------*/

/*----- Function signatures -----*/
// Enter critical section and disable interrupts
void critical_enter();

// Exit critical section and enable interrupts
void critical_exit();
/*----------*/

/*----- End of include guards -----*/
#endif
/*----------*/