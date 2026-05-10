// Low level API for USART driver
#ifndef USART_LL_H
#define USART_LL_H

#include <stdint.h>

#include "usart_types.h"

// Low level initialisation of USART
// Taking baudrate in parameter
void usart_ll_init(uint32_t baudrate);

// Low level putChar for USART
usart_status_t usart_ll_putchar(char);

// Low level getChar for USART
usart_status_t usart_ll_getchar(char*);

#endif