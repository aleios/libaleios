#pragma once
#ifndef AE_ENTITYSYSTEM_HPP
#define AE_ENTITYSYSTEM_HPP

#include <vector>

namespace ae
{
    namespace detail
    {
        class BaseEntitySystem
        {
        public:
            BaseEntitySystem();

            virtual ~BaseEntitySystem() = 0;

            World* GetWorld() const { return m_world; }

            const std::vector<Entity>& GetEntities() const { return m_entities; }
        private:
            friend class World;
            void SetWorld(World& world) { m_world = &world; }
            World* m_world{ nullptr };

            // Entity functions
            void AddEntity(Entity& entity);
            void RemoveEntity(Entity& entity);

            std::vector<Entity> m_entities;
        };
    }

    class Entity;
    class World;
    template<class RequiredList>
    class EntitySystem
        : public detail::BaseEntitySystem
    {
    public:
        EntitySystem()
            : detail::BaseEntitySystem{}
        {
        }

        virtual void FixedUpdate() {}
        virtual void Update(float dt) = 0;
        
        
    private:
        
    };
}

#endif