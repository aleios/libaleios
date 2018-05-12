#pragma once
#ifndef AE_COMPONENT_HPP
#define AE_COMPONENT_HPP

#include <bitset>
#include "../logger.hpp"

namespace ae
{
    class Entity;
    namespace detail
    {
        static const std::size_t MAX_COMPONENTS = 64;
        using ComponentMask = std::bitset<MAX_COMPONENTS>;

        inline std::size_t& GetComponentCounter()
        {
            static std::size_t counter = 0;
            return counter;
        }

        template<typename T>
        std::size_t GetComponentIndex()
        {
            static std::size_t index = GetComponentCounter()++;
            AE_ASSERTF(index < MAX_COMPONENTS, "Error: Too many components registered. MAX: %d", MAX_COMPONENTS);
            return index;
        }

        template<typename T>
        inline auto BuildComponentMask() -> typename std::enable_if<!std::is_same<T, Entity>::value, ComponentMask>::type
        {
            static_assert(std::is_base_of<Component, T>(), "T is not a Component. Must inherit from Component class.");
            return { (1ULL << GetComponentIndex<T>()) };
        }

        // Match case for when Entity specified instead of component.
        template<typename T>
        inline auto BuildComponentMask() -> typename std::enable_if<std::is_same<T, Entity>::value, ComponentMask>::type
        {
            return { 0 };
        }

        // Variadic for multiple components
        template<typename C1, typename C2, typename ...CX>
        inline auto BuildComponentMask() -> typename std::enable_if<!std::is_same<C1, Entity>::value, ComponentMask>::type
        {
            return BuildComponentMask<C1>() | BuildComponentMask<C2, CX...>();
        }
    }

    class Component
    {
    public:
        virtual ~Component() {}
    };
}

#endif