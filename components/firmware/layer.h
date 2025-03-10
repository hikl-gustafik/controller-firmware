#pragma once

#include <set>

// Forward declaration to prevent circular dependencies.
class Runtime;

class Layer {
protected:
    /**
     * @brief Runs after being costructed during loading.
     */
    virtual void Initialize(Runtime& runtime) {}

    /**
     * @brief Runs repeatedly while the layer is active.
     */
    virtual void Process(Runtime& runtime) {}

    /**
     * @brief Runs before the layer is shut down by the runtime.
     */
    virtual void Shutdown(Runtime& runtime) {}

    /**
     * @brief Initialize layer and synchronize its process to this instance.
     *
     * @param layer Layer to synchronize.
     */
    void StartSync(Layer* layer, Runtime& runtime);

    /**
     * @brief Shutdown synchronized layer and stop synchronizing.
     *
     * Called automatically when this layer is shutting down.
     */
    void StopSync(Layer* layer, Runtime& runtime);
private:
    // Runtime can access private members of this class.
    friend class Runtime;
private:
    // Called by the runtime and parent layers during sync.
    void InternalInitialize(Runtime& runtime);
    // Called by the runtime and parent layers during sync.
    void InternalProcess(Runtime& runtime);
    // Called by the runtime and parent layers during sync.
    void InternalShutdown(Runtime& runtime);

    std::set<Layer*> m_SyncLayers;
};
