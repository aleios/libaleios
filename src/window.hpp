#pragma once
#ifndef AE_WINDOW_HPP
#define AE_WINDOW_HPP

#include <memory>
#include <cstdint>

namespace ae
{
    class Game;
    class Window
    {
    public:
        Window() = default;
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        virtual ~Window() = default;

        // Input functions
        virtual void CheckEvents() = 0;

        // Screen functions.
        virtual void Clear() = 0;
        virtual void Display() = 0;

        void Cleanup();

        //Window(int width, int height, int bpp);
    protected:
        // Window management implementations.
        virtual void Init() = 0;
        virtual void Destroy() = 0;

    private:
    };  
}

#endif
