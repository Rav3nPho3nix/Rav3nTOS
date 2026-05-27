#ifndef LOG_H
#define LOG_H

// Log info
// Take message as parameter
void log_info(const char*);

// Log error
// Take message as parameter
void log_error(const char*);

// Warn error
// Take message as parameter
void log_warn(const char*);

// Panic and dont let the kernel execute furthermore
// Take message as parameter
void log_panic(const char*);

#endif