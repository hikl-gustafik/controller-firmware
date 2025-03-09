#include "layer.h"

void Layer::InternalInitialize() {
    Initialize();
}

void Layer::InternalProcess() {
    for (Layer* layer : m_SyncLayers) {
        layer->InternalProcess();
    }

    Process();
}

void Layer::InternalShutdown() {
    for (Layer* layer : m_SyncLayers) {
        StopSync(layer);
    }

    Shutdown();
}

void Layer::StartSync(Layer* layer) {
    layer->InternalInitialize();
    m_SyncLayers.insert(layer);
}

void Layer::StopSync(Layer* layer) {
    layer->InternalShutdown();
    m_SyncLayers.erase(layer);
}
