#include "log.h"
#include "printf.h"

void log_info(const char* format, ...) {
    printf_("[INFO] ");
    va_list args;
    va_start(args, format);
    vprintf_(format, args);
    va_end(args);
    printf_("\n");
}

void log_error(const char* format, ...) {
    printf_("[ERROR] ");
    va_list args;
    va_start(args, format);
    vprintf_(format, args);
    va_end(args);
    printf_("\n");
}

void log_warn(const char* format, ...) {
    printf_("[WARN] ");
    va_list args;
    va_start(args, format);
    vprintf_(format, args);
    va_end(args);
    printf_("\n");
}

void log_panic(const char* format, ...) {
    printf_("[PANIC] ");
    va_list args;
    va_start(args, format);
    vprintf_(format, args);
    va_end(args);
    printf_("\n");

    // Never quit panic function
    while (1);
}