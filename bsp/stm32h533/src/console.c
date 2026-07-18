#include "console.h"
#include "usart.h"

void console_write(const char* msg) {
    usart_write_string(msg);
}