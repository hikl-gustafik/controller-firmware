#pragma once

// Forward declaration to prevent circular dependencies.
class Runtime;

class Layer {
public:
    /**
     * @brief Method overrideable by child layers to return their name.
     *
     * Used for menus and debugging.
     *
     * @returns Name of the layer.
     */
    virtual inline const char* GetName() const { return "Layer"; }
protected:
    /*
     * @brief Runs when the layer is pushed to the runtime layer stack.
     */
    virtual void Initialize(Runtime& runtime) {}

    /**
     * @brief Runs repeatedly while the layer is active, regardless of focus.
     *
     * @param delta Rough time since last call, in seconds.
     */
    virtual void Process(Runtime& runtime, float delta) {}

    /**
     * @brief Runs before the layer is popped off the runtime layer stack.
     */
    virtual void Shutdown(Runtime& runtime) {}

    /**
     * @brief Runs when the layer gains focus.
     */
    virtual void Awake(Runtime& runtime) {}

    /**
     * @brief Runs repeatedly while the layer is active and focused.
     *
     * Typically used for drawing and listening for layer-specific input.
     *
     * @param delta Rough time since last call, in seconds.
     */
    virtual void Draw(Runtime& runtime, float delta) {}

    /**
     * @brief Runs when the layer loses focus.
     */
    virtual void Sleep(Runtime& runtime) {}

    /**
     * @returns Text to display while the layer is loading. (default: empty string)
     *
     * Can be used to display a loading screen or message. Make sure to clear
     * the display before returning from Awake().
     */
    virtual inline const char* GetLoadingText() { return ""; }

    /**
     * @returns Text to return when the layer is popped. (default: "")
     */
    virtual inline const char* GetReturnText() const { return ""; }
private:
    // Runtime can access private members of this class.
    friend class Runtime;
private:
    // Called by the runtime.
    void InternalInitialize(Runtime& runtime);
    // Called by the runtime.
    void InternalProcess(Runtime& runtime, float delta);
    // Called by the runtime.
    void InternalShutdown(Runtime& runtime);
    // Called by the runtime.
    void InternalAwake(Runtime& runtime);
    // Called by the runtime.
    void InternalDraw(Runtime& runtime, float delta);
    // Called by the runtime.
    void InternalSleep(Runtime& runtime);

    // Reset display settings and display loading screen based on GetLoadingText().
    void ResetDisplay(Runtime& runtime);
};
