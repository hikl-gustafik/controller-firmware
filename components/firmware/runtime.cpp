#include "runtime.h"

#include "config.h"
#include "debug.h"

#include <freertos/FreeRTOS.h>
#include "Wire.h"

static const char* s_Tag = "runtime";

Runtime::Runtime() :
    m_Display(FW_SCREEN_WIDTH, FW_SCREEN_HEIGHT, &Wire, FW_PIN_RESET)
{
    // Intialize runtime
    ESP_LOGI(s_Tag, "Initializing...");
    Wire.begin(FW_PIN_SDA, FW_PIN_SCL, FW_I2C_FREQUENCY);

    // Initialize display
    ESP_LOGD(s_Tag, "Initializing display...");
    ASSERT(
        m_Display.begin(SSD1306_SWITCHCAPVCC, FW_SCREEN_ADDRESS),
        "SSD1306 allocation failed! (display)"
    );
    m_Display.setRotation(2); // Upside down
    m_Display.clearDisplay(); // Clear display
    m_Display.display(); // Initial draw

    // Initialize wifi
    ESP_LOGD(s_Tag, "Initializing wifi...");
    m_Wifi.disconnect();
}

Runtime::~Runtime() {
    ESP_LOGI(s_Tag, "Shutting down...");
    if (m_Running) {
        ESP_LOGW(s_Tag, "Loop should be ended before destroying the runtime!");
    }

    // Shutdown display
    ESP_LOGD(s_Tag, "Shutting down display...");
    m_Display.clearDisplay();
    m_Display.display();

    // Shutdown wifi
    ESP_LOGD(s_Tag, "Shutting down wifi...");
    m_Wifi.disconnect();

    ESP_LOGI(s_Tag, "Destruction complete.");
}

float Runtime::GetDelta() {
    if (!m_Running) {
        ESP_LOGW(s_Tag, "Requested delta time while not running! Returning 0.");
        return 0.0f;
    }
    float result = m_DeltaTime / 1000.0f;
    m_DeltaTime = 0.0f;
    return result;
}

void Runtime::BeginLoop(unsigned int tickDelay) {
    ESP_LOGD(s_Tag, "Starting loop...");
    ESP_LOGV(s_Tag, "Loop tick delay: %d.", tickDelay);

    if (m_Running) {
        ESP_LOGW(s_Tag, "Attempted to begin loop while it's already running!");
        return;
    }

    // Start delta task.
    xTaskCreate([](void* pvParameters) {
        const int delay = 1; // Ticks
        while (true) {
            float* deltaTime = (float*)pvParameters;
            *deltaTime += pdTICKS_TO_MS(delay);
            vTaskDelay(delay);
        }
        vTaskDelete(NULL);
    }, "UpdateDelta", 4096, &m_DeltaTime, 1, &m_DeltaTask);

    // Intialize and awake layers pushed before the loop started.
    for (Layer* layer : m_LayerStack) {
        ASSERT(layer, "Null layer detected in layer stack!");
        layer->InternalInitialize(*this);
        layer->InternalAwake(*this);
    }

    // Run process and draw.
    m_Running = true;
    while (m_Running) {
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

    ESP_LOGD(s_Tag, "Loop exited.");
}

void Runtime::EndLoop() {
    ESP_LOGD(s_Tag, "Exiting loop...");
    m_Running = false;
}

void Runtime::Push(Layer* layer) {
    ASSERT(layer, "Attempted to push a null layer on the layer stack!");
    ESP_LOGD(s_Tag, "Pushing layer %s (%p) to the layer stack...", layer->GetName(), layer);

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

const char* Runtime::Pop() {
    ASSERT(!m_LayerStack.empty(), "Attempted to pop a layer from an empty layer stack!");
    ESP_LOGD(s_Tag, "Popping layer %s (%p) from the layer stack...", m_LayerStack.back()->GetName(), m_LayerStack.back());

    Layer* popped = m_LayerStack.back();
    // Get return text of the original top layer.
    const char* returnText = popped->GetReturnText();
    // Sleep, shutdown, and pop original top layer.
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

    return returnText;
}

const Layer* Runtime::Top() {
    ASSERT(!m_LayerStack.empty(), "Attempted to access top layer of an empty layer stack!");
    Layer* top = m_LayerStack.back();
    ASSERT(top, "Null layer detected in layer stack!");
    return top;
}
