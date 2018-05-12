#include "game.hpp"

#ifdef PLATFORM_DREAMCAST
    #include "dreamcast/dreamcastwindow.hpp"
    namespace ae { typedef detail::DreamcastWindow SystemWindow; }
#else
    #include "sdl/sdlwindow.hpp"
    namespace ae { typedef detail::SDLWindow SystemWindow; }
#endif

#include "ecs/component.hpp"

namespace ae
{
    Game::Game()
    {
    }

    int Game::Run()
    {
        // Close previous window if relevant.
        if (m_window)
        {
            m_window->Cleanup();
            m_window.reset();
        }

        // Create window with specified settings.
        m_window = SystemWindow::Create(this);

        // Main loop
        while (1)
        {
            // Check for inputs.
            m_window->CheckEvents();
        }

        // Cleanup resources.
        if (m_window)
        {
            m_window->Cleanup();
            m_window.reset();
        }

        return 0;
    }
}
