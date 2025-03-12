#include "layer.h"
#include "runtime.h"

#include "apps/diagnostics.cpp"
#include "apps/doom.cpp"
#include "apps/screensaver.cpp"
#include "apps/menu.cpp"

extern "C" void app_main(void) {
    Diagnostics diagnostics;
    Doom doom;
    ScreenSaver screenSaver;

    Layer* items[] = {
        &diagnostics,
        &doom,
        &screenSaver,
    };
    Menu mainMenu(items);

    Runtime runtime;
    runtime.Push(&mainMenu);
    runtime.BeginLoop();
}
