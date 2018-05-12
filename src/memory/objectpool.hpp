#pragma once
#ifndef AE_OBJECTPOOL_HPP
#define AE_OBJECTPOOL_HPP

#include <vector>
#include <cassert>

namespace ae
{
    class BaseObjectPool
    {
    public:
        explicit BaseObjectPool(size_t objectSize, size_t chunkSize)
            : m_objectSize(objectSize), m_chunkSize(chunkSize), m_currentSize(0), m_currentCapacity(0)
        {
        }

        virtual ~BaseObjectPool()
        {
            for (uint8_t* blk : m_chunks)
            {
                delete[] blk;
            }
        }

        void* Allocate(size_t nptr)
        {
            assert(nptr < m_size);
            return m_chunks[nptr / m_chunkSize] + (nptr % m_chunkSize) * m_objectSize;
        }
        const void* Allocate(size_t nptr) const
        {
            assert(nptr < m_size);
            return m_chunks[nptr / m_chunkSize] + (nptr % m_chunkSize) * m_objectSize;
        }

        void Expand(size_t size)
        {
            if (size >= m_currentSize)
            {
                if (size >= m_currentCapacity)
                {
                    Reserve(size);
                }
                m_currentSize = size;
            }
        }
        void Reserve(size_t size)
        {
            while (m_currentCapacity < size)
            {
                uint8_t* chunk = new uint8_t[m_objectSize * m_chunkSize];
                m_chunks.push_back(chunk);
                m_currentCapacity += m_chunkSize;
            }
        }

        virtual void Destroy() = 0;

    private:
        std::vector<uint8_t*> m_chunks;
        size_t m_objectSize;
        size_t m_chunkSize;

        size_t m_currentSize;
        size_t m_currentCapacity;
    };

    template<typename T, size_t ChunkSize = 2048>
    class ObjectPool
        : BaseObjectPool
    {
    public:
        ObjectPool()
            : BaseObjectPool(sizeof(T), ChunkSize)
        {
        }
        virtual ~ObjectPool() = default;

    private:
    };
}

#endif