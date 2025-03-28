#include "layer.h"

#include "debug.h"
#include "runtime.h"

static const char* s_Tag = "layer";

void Layer::ResetDisplay(Runtime& runtime) {
    auto& display = runtime.GetDisplay();
    // Clear display
    display.clearDisplay();
    // Set default text settings
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setTextWrap(false);
    // Loading screen
    display.setCursor(0, 0);
    display.print(GetLoadingText());
    // Initial draw
    display.display();
}

void Layer::InternalInitialize(Runtime& runtime) {
    ESP_LOGD(s_Tag, "Initializing layer %s (%p)...", GetName(), this);
    ResetDisplay(runtime);
    Initialize(runtime);
}

void Layer::InternalProcess(Runtime& runtime, float delta) {
    ESP_LOGV(s_Tag, "Running process on layer %s (%p)", GetName(), this);
    Process(runtime, delta);
}

void Layer::InternalShutdown(Runtime& runtime) {
    ESP_LOGD(s_Tag, "Shutting down layer %s (%p)...", GetName(), this);
    Shutdown(runtime);
}

void Layer::InternalAwake(Runtime& runtime) {
    ESP_LOGD(s_Tag, "Awaking layer %s (%p)", GetName(), this);
    ResetDisplay(runtime);
    Awake(runtime);
}

void Layer::InternalDraw(Runtime& runtime, float delta) {
    ESP_LOGV(s_Tag, "Drawing layer %s (%p)", GetName(), this);
    Draw(runtime, delta);
}

void Layer::InternalSleep(Runtime& runtime) {
    ESP_LOGD(s_Tag, "Sleeping layer %s (%p)", GetName(), this);
    runtime.GetHaptics().SetAll(0.0f);
    Sleep(runtime);
}
