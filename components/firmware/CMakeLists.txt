file(GLOB_RECURSE SRC_FILES "*.cpp")

idf_component_register(
    SRCS ${SRC_FILES}
    REQUIRES arduino Adafruit_SSD1306
    PRIV_REQUIRES spi_flash
    INCLUDE_DIRS "."
)
