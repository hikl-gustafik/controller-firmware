#include "haptics.h"

#include "config.h"

#include "esp32-hal-ledc.h"

Haptics::Haptics(uint32_t frequency, uint8_t resolution) :
    m_Frequency(frequency),
    m_Resolution(resolution),
    m_MaxIntensity((1U << resolution) - 1) // (2^resolution) - 1
{
    ledcAttachChannel(FW_PIN_VMOTOR1, m_Frequency, m_Resolution, FW_CHANNEL_VMOTOR1);
    ledcAttachChannel(FW_PIN_VMOTOR2, m_Frequency, m_Resolution, FW_CHANNEL_VMOTOR2);
    ledcAttachChannel(FW_PIN_VMOTOR3, m_Frequency, m_Resolution, FW_CHANNEL_VMOTOR3);
    ledcAttachChannel(FW_PIN_VMOTOR4, m_Frequency, m_Resolution, FW_CHANNEL_VMOTOR4);

    ledcWrite(FW_PIN_VMOTOR1, 0);
    ledcWrite(FW_PIN_VMOTOR2, 0);
    ledcWrite(FW_PIN_VMOTOR3, 0);
    ledcWrite(FW_PIN_VMOTOR4, 0);
}

void Haptics::SetMotorByPin(uint8_t pin, float intensity) {
    if (intensity < 0.0f) intensity *= -1.0f;
    if (intensity > 1.0f) intensity = 1.0f;
    uint32_t rawIntensity = (uint32_t)(intensity * m_MaxIntensity);

    ledcWrite(pin, rawIntensity);
}

void Haptics::SetMotor1(float intensity) {
    SetMotorByPin(FW_PIN_VMOTOR1, intensity);
}

void Haptics::SetMotor2(float intensity) {
    SetMotorByPin(FW_PIN_VMOTOR2, intensity);
}

void Haptics::SetMotor3(float intensity) {
    SetMotorByPin(FW_PIN_VMOTOR3, intensity);
}

void Haptics::SetMotor4(float intensity) {
    SetMotorByPin(FW_PIN_VMOTOR4, intensity);
}

void Haptics::SetAll(float intensity) {
    SetMotor1(intensity);
    SetMotor2(intensity);
    SetMotor3(intensity);
    SetMotor4(intensity);
}
