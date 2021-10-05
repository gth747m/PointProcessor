#pragma once

#include "PointProcessorLib.h"

namespace point_processor
{
    /// <summary>
    /// Structure for allocating things in shared memory
    /// </summary>
    /// <typeparam name="T">Value type being stored</typeparam>
    template <class T>
    class ShmAllocator
    {
    public:
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef T& reference;
        typedef const T& const_reference;
        typedef T value_type;

        /// <summary>
        /// Default Constructor
        /// </summary>
        /// <returns></returns>
        ShmAllocator() 
        {
        }

        /// <summary>
        /// Copy Constructor
        /// </summary>
        /// <typeparam name="U">Value type being stored</typeparam>
        template<class U> 
        ShmAllocator(const ShmAllocator<U>&) 
        {
        }

        /// <summary>
        /// Equals Operator
        /// </summary>
        /// <typeparam name="U">Value type being stored</typeparam>
        /// <param name=""></param>
        /// <returns>True, all match because this is a stateless allocator</returns>
        template<class U> 
        bool operator==(const ShmAllocator<U>&) const
        {
            return true;
        }

        /// <summary>
        /// Not Equals Operator
        /// </summary>
        /// <typeparam name="U">Value type being stored</typeparam>
        /// <param name=""></param>
        /// <returns>False, all match because this is a stateless allocator</returns>
        template<class U> 
        bool operator!=(const ShmAllocator<U>&) const
        {
            return false;
        }

        /// <summary>
        /// Allocate enough space to store n number of objects
        /// </summary>
        /// <param name="n">Number of objects to allocate space for</param>
        /// <returns>Pointer to the start of allcoated space</returns>
        T* allocate(const size_t n) const
        {
            return reinterpret_cast<T*>(pool->allocate(n * sizeof(T)));
        }

        /// <summary>
        /// Deallocate a previously allocated object
        /// </summary>
        /// <param name="p">Pointer to previously allocated object</param>
        /// <param name="n">Number of objects allocated here</param>
        /// <returns></returns>
        void deallocate(T* const p, size_t n) const
        {
            pool->deallocate(reinterpret_cast<unsigned char*>(p), n * sizeof(T));
        }

    private:
        static ShmPool* pool;
    };

    template<class T>
    ShmPool* ShmAllocator<T>::pool = new ShmPool("SbbShmPool");
}
