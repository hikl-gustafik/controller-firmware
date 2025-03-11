#include "layer.h"

#include "debug.h"

static const char* TAG = "layer";

void Layer::InternalInitialize(Runtime& runtime) {
    ESP_LOGD(TAG, "Initializing layer %p...", this);
    Initialize(runtime);
}

void Layer::InternalProcess(Runtime& runtime) {
    ESP_LOGV(TAG, "Running process on sync layers of %p...", this);
    for (Layer* const layer : m_SyncLayers) {
        ASSERT(layer, "Sync layer is null during process!");
        // Recursive process call
        layer->InternalProcess(runtime);
    }

    ESP_LOGV(TAG, "Running process on layer %p", this);
    Process(runtime);
}

void Layer::InternalShutdown(Runtime& runtime) {
    ESP_LOGV(TAG, "Shutting down sync layers of %p...", this);
    for (Layer* layer : m_SyncLayers) {
        ASSERT(layer, "Sync layer is null during shutdown!");
        StopSync(layer, runtime);
    }

    ESP_LOGD(TAG, "Shutting down layer %p...", this);
    Shutdown(runtime);
}

void Layer::StartSync(Layer* layer, Runtime& runtime) {
    ESP_LOGD(TAG, "Started syncing %p from %p", layer, this);
    ASSERT(layer, "Sync layer is null during start!");
    layer->InternalInitialize(runtime);
    m_SyncLayers.insert(layer);
}

void Layer::StopSync(Layer* layer, Runtime& runtime) {
    ESP_LOGD(TAG, "Stopped syncing %p from %p", layer, this);
    ASSERT(layer, "Sync layer is null during stop!");
    layer->InternalShutdown(runtime);
    m_SyncLayers.erase(layer);
}
