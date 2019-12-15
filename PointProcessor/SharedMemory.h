#pragma once

#include <stdint.h>
#include <string.h>

#ifdef _WIN32
#    define WIN32_LEAN_AND_MEAN
#    include <Windows.h>
#endif

/// <summary>
/// Max name length for shared memory
/// </summary>
#define SHM_NAME_LEN 32

/// <summary>
/// Shared memory structure
/// </summary>
typedef struct SharedMemory
{
    /// <summary>
    /// Name of this shared memory region
    /// </summary>
    char name[SHM_NAME_LEN];
    /// <summary>
    /// Pointer to shared memory
    /// </summary>
    void* memory;
    /// <summary>
    /// Size of shared memory region
    /// </summary>
    size_t size;
#ifdef _WIN32
    /// <summary>
    /// Handle to shared memory
    /// </summary>
    HANDLE handle;
#endif
} SharedMemory;

/// <summary>
/// Possible SharedMemory statuses
/// </summary>
enum SharedMemoryStatus
{
    /// <summary>
    /// SharedMemory name too long
    /// </summary>
    SHM_NAME_TOO_LONG = -3,
    /// <summary>
    /// SharedMemory pointer was null
    /// </summary>
    SHM_NULL = -2,
    /// <summary>
    /// General failure
    /// </summary>
    SHM_FAILURE = -1,
    /// <summary>
    /// Shared memory operation successful
    /// </summary>
    SHM_SUCCESS = 0,
    /// <summary>
    /// Shared memory didn't exist, so it was created
    /// </summary>
    SHM_CREATED = 1
};

/// <summary>
/// Get or create a shared section of memory by name and 
/// </summary>
/// <param name="memory">Pointer to SharedMemory structure</param>
/// <param name="name">Name of shared memory segment</param>
/// <param name="size">Size of shared memory segment</param>
/// <returns>Status as defined in SharedMemoryStatus</returns>
int32_t get_shared_memory(SharedMemory* memory, const char* const name, size_t size);

/// <summary>
/// Close a SharedMemory object
/// </summary>
/// <param name="memory">Pointer to Shared memory structure</param>
/// <returns>Status as defined in SharedMemoryStatus</returns>
int32_t close_shared_memory(SharedMemory* memory);
