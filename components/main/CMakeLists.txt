file(GLOB_RECURSE SRC_FILES "*.cpp")

# Remove the files in the "apps/" directory
foreach(file ${SRC_FILES})
    if("${file}" MATCHES "^${CMAKE_SOURCE_DIR}/apps/.*\\.cpp$")
        list(REMOVE_ITEM SRC_FILES ${file})
    endif()
endforeach()

idf_component_register(
    SRCS ${SRC_FILES}
    REQUIRES firmware
    PRIV_REQUIRES spi_flash
    INCLUDE_DIRS "."
)
