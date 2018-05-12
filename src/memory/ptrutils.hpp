#pragma once
#ifndef AE_PTRUTILS_HPP
#define AE_PTRUTILS_HPP

#include <memory>

namespace ae
{
    // Implementation of std::make_unique for c++11 dreamcast builds.
    template<typename T, typename ...Args>
    std::unique_ptr<T> make_unique(Args&& ...args)
    {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
}

#endif