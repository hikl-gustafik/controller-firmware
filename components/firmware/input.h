#pragma once

#include "config.h"

#include <cstdint>

#include "esp32-hal-gpio.h"

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

    /**
     * @param state The state to check (default = LOW)
     *
     * @returns True if the left joystick button is pressed
     */
    bool LeftJoystickButton(int state = LOW);

    /**
     * @param state The state to check (default = LOW)
     *
     * @returns True if the right joystick button is pressed
     */
    bool RightJoystickButton(int state = LOW);

    /**
     * @param state The state to check (default = LOW)
     *
     * @returns True if button 1 is pressed
     */
    bool Button1(int state = LOW);

    /**
     * @param state The state to check (default = LOW)
     *
     * @returns True if button 2 is pressed
     */
    bool Button2(int state = LOW);

    /**
     * @param state The state to check (default = LOW)
     *
     * @returns True if button 3 is pressed
     */
    bool Button3(int state = LOW);

    /**
     * @param state The state to check (default = LOW)
     *
     * @returns True if button 4 is pressed
     */
    bool Button4(int state = LOW);
private:
    double FormatJoystickOutput(uint16_t raw);
};
