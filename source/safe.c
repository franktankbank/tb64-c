#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

// Wrapper for fprintf that guarantees null-terminated formatting
int safe_fprintf(FILE* stream, const char* format, ...)
{
    int result;
    va_list args;
    va_start(args, format);
    result = vfprintf(stream, format, args);
    va_end(args);
    return result;
}

// Safe snprintf wrapper that ensures null termination
int safe_snprintf(char* buffer, size_t size, const char* format, ...)
{
    if (size == 0) {
        return 0;
    }

    va_list args;
    va_start(args, format);
    int written = vsnprintf(buffer, size, format, args);
    va_end(args);

    buffer[size - 1] = '\0';  // Always ensure null termination
    return written;
}

// A safe wrapper around memcpy that avoids NULL or zero-size copies
void* safe_memcpy(void* dest, const void* src, size_t n)
{
    if (!dest || !src || n == 0) {
        return dest;  // no-op
    }
    return memcpy(dest, src, n);
}
