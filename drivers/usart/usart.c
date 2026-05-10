// Implementation of USART driver
// Bridge to the USART LOW LEVEL calls
#include "usart.h"
#include "usart_ll.h"

void usart_init(uint32_t baudrate) {
    return usart_ll_init(baudrate);
}

usart_status_t usart_putchar(char c) {
    return usart_ll_putchar(c);
}

usart_status_t usart_getchar(char* ptr_c) {
    return usart_ll_getchar(ptr_c);
}
