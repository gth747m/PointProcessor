#pragma once

#include "SBBLib.h"

namespace sbb
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
        ShmAllocator() noexcept 
        {
        }

        /// <summary>
        /// Copy Constructor
        /// </summary>
        /// <typeparam name="U">Value type being stored</typeparam>
        template<class U> 
        ShmAllocator(const ShmAllocator<U>&) noexcept 
        {
        }

        /// <summary>
        /// Equals Operator
        /// </summary>
        /// <typeparam name="U">Value type being stored</typeparam>
        /// <param name=""></param>
        /// <returns>True, all match because this is a stateless allocator</returns>
        template<class U> 
        bool operator==(const ShmAllocator<U>&) const noexcept
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
        bool operator!=(const ShmAllocator<U>&) const noexcept
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
            if (n == 0)
            {
                return nullptr;
            }
            if (n > static_cast<size_t>(-1) / sizeof(T))
            {
                throw std::bad_array_new_length();
            }
            void* const pv = malloc(n * sizeof(T));
            if (!pv)
            {
                throw std::bad_alloc();
            }
            return static_cast<T*>(pv);
        }

        /// <summary>
        /// Deallocate a previously allocated object
        /// </summary>
        /// <param name="p">Pointer to previously allocated object</param>
        /// <param name=""></param>
        /// <returns></returns>
        void deallocate(T* const p, size_t) const noexcept
        {
            free(p);
        }
        
    private:
        static ShmPool* pool;
    };
}
