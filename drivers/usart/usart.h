// API for USART driver
#ifndef USART_H
#define USART_H

#include <stdint.h>

#include "usart_types.h"

// Initialisation of USART
// Taking baudrate in parameter
void usart_init(uint32_t baudrate);

// PutChar for USART
usart_status_t usart_putchar(char);

// GetChar for USART
usart_status_t usart_getchar(char*);

#endif