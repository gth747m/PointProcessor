#pragma once

#include "SBBLib.h"

namespace sbb
{
    /// <summary>
    /// Shared Memory Pool
    /// </summary>
    class ShmPool
    {
    public:
        /// <summary>
        /// Class Constructor
        /// </summary>
        ShmPool(const char* shm_name);
        /// <summary>
        /// Class Constructor
        /// </summary>
        ShmPool(std::string shm_name);
        /// <summary>
        /// Class Destructor
        /// </summary>
        ~ShmPool();
        /// <summary>
        /// Allocate Memory
        /// </summary>
        /// <param name="n_bytes">Number of bytes to allocate</param>
        /// <returns>Pointer to start of allocated memory region</returns>
        unsigned char* allocate(size_t n_bytes);
        /// <summary>
        /// Deallocate Memory
        /// </summary>
        /// <param name="p">Pointer to start of memory region</param>
        /// <param name="n_bytes">Number of bytes to deallocate</param>
        void deallocate(unsigned char* p, size_t);
    private:
        /// <summary>
        /// Pointer to shared memory
        /// </summary>
        std::unique_ptr<SharedMemory<unsigned char>> shm;
        /// <summary>
        /// Minimum block size per allocation
        /// </summary>
        static const size_t block_size = 32;
    };
}
