#include "debug.h"
#include "usart.h"

void debug_write(const char* msg) {
    usart_write_string(msg);
}