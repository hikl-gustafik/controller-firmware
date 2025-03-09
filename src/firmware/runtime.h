#pragma once

#include "layer.h"

class Runtime {
public:
    static void Initialize();
    static void Shutdown();

    static Runtime& Instance();

    // Starts the program loop.
    void BeginLoop();
    // Shuts down the current active layer and loads the new one.
    void Switch(Layer* layer);
private:
    Runtime();
    ~Runtime();

    bool m_ShouldStop = false;
    Layer* m_ActiveLayer = nullptr;
};
