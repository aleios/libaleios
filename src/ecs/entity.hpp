#pragma once
#ifndef AE_ENTITY_HPP
#define AE_ENTITY_HPP

#include "component.hpp"

#include <type_traits>
#include <cstdint>

namespace ae
{
    class World;
    class Entity
    {
    public:
        struct ID
        {
            friend class World;

            ID()
                : m_index(0)
            {
            }
            explicit ID(size_t id)
                : m_index(id)
            {
            }

            bool operator==(const ID& other) const { return m_index == other.m_index && m_version == other.m_version; }
            bool operator!=(const ID& other) const { return !operator==(other); }
            bool operator<(const ID& other) const { return m_index < other.m_index && m_version < other.m_version; }

            size_t GetIndex() const { return m_index; }
            size_t GetVersion() const { return m_version; }
        private:
            size_t m_index, m_version;
        };
        static const ID INVALID;

        Entity() = default;
        Entity(World* world, ID id)
            : m_world(world), m_index(id)
        {
        }
        Entity(const Entity&) = default;
        ~Entity() = default;

        template<typename T, typename... Args>
        T& AddComponent(Args&& ...args)
        {
            static_assert(std::is_base_of<Component, T>(), "T is not a Component.");
            return m_world->CreateComponent(*this, std::forward<Args>(args)...);
        }

        template<typename T>
        void RemoveComponent()
        {
            static_assert(std::is_base_of<Component, T>(), "T is not a Component.");
            m_world->RemoveComponent<T>(*this);
        }

        template<typename T, typename = typename std::enable_if<!std::is_const<T>::value>::type>
        T& GetComponent()
        {
            static_assert(std::is_base_of<Component, T>(), "T is not a Component.");
            return m_world->GetComponent<T>(*this);
        }

        template<typename T, typename = typename std::enable_if<std::is_const<T>::value>::type>
        const T& GetComponent() const
        {
            static_assert(std::is_base_of<Component, T>(), "T is not a Component.");
            return m_world->GetComponent<T>(*this);
        }

        template<typename T>
        bool HasComponent() const
        {
            static_assert(std::is_base_of<Component, T>(), "T is not a Component.");
            return m_world->HasComponent<T>(*this);
        }

        void Destroy();
        void Invalidate();
        bool IsValid() const;

        Entity::ID GetID() const;

        World* GetWorld() const { return m_world; }

        detail::ComponentMask GetComponentMask() const;
    private:
        World* m_world{ nullptr };
        Entity::ID m_index{ INVALID };
    };

    // Initialize static INVALID with default constructor. INVALID = 0.
    const Entity::ID Entity::INVALID;
}

#endif