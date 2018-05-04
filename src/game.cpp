#include "game.hpp"

#ifdef PLATFORM_DREAMCAST
    #include "dreamcast/dreamcastwindow.hpp"
    namespace ae { typedef detail::DreamcastWindow SystemWindow; }
#else
    #include "sdl/sdlwindow.hpp"
    namespace ae { typedef detail::SDLWindow SystemWindow; }
#endif

namespace ae
{
    Game::Game()
    {
        std::shared_ptr<Window> window;
        window = SystemWindow::Create(this);
    }
}
