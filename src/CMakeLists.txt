set(SRC
    game.hpp
    game.cpp

    window.hpp
    window.cpp    
)

if(PLATFORM_DREAMCAST)
    set(SRC ${SRC}
        dreamcast/dreamcastwindow.hpp
        dreamcast/dreamcastwindow.cpp    
    )
else()
    set(SRC ${SRC}
        sdl/sdlwindow.hpp
        sdl/sdlwindow.cpp    
    )
endif()

add_library(${PROJECT_NAME} STATIC ${SRC})

if(PLATFORM_DREAMCAST)
    target_link_libraries(${PROJECT_NAME} GL tremor kosutils)
else()
    target_link_libraries(${PROJECT_NAME} SDL2 GL tremor)
endif()

# Library install target
if(PLATFORM_DREAMCAST)
    #install(TARGETS ${PROJECT_NAME}
    #    RUNTIME $ENV{KOS_BASE}/bin
    #    LIBRARY $ENV{KOS_BASE}/lib
    #    ARCHIVE $ENV{KOS_BASE}/lib)
else()
    install(TARGETS ${PROJECT_NAME})
endif()
