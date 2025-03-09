#pragma once

#include "ssd1306.h"
#include "font8x8_basic.h"

class Display {
public:
    Display();
    ~Display();

    inline SSD1306_t& getDevice() { return m_Device; }

    inline void ClearScreen(bool invert = false) {
        ssd1306_clear_screen(&m_Device, invert);
    }
    inline void SetContrast(int contrast) {
        ssd1306_contrast(&m_Device, contrast);
    }
private:
    SSD1306_t m_Device;
};
