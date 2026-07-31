/*
* printf.c
*
* Author : CAPITANO Giuliano (@Rav3nPho3nix)
*/

/*----- Includes -----*/
#include "printf.h"
#include <unistd.h>
/*----------*/

/*----- Defines -----*/

/*----------*/

/*----- Global variables -----*/

/*----------*/

/*----- Internal functions -----*/

/*----------*/

/*----- Function implementations -----*/
void _putchar(char character) {
    write(1, &character, 1);
}
/*----------*/