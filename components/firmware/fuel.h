#pragma once

#include "Adafruit_MAX1704X.h"

class Fuel {
public:
    Fuel(int maxAttempts = 10, int waitMs = 100);

    /**
     * @returns True if the battery is connected
     */
    bool IsActive();

    /**
     * @param badResult Value to return if battery is not connected (defaults to 0)
     *
     * @returns Battery voltage (V) or badResult if battery is not connected
     */
    float Voltage(float badResult = 0.0);

    /**
     * @param badResult Value to return if battery is not connected (defaults to 100)
     *
     * @returns Battery percentage (%) or badResult if battery is not connected
     */
    float Percent(float badResult = 100.0);

    /**
     * @param badResult Value to return if battery is not connected (defaults to 0)
     *
     * @returns Battery charge rate (%/h) or badResult if battery is not connected
     */
    float ChargeRate(float badResult = 0.0);

    inline Adafruit_MAX17048& GetDevice() { return m_Device; }
private:
    Adafruit_MAX17048 m_Device;
};
