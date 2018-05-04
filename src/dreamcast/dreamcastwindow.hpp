#pragma once
#ifndef AE_DETAIL_DREAMCASTWINDOW_HPP
#define AE_DETAIL_DREAMCASTWINDOW_HPP

#include "../window.hpp"

namespace ae
{
    namespace detail
    {
        class DreamcastWindow
            : public Window
        {
        public:
            DreamcastWindow() = default;
            virtual void CheckEvents() final;    
            virtual void Clear() final;
            virtual void Display() final;

            static std::shared_ptr<Window> Create(Game* game)
            {
                return std::make_shared<DreamcastWindow>();
            }
        protected:
            virtual void Init() final;
            virtual void Destroy() final;
        };
    }
}

#endif
