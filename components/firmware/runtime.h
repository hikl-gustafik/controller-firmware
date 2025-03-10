#pragma once

#include "layer.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>

using Display = Adafruit_SSD1306;

class Runtime {
public:
    Runtime();
    ~Runtime();

    inline Display& GetDisplay() { return m_Display; }

    /**
     * @brief Start the program loop.
     *
     * Must be called explicitly!
     */
    void BeginLoop(unsigned int tickDelayMs = 10);

    /**
     * @brief Stop the program loop.
     *
     * Should be run from within the loop.
     */
    void EndLoop();

    /**
     * @brief Shut down the current active layer and load the new one.
     *
     * Load = construct and initialize.
     */
    void Switch(Layer* layer);
private:
    Display m_Display;

    bool m_ShouldStop = false;
    Layer* m_ActiveLayer = nullptr;
};
