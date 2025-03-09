#include "runtime.h"

#include "debug.h"

#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"

static Runtime* s_Instance;

Runtime::Runtime() {
}

Runtime::~Runtime() {
}

void Runtime::Initialize() {
    ASSERT(!s_Instance, "Runtime is already initialized!");
    DEBUG("Initializing runtime...");
    s_Instance = new Runtime();
}

void Runtime::Shutdown() {
    DEBUG("Shutting down runtime...");

    if (!s_Instance) {
        return;
    }

    s_Instance->m_ShouldStop = true;

    delete s_Instance;
    s_Instance = nullptr;
}

Runtime& Runtime::Instance() {
    ASSERT(s_Instance, "Runtime is not initialized!");
    return *s_Instance;
}

void Runtime::BeginLoop() {
    while (!m_ShouldStop) {
        if (m_ActiveApp) {
            m_ActiveApp->Process();
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void Runtime::Switch(App* app) {
    ASSERT(app, "Attempted to switch to null app!");

    if (m_ActiveApp) {
        m_ActiveApp->Shutdown();
    }

    m_ActiveApp = app;
    m_ActiveApp->Initialize();
}
