#pragma once

#include "display.h"
#include "layer.h"

class Runtime {
public:
    static void Initialize();
    static void Shutdown();
    static Runtime& Instance();

    inline Display& getDisplay() { return m_Display; }

    // Starts the program loop.
    void BeginLoop();
    // Shuts down the current active layer and loads the new one.
    void Switch(Layer* layer);
private:
    Runtime();
    ~Runtime();

    Display m_Display;

    bool m_ShouldStop = false;
    Layer* m_ActiveLayer = nullptr;
};
