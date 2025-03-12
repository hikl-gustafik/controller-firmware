#include "runtime.h"

#include "config.h"
#include "debug.h"

#include <freertos/FreeRTOS.h>
#include "Wire.h"

static const char* TAG = "runtime";

Runtime::Runtime() :
    m_Display(FW_SCREEN_WIDTH, FW_SCREEN_HEIGHT, &Wire, FW_PIN_RESET)
{
    ESP_LOGI(TAG, "Initializing...");
    Wire.begin(FW_PIN_SDA, FW_PIN_SCL, FW_I2C_FREQUENCY);

    ESP_LOGD(TAG, "Initializing display...");
    ASSERT(
        m_Display.begin(SSD1306_SWITCHCAPVCC, FW_SCREEN_ADDRESS),
        "SSD1306 allocation failed! (display)"
    );
    m_Display.setRotation(2); // Upside down
    m_Display.clearDisplay(); // Clear display
    // Initial draw
    m_Display.display();
}

Runtime::~Runtime() {
    ESP_LOGI(TAG, "Destroying...");
}

void Runtime::UpdateDelta(void*) {
    while (true) {
        s_DeltaTime += pdTICKS_TO_MS(1);
        vTaskDelay(1);
    }
    vTaskDelete(NULL);
}

float Runtime::GetDelta() {
    float result = s_DeltaTime / 1000.0f;
    s_DeltaTime = 0.0f;
    return result;
}

void Runtime::BeginLoop(unsigned int tickDelay) {
    ESP_LOGD(TAG, "Starting loop...");
    ESP_LOGV(TAG, "Loop tick delay: %d.", tickDelay);

    // Start delta task
    xTaskCreate(UpdateDelta, "UpdateDelta", 4096, 0, 1, &m_DeltaTask);

    // Intialize and awake layers pushed before the loop started.
    for (Layer* layer : m_LayerStack) {
        ASSERT(layer, "Null layer detected in layer stack!");
        layer->InternalInitialize(*this);
        layer->InternalAwake(*this);
    }

    // Run process and draw.
    while (!m_ShouldStop) {
        float delta = GetDelta();

        for (Layer* layer : m_LayerStack) {
            ASSERT(layer, "Null layer detected in layer stack!");
            layer->InternalProcess(*this, delta);
        }

        Layer* focused = m_LayerStack.back();
        ASSERT(focused, "Null layer detected at the top of layer stack!");
        focused->InternalDraw(*this, delta);

        // End loop if layer stack is empty.
        if (m_LayerStack.empty()) {
            EndLoop();
        }

        vTaskDelay(tickDelay);
    }

    // Sleep and shutdown all layers left on the stack after loop exited.
    for (Layer* layer : m_LayerStack) {
        ASSERT(layer, "Null layer detected in layer stack!");
        layer->InternalSleep(*this);
        layer->InternalShutdown(*this);
    }

    // End delta task.
    vTaskDelete(m_DeltaTask);
    GetDelta();

    ESP_LOGD(TAG, "Loop exited.");
}

void Runtime::EndLoop() {
    ESP_LOGD(TAG, "Exiting loop...");
    m_ShouldStop = true;
}

void Runtime::Push(Layer* layer) {
    ASSERT(layer, "Attempted to push a null layer on the layer stack!");
    ESP_LOGD(TAG, "Pushing layer %s (%p) to the layer stack...", layer->GetName(), layer);

    // Sleep original top layer.
    if (!m_LayerStack.empty()) {
        Layer* top = m_LayerStack.back();
        if (top) {
            top->InternalSleep(*this);
        }
    }

    // Push, initialize, and awake new top layer.
    m_LayerStack.push_back(layer);
    layer->InternalInitialize(*this);
    layer->InternalAwake(*this);
}

void Runtime::Pop() {
    ASSERT(!m_LayerStack.empty(), "Attempted to pop a layer from an empty layer stack!");
    ESP_LOGD(TAG, "Popping layer %s (%p) from the layer stack...", m_LayerStack.back()->GetName(), m_LayerStack.back());

    // Sleep, shutdown, and pop original top layer.
    Layer* popped = m_LayerStack.back();
    m_LayerStack.pop_back();
    if (popped) {
        popped->InternalSleep(*this);
        popped->InternalShutdown(*this);
    }

    // Awake new top layer.
    if (!m_LayerStack.empty()) {
        Layer* top = m_LayerStack.back();
        if (top) {
            top->InternalAwake(*this);
        }
    }
}

const Layer* Runtime::Top() {
    ASSERT(!m_LayerStack.empty(), "Attempted to access top layer of an empty layer stack!");
    Layer* top = m_LayerStack.back();
    ASSERT(top, "Null layer detected in layer stack!");
    return top;
}
