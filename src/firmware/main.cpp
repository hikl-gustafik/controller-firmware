#include <stdio.h>

#include "application.h"

extern "C" void app_main(void) {
    Application app;
    printf("My number is %d\n", app.myNumber());
}
