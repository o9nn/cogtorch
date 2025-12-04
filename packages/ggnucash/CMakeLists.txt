cmake_minimum_required(VERSION 3.10)
project(ggnucash VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Library sources
set(GGNUCASH_SOURCES
    src/virtual-device.cpp
    src/llama-coprocessor-driver.cpp
)

# Build shared library
add_library(ggnucash SHARED ${GGNUCASH_SOURCES})

# Build static library
add_library(ggnucash_static STATIC ${GGNUCASH_SOURCES})
set_target_properties(ggnucash_static PROPERTIES OUTPUT_NAME ggnucash)

# Set library properties
set_target_properties(ggnucash PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER "include/ggnucash/vdev/virtual-device.h;include/ggnucash/vdev/llama-coprocessor-driver.h"
)

# Example executable
add_executable(device-admin examples/device-admin.cpp)
target_link_libraries(device-admin ggnucash)

# Installation rules
install(TARGETS ggnucash ggnucash_static device-admin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/ggnucash/vdev
)

# Install all headers
install(DIRECTORY include/ggnucash
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

# Print build information
message(STATUS "ggnucash configuration:")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  Install prefix: ${CMAKE_INSTALL_PREFIX}")
