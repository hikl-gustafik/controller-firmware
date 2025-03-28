#pragma once

// Out of line, compiler wants it this way for some reason
#include <vector>

#include "WiFi.h"
#include "fuel.h"
#include "haptics.h"
#include "input.h"
#include "layer.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>

// Aliases for types handled by the runtime

using Display = Adafruit_SSD1306;
using Wifi = WiFiClass;

class Runtime {
public:
    Runtime();
    ~Runtime();

    // Handled by the runtime

    inline Display& GetDisplay() { return m_Display; }
    inline Wifi GetWifi() { return m_Wifi; }

    // Handled by custom classes

    inline Fuel& GetFuel() { return m_Fuel; }
    inline Haptics& GetHaptics() { return m_Haptics; }
    inline Input& GetInput() { return m_Input; }

    /**
     * @brief Start the program loop.
     *
     * Must be called explicitly!
     */
    void BeginLoop(unsigned int tickDelay = 1);

    /**
     * @brief Stop the program loop.
     *
     * Should be run from within the loop.
     */
    void EndLoop();

    /**
     * @brief Push new layer onto the layer stack and initialize and focus it.
     */
    void Push(Layer* layer);

    /**
     * @brief Pop the top layer off the layer stack and shut it down.
     *
     * Focuses the layer below it.
     */
    void Pop();

    /**
     * @returns The top layer of the layer stack.
     */
    const Layer* Top();
private:
    Display m_Display;
    Wifi& m_Wifi = WiFi;

    Fuel m_Fuel;
    Haptics m_Haptics;
    Input m_Input;

    bool m_Running = false;

    TaskHandle_t m_DeltaTask;
    float m_DeltaTime = 0.0f; // Milliseconds
    float GetDelta(); // Seconds

    // Vector publicly acts as a stack
    // because we need iteration.
    std::vector<Layer*> m_LayerStack;
};
