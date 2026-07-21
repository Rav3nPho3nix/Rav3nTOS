#include "console.h"
#include "bsp.h"

void console_write(const char* msg) {
    printf("%s", msg);
}