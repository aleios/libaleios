#pragma once
#ifndef AE_DETAIL_DREAMCASTWINDOW_HPP
#define AE_DETAIL_DREAMCASTWINDOW_HPP

#include "../window.hpp"
#include "../memory/ptrutils.hpp"

namespace ae
{
    namespace detail
    {
        class DreamcastWindow
            : public Window
        {
        public:
            DreamcastWindow() = default;
            DreamcastWindow(int width, int height, int bpp);

            virtual void CheckEvents() final;    
            virtual void Clear() final;
            virtual void Display() final;

            static std::unique_ptr<Window> Create(Game* game)
            {
                return ae::make_unique<DreamcastWindow>();
            }
        protected:
            virtual void Init() final;
            virtual void Destroy() final;
        };
    }
}

#endif
