#ifndef SAFE_H
#define SAFE_H

#include <stdio.h>

int safe_fprintf(FILE* stream, const char* format, ...);

int safe_snprintf(char* buffer, size_t size, const char* format, ...);

void* safe_memcpy(void* dest, const void* src, size_t n);

#endif
