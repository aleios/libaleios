# All platform sources
set(SRC
    game.hpp
    game.cpp

    window.hpp
    window.cpp

    renderer/renderer.hpp

    ecs/component.hpp
    ecs/entity.hpp
    ecs/world.hpp
)

# Platform specific sources
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

# Static library target
add_library(${PROJECT_NAME} STATIC ${SRC})

# Platform specific library linking.
if(PLATFORM_DREAMCAST)
    target_link_libraries(${PROJECT_NAME} GL tremor kosutils)
else()
    target_link_libraries(${PROJECT_NAME} SDL2 GL tremor)
endif()

# Library install target
if(PLATFORM_DREAMCAST)
    #install(TARGETS ${PROJECT_NAME}
    #    RUNTIME DESTINATION $ENV{KOS_BASE}/bin
    #    LIBRARY DESTINATION $ENV{KOS_BASE}/lib
    #    ARCHIVE DESTINATION $ENV{KOS_BASE}/lib)
else()
    install(TARGETS ${PROJECT_NAME}
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
            )
endif()
