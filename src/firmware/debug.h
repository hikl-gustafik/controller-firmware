#pragma once

#include <stdio.h>

#if !defined(RELEASE) && !defined(DIST)

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

#else

#define ASSERT(condition, message)
#define DEBUG(message)

#endif
