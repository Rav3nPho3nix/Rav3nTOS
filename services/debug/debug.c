#include "debug.h"
#include "usart.h"

void debug_write(const char* str) {
    usart_write_string(str);
}