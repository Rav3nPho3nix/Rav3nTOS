// Return values of USART functions
#ifndef USART_TYPES_H
#define USART_TYPES_H

typedef enum {
    USART_STATUS_OK = 0,
    USART_STATUS_ERROR = -1,
    USART_STATUS_RX_EMPTY = -2,
    USART_STATUS_TX_FULL = -3
} usart_status_t;

#endif