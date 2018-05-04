#pragma once
#ifndef AE_DETAIL_SDLWINDOW_HPP
#define AE_DETAIL_SDLWINDOW_HPP

#include "../window.hpp"

struct SDL_Window;
namespace ae
{
    namespace detail
    {
        class SDLWindow
            : public Window
        {
        public:
            SDLWindow() = default;
            ~SDLWindow();

            virtual void CheckEvents() final;

            virtual void Clear() final;
            virtual void Display() final;

            static std::shared_ptr<Window> Create(Game* game)
            {
                return std::make_shared<SDLWindow>();
            }
        protected:
            virtual void Init() final;
            virtual void Destroy() final;
        private:
            SDL_Window* m_window{nullptr};
            void* m_context{nullptr};
        };
    }
}

#endif
