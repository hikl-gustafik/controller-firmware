#include "runtime.h"

#include "debug.h"

#include <freertos/FreeRTOS.h>
#include "Wire.h"

#define FW_SCREEN_WIDTH 128
#define FW_SCREEN_HEIGHT 64
#define FW_SCREEN_ADDRESS 0x3C
#define FW_RESET -1

static const char* TAG = "runtime";

Runtime::Runtime() :
    m_Display(FW_SCREEN_WIDTH, FW_SCREEN_HEIGHT, &Wire, FW_RESET)
{
    ESP_LOGI(TAG, "Initializing...");

    ASSERT(
        m_Display.begin(SSD1306_SWITCHCAPVCC, FW_SCREEN_ADDRESS),
        "SSD1306 allocation failed!"
    );
    m_Display.clearDisplay();
}

Runtime::~Runtime() {
    ESP_LOGI(TAG, "Destroying...");
}

void Runtime::BeginLoop(unsigned int tickDelayMs) {
    ESP_LOGD(TAG, "Starting loop...");
    ESP_LOGV(TAG, "Loop tick delay: %d ms.", tickDelayMs);
    while (!m_ShouldStop) {
        if (m_ActiveLayer) {
            m_ActiveLayer->InternalProcess(*this);
        }
        vTaskDelay(pdMS_TO_TICKS(tickDelayMs));
    }
    ESP_LOGD(TAG, "Loop exited.");
}

void Runtime::EndLoop() {
    ESP_LOGD(TAG, "Exiting loop...");
    m_ShouldStop = true;
}

void Runtime::Switch(Layer* layer) {
    ESP_LOGD(TAG, "Switching from layer %p to %p", m_ActiveLayer, layer);
    ASSERT(layer, "Attempted to switch to null layer!");

    if (m_ActiveLayer) {
        m_ActiveLayer->InternalShutdown(*this);
    }

    m_ActiveLayer = layer;
    m_ActiveLayer->InternalInitialize(*this);
}
