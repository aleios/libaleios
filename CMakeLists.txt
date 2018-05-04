project(libaleios)

#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Dreamcast")
    set(PLATFORM_DREAMCAST 1)
    add_definitions(-DPLATFORM_DREAMCAST)
else()
    set(PLATFORM_PC 1)
    add_definitions(-DPLATFORM_PC)
endif()



# Build source files
add_subdirectory(src)
