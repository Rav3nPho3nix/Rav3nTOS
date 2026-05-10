// Implementation of USART driver
// Bridge to the USART LOW LEVEL calls
#include "usart.h"
#include "usart_ll.h"

void usart_init(uint32_t baudrate) {
    return usart_ll_init(baudrate);
}

usart_status_t usart_write_char(char c) {
    return usart_ll_write_char(c);
}

usart_status_t usart_read_char(char* ptr_c) {
    return usart_ll_read_char(ptr_c);
}

usart_status_t usart_write_string(const char* str) {
    return usart_ll_write_string(str);
}
