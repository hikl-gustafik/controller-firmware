#pragma once

#include <cstdint>

class Haptics {
public:
    Haptics(uint32_t frequency = 5000, uint8_t resolution = 8);

    void SetMotor1(uint8_t intensity);
    void SetMotor2(uint8_t intensity);
    void SetMotor3(uint8_t intensity);
    void SetMotor4(uint8_t intensity);
    void SetAll(uint8_t intensity);
};
