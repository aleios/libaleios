#pragma once
#ifndef AE_GAME_HPP
#define AE_GAME_HPP

#include <memory>

namespace ae
{
    class Window;
    class Game
    {
    public:
        Game();

    private:
        std::shared_ptr<Window> m_window{nullptr};
    };
}

#endif
