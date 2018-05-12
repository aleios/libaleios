cmake_minimum_required(VERSION 3.10)
project(libaleios)

#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Require C++11 and disable nonstandard extensions.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set cmake module path
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Options
option(PLATFORM_OPENGL_V1 "Use OpenGL version 1" OFF)

# Setup PC dependencies.
if(PLATFORM_DREAMCAST)

    # Force OpenGL version 1 for dreamcast builds.
    set(PLATFORM_OPENGL_V1)
    add_definitions("-DPLATFORM_OPENGL_V1")
else()
    set(PLATFORM_PC 1)
    add_definitions(-DPLATFORM_PC)

    # Determine OpenGL version to use.
    if(PLATFORM_OPENGL_V1)
        add_definitions("-DPLATFORM_OPENGL_V1")
    else()
        set(PLATFORM_OPENGL_V2 1)
        add_definitions("-DPLATFORM_OPENGL_V2")
    endif()

    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIR})
endif()

# Build source files
add_subdirectory(src)
