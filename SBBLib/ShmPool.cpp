#include "SBBLib.h"

namespace sbb
{
    /// <summary>
    /// Class Constructor
    /// </summary>
    ShmPool::ShmPool(const char* shm_name)
    {
        shm = std::make_unique<SharedMemory<unsigned char, mem_size>>(shm_name);
        mutex = std::make_unique<NamedMutex>(std::string("Lock") + shm_name);
    }

    /// <summary>
    /// Class Constructor
    /// </summary>
    ShmPool::ShmPool(std::string shm_name) : 
        ShmPool(shm_name.c_str()) {}

    /// <summary>
    /// Class Destructor
    /// </summary>
    ShmPool::~ShmPool()
    {

    }

    /// <summary>
    /// Allocate Memory
    /// </summary>
    /// <param name="n_bytes">Number of bytes to allocate</param>
    /// <returns>Pointer to start of allocated memory region</returns>
    unsigned char* ShmPool::allocate(size_t n_bytes)
    {
        if (n_bytes == 0)
        {
            return nullptr;
        }
        void* const p = malloc(n_bytes);
        if (!p)
        {
            throw std::bad_alloc();
        }
        return static_cast<unsigned char*>(p);
    }

    /// <summary>
    /// Deallocate Memory
    /// </summary>
    /// <param name="p">Pointer to start of memory region</param>
    /// <param name="n_bytes">Number of bytes to deallocate</param>
    void ShmPool::deallocate(unsigned char* const p, size_t)
    {
        if (p)
        {
            free(p);
        }
    }
}