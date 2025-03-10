#pragma once

#include "config.h"

#include <cstdint>

class Input {
public:
    Input();

    /**
     * @returns Horizontal axis of left joystick (-1.0 to 1.0)
     */
    double LeftJoystickX();

    /**
     * @returns Vertical axis of left joystick (-1.0 to 1.0)
     */
    double LeftJoystickY();

    /**
     * @returns Horizontal axis of right joystick (-1.0 to 1.0)
     */
    double RightJoystickX();

    /**
     * @returns Vertical axis of right joystick (-1.0 to 1.0)
     */
    double RightJoystickY();
private:
    double FormatJoystickOutput(uint16_t raw);
};
