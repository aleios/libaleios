#include "sdlwindow.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

namespace ae
{
    namespace detail
    {
        SDLWindow::~SDLWindow()
        {
            Cleanup();
        }

        void SDLWindow::CheckEvents()
        {
            SDL_Event ev;
            while(SDL_PollEvent(&ev))
            {
                // Handle SDL input events.
            }
        }

        void SDLWindow::Clear()
        {
            glClear(GL_COLOR_BUFFER_BIT);
        }

        void SDLWindow::Display()
        {
            SDL_GL_SwapWindow(m_window);
        }

        void SDLWindow::Init()
        {
            SDL_Init(SDL_INIT_EVERYTHING);

            SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
            //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
            
            //m_window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED)
            m_context = SDL_GL_CreateContext(m_window);
        }

        void SDLWindow::Destroy()
        {
            SDL_Quit();
        }
    }
}
