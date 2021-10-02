#pragma once

#include <stdlib.h>
#include <new>
#include <memory>

template <class T>
struct ShmAllocator
{
    typedef T value_type;
    ShmAllocator() noexcept {}

    // A converting copy constructor
    template<class U> ShmAllocator(const ShmAllocator<U>&) noexcept {}

    template<class U> bool operator==(const ShmAllocator<U>&) const noexcept 
    {
        return true;
    }

    template<class U> bool operator!=(const ShmAllocator<U>&) const noexcept
    {
        return false;
    }

    T* allocate(const size_t n) const;

    void deallocate(T* const p, size_t) const noexcept;
};

template<class T>
T* ShmAllocator<T>::allocate(const size_t n) const
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

template<class T>
void ShmAllocator<T>::deallocate(T * const p, size_t) const noexcept
{
    free(p);
}
