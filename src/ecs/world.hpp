#pragma once
#ifndef WORLD_HPP
#define WORLD_HPP

#include "entity.hpp"
#include "../memory/objectpool.hpp"

namespace ae
{
    class World
    {
    public:
        Entity CreateEntity()
        {
            std::size_t index, version;
            
            // Check for free indices. Create one if none.
            if (m_entityFreeList.empty())
            {
                
            }
        }
        void DestroyEntity(Entity::ID entity);
    private:

        template<typename T>
        ObjectPool<T>* GetComponentPool()
        {

        }

        // Entity component functions.
        template<typename T, typename ...Args>
        T& CreateComponent(Entity& entity, Args... args)
        {
            //detail::GetComponentIndex<T>();
            ObjectPool<T>* pool = GetComponentPool<T>();
            ::new(pool->Allocate(entity.GetID().GetIndex())) T(std::forward<Args>(args)...);


        }

        template<typename T>
        void RemoveComponent(Entity& entity);

        template<typename T>
        bool HasComponent(Entity& entity) const;

        template<typename T>
        T& GetComponent(Entity& entity) const;

        std::vector<BaseObjectPool*> m_componentPools;
        std::vector<std::size_t> m_entityVersionList, m_entityFreeList;
    };
}

#endif