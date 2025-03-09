#pragma once

#include <set>

class Layer {
public:
protected:
    // Runs while the app loads.
    virtual void Initialize() {}
    // Runs repeatedly when the app is active.
    virtual void Process() {}
    // Runs before the app is closed.
    virtual void Shutdown() {}

    // Initialize layer and synchronize its process to this instance.
    void StartSync(Layer* layer);
    // Shutdown synchronized layer and stop synchronizing.
    // Called automatically when this layer is shutting down.
    void StopSync(Layer* layer);
private:
    friend class Runtime;
    // Called by the runtime and parent layers during sync.
    void InternalInitialize();
    // Called by the runtime and parent layers during sync.
    void InternalProcess();
    // Called by the runtime and parent layers during sync.
    void InternalShutdown();

    std::set<Layer*> m_SyncLayers;
};
