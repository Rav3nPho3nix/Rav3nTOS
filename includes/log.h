#ifndef LOG_H
#define LOG_H

// Log info
// Take message as parameter
// void log_info(const char*);
void log_info(const char* format, ...);

// Log error
// Take message as parameter
// void log_error(const char*);
void log_error(const char* format, ...);

// Warn error
// Take message as parameter
// void log_warn(const char*);
void log_warn(const char* format, ...);

// Panic and dont let the kernel execute furthermore
// Take message as parameter
// void log_panic(const char*);
void log_panic(const char* format, ...);

#endif