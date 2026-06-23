// API for USART driver
#ifndef USART_H
#define USART_H

#include <stdint.h>

#include "usart_status.h"

// Initialisation of USART
// Taking baudrate in parameter
void usart_init(uint32_t baudrate);

// WriteChar for USART
UsartStatus usart_write_char(char);

// ReadChar for USART
UsartStatus usart_read_char(char*);

// WriteString for USART
UsartStatus usart_write_string(const char*);

#endif