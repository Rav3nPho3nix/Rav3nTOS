#include "log.h"
#include "console.h"

void _log_write(const char* category, const char* msg) {
    console_write(category);
    console_write(msg);
    console_write("\r\n");
}

void log_info(const char* msg) {
    _log_write("[INFO] ", msg);
}

void log_error(const char* msg) {
    _log_write("[ERROR] ", msg);
}

void log_warn(const char* msg) {
    _log_write("[WARN] ", msg);
}

void log_panic(const char* msg) {
    _log_write("[PANIC] ", msg);
    // Never quit panic function
    while (1) {}
}