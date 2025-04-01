#include "layer.h"
#include "runtime.h"

#include "prebuilt/keyboard.h"
#include "prebuilt/layer-picker.h"

#include "apps/dashboard.cpp"
#include "apps/doom.cpp"
#include "apps/screen-saver.cpp"
#include "apps/main-menu.cpp"

extern "C" void app_main(void) {
    // Games
    Doom doom;
    Layer* games[] = {
        &doom,
    };
    LayerPicker gameMenu(games, "Games");

    // Tests
    ScreenSaver screenSaver;
    Keyboard keyboard;
    Layer* tests[] = {
        &screenSaver,
        (Layer*)&keyboard,
    };
    LayerPicker testMenu(tests, "Tests");

    // Standalone
    Dashboard dashboard;

    // Main menu
    Layer* items[] = {
        &dashboard,
        &gameMenu,
        &testMenu,
    };
    MainMenu mainMenu(items);

    Runtime runtime;
    runtime.Push(&mainMenu);
    runtime.BeginLoop();
}
