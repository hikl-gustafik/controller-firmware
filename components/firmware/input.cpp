#include "input.h"

#include "debug.h"

#include "esp32-hal-adc.h"
#include "esp32-hal-gpio.h"

static const char* s_Tag = "input";

Input::Input() {
    ESP_LOGD(s_Tag, "Initializing input...");

    // Left joystick axes
    pinMode(FW_PIN_LJX, INPUT);
    pinMode(FW_PIN_LJY, INPUT);
    // Left joystick button
    pinMode(FW_PIN_LJZ, INPUT_PULLUP);
    // Right joystick axes
    pinMode(FW_PIN_RJX, INPUT);
    pinMode(FW_PIN_RJY, INPUT);
    // Right joystick button
    pinMode(FW_PIN_RJZ, INPUT_PULLUP);
    // Buttons
    pinMode(FW_PIN_B1, INPUT_PULLUP);
    pinMode(FW_PIN_B2, INPUT_PULLUP);
    pinMode(FW_PIN_B3, INPUT_PULLUP);
    pinMode(FW_PIN_B4, INPUT_PULLUP);
}

double Input::FormatJoystickOutput(uint16_t raw) {
    if (raw <= FW_JOYSTICK_MIN) return -1.0;
    if (raw >= FW_JOYSTICK_MAX) return 1.0;
    double fraction = (double)raw / FW_JOYSTICK_MAX; // 0.0 to 1.0
    double scaled = (fraction - 0.5) * 2; // -1.0 to 1.0
    if (
        scaled < FW_JOYSTICK_DEADZONE &&
        scaled > -FW_JOYSTICK_DEADZONE
    ) {
        return 0.0;
    }
    if (scaled > FW_JOYSTICK_SATURATION) {
        return 1.0;
    }
    if (scaled < -FW_JOYSTICK_SATURATION) {
        return -1.0;
    }
    return scaled;
}

double Input::LeftJoystickX() {
    return FormatJoystickOutput(analogRead(FW_PIN_LJX));
}

double Input::LeftJoystickY() {
    return FormatJoystickOutput(analogRead(FW_PIN_LJY));
}

double Input::RightJoystickX() {
    return FormatJoystickOutput(analogRead(FW_PIN_RJX));
}

double Input::RightJoystickY() {
    return FormatJoystickOutput(analogRead(FW_PIN_RJY));
}

bool Input::LeftJoystickButton(int state) {
    return digitalRead(FW_PIN_LJZ) == state;
}

bool Input::RightJoystickButton(int state) {
    return digitalRead(FW_PIN_RJZ) == state;
}

bool Input::Button1(int state) {
    return digitalRead(FW_PIN_B1) == state;
}

bool Input::Button2(int state) {
    return digitalRead(FW_PIN_B2) == state;
}

bool Input::Button3(int state) {
    return digitalRead(FW_PIN_B3) == state;
}

bool Input::Button4(int state) {
    return digitalRead(FW_PIN_B4) == state;
}
