file(GLOB_RECURSE SRC_FILES "*.cpp")

idf_component_register(
    SRCS ${SRC_FILES}
    PRIV_REQUIRES spi_flash
    INCLUDE_DIRS "."
)
