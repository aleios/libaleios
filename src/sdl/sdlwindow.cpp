#include "sdlwindow.hpp"

#include <SDL.h>
#include <SDL_opengl.h>

namespace ae
{
    namespace detail
    {
        uint32_t SDLWindow::s_numInstances = 0;

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
                switch (ev.type)
                {
                case SDL_QUIT:
                    Destroy();
                    break;

                // Keyboard
                case SDL_KEYDOWN:
                case SDL_KEYUP:

                    break;

                // Mouse
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                    break;

                case SDL_MOUSEMOTION:
                    break;
                case SDL_MOUSEWHEEL:
                    break;

                // Joystick API
                case SDL_JOYBUTTONDOWN:
                case SDL_JOYBUTTONUP:

                    break;

                case SDL_JOYAXISMOTION:
                
                    break;
                
                case SDL_JOYHATMOTION:

                    break;

                // Game controller
                case SDL_CONTROLLERBUTTONDOWN:
                case SDL_CONTROLLERBUTTONUP:

                    break;
                case SDL_CONTROLLERAXISMOTION:

                    break;
                }
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
            if (s_numInstances == 0)
            {
                SDL_Init(SDL_INIT_EVERYTHING);
            }
            s_numInstances++;

            // Per window initialization.
            SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
            
            m_window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);
            m_context = SDL_GL_CreateContext(m_window);
        }

        void SDLWindow::Destroy()
        {
            SDL_GL_DeleteContext(m_context);
            SDL_DestroyWindow(m_window);

            s_numInstances--;
            if (s_numInstances == 0)
            {
                SDL_Quit();
            }
        }
    }
}
