#pragma once


#ifdef DIST

#define ASSERT(condition, ...)
#define DEBUG(message)

#else

#include <stdio.h>

#define ASSERT(condition, ...) \
    do { \
        if (!condition) { \
            printf("[ASSERTION FAILED] "); \
            printf(__VA_ARGS__); \
            printf("\n"); \
            while(1); \
        } \
    } while(0)

#define DEBUG(...) \
    do { \
        printf("[DEBUG] "); \
        printf(__VA_ARGS__); \
        printf("\n"); \
    } while(0)

#endif
