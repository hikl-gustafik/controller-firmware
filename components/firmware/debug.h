#pragma once

#include "esp_log.h"

#ifdef DIST

#define ASSERT(condition, ...)

#else

#define ASSERT(condition, ...)\
    do {\
        if (!condition) {\
            ESP_LOGE(\
                "ASSERTION FAILED",\
                __VA_ARGS__\
            );\
            while(1); \
        }\
    } while(0)

#endif
