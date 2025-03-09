#include "display.h"
#include "debug.h"
#include "ssd1306.h"

Display::Display() {

#if CONFIG_I2C_INTERFACE
    DEBUG("Starting display as I2C...");
    i2c_master_init(
        &m_Device,
        CONFIG_SDA_GPIO,
        CONFIG_SCL_GPIO,
        CONFIG_RESET_GPIO
    );
#endif
#if CONFIG_SPI_INTERFACE
    ASSERT(false, "SPI display interface not implemented.");
#endif

#if CONFIG_FLIP
    DEBUG("Display flipped.");
    m_Device._flip = true;
#endif

#if CONFIG_SSD1306_128x64
    DEBUG("Display size: 128x64");
	ssd1306_init(&m_Device, 128, 64);
#endif
#if CONFIG_SSD1306_128x32
    DEBUG("Display size: 128x32");
	ssd1306_init(&m_Device, 128, 32);
#endif

    ClearScreen();
    SetContrast(0xff);

}

Display::~Display() {
}
