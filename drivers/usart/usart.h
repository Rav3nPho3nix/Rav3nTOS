// API for USART driver
#ifndef USART_H
#define USART_H

#include <stdint.h>

#include "usart_types.h"

// Initialisation of USART
// Taking baudrate in parameter
void usart_init(uint32_t baudrate);

// WriteChar for USART
usart_status_t usart_write_char(char);

// ReadChar for USART
usart_status_t usart_read_char(char*);

// WriteString for USART
usart_status_t usart_write_string(const char*);

#endif