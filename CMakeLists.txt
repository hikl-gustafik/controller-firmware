cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_STANDARD 17)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

set(EXTRA_COMPONENT_DIRS src)

project(myproj)
