#include "haptics.h"

#include "config.h"

#include "esp32-hal-ledc.h"

Haptics::Haptics(uint32_t frequency, uint8_t resolution) {
    ledcAttachChannel(FW_PIN_VMOTOR1, 5000, 8, FW_CHANNEL_VMOTOR1);
    ledcAttachChannel(FW_PIN_VMOTOR2, 5000, 8, FW_CHANNEL_VMOTOR2);
    ledcAttachChannel(FW_PIN_VMOTOR3, 5000, 8, FW_CHANNEL_VMOTOR3);
    ledcAttachChannel(FW_PIN_VMOTOR4, 5000, 8, FW_CHANNEL_VMOTOR4);

    ledcWrite(FW_PIN_VMOTOR1, 0);
    ledcWrite(FW_PIN_VMOTOR2, 0);
    ledcWrite(FW_PIN_VMOTOR3, 0);
    ledcWrite(FW_PIN_VMOTOR4, 0);
}

void Haptics::SetMotor1(uint8_t intensity) {
    ledcWrite(FW_PIN_VMOTOR1, intensity);
}

void Haptics::SetMotor2(uint8_t intensity) {
    ledcWrite(FW_PIN_VMOTOR2, intensity);
}

void Haptics::SetMotor3(uint8_t intensity) {
    ledcWrite(FW_PIN_VMOTOR3, intensity);
}

void Haptics::SetMotor4(uint8_t intensity) {
    ledcWrite(FW_PIN_VMOTOR4, intensity);
}

void Haptics::SetAll(uint8_t intensity) {
    SetMotor1(intensity);
    SetMotor2(intensity);
    SetMotor3(intensity);
    SetMotor4(intensity);
}
