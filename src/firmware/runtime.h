#pragma once

#include "app.h"

class Runtime {
public:
    // Starts program loop
    static void Initialize();
    static void Shutdown();

    static Runtime& Instance();

    // Starts program loop
    void BeginLoop();
    // Destroys the previous active app and loads the new one
    void Switch(App* app);
private:
    Runtime();
    ~Runtime();

    bool m_ShouldStop = false;
    App* m_ActiveApp = nullptr;
};
