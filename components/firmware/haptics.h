#pragma once

#include <cstdint>

class Haptics {
public:
    Haptics(uint32_t frequency = 5000, uint8_t resolution = 8);

    /**
     * @brief Set vibration intensity of motor 1.
     *
     * Intensity is automatically absoluted and capped at 1.0.
     *
     * @param intensity Intensity of the motor (0.0 - 1.0)
     */
    void SetMotor1(float intensity);

    /**
     * @brief Set vibration intensity of motor 2.
     *
     * Intensity is automatically absoluted and capped at 1.0.
     *
     * @param intensity Intensity of the motor (0.0 - 1.0)
     */
    void SetMotor2(float intensity);

    /**
     * @brief Set vibration intensity of motor 3.
     *
     * Intensity is automatically absoluted and capped at 1.0.
     *
     * @param intensity Intensity of the motor (0.0 - 1.0)
     */
    void SetMotor3(float intensity);

    /**
     * @brief Set vibration intensity of motor 4.
     *
     * Intensity is automatically absoluted and capped at 1.0.
     *
     * @param intensity Intensity of the motor (0.0 - 1.0)
     */
    void SetMotor4(float intensity);

    /**
     * @brief Set vibration intensity of all motors.
     *
     * Intensity is automatically absoluted and capped at 1.0.
     *
     * @param intensity Intensity of the motors (0.0 - 1.0)
     */
    void SetAll(float intensity);
private:
    uint32_t m_Frequency;
    uint8_t m_Resolution;

    uint32_t m_MaxIntensity;

    void SetMotorByPin(uint8_t pin, float intensity);
};
