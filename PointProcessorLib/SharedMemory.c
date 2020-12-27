#include "SharedMemory.h"

#include <stdbool.h>

#ifdef __linux__
#    include <unistd.h>
#    include <errno.h>
#    include <fcntl.h>
#    include <sys/mman.h>
#    include <sys/stat.h>
#endif

/// <summary>
/// Get or create a shared section of memory by name and 
/// </summary>
/// <param name="memory">Pointer to SharedMemory structure</param>
/// <param name="name">Name of shared memory segment</param>
/// <param name="size">Size of shared memory segment</param>
/// <returns>Status as defined in SharedMemoryStatus</returns>
POINTLIB_API int32_t shared_memory_get(
    SharedMemory*     memory, 
    const char* const name, 
    size_t size)
{
#ifdef __linux__
    bool init = false;
    int shm_fd = -1;
    if (memory == NULL)
    {
        return SHM_NULL;
    }
    // Create shared memory object
    shm_fd = shm_open(
        name, 
        O_RDWR | O_CREAT | O_EXCL, 
        S_IRUSR | S_IWUSR);
    // Couldn't create shared memory object
    if (shm_fd == -1)
    {
        // Couldn't create it because it already exists
        if (errno == EEXIST)
        {
            // Get the preexisting file descriptor
            shm_fd = shm_open(
                name, 
                O_RDWR, 
                S_IRUSR | S_IWUSR);
            if (shm_fd == -1)
            {
                return SHM_FAILURE;
            }
        }
        // OH NO, WTF HAPPENED?!?!?!
        else
        {
            return SHM_FAILURE;
        }
    }
    // Created shared memory object (first one to do so)
    else
    {
        init = true;
        // Resize shared region
        if (ftruncate(shm_fd, size) == -1)
        {
            return SHM_FAILURE;
        }
    }
    // Map shared memory object
    void *lmem = mmap(
        NULL, 
        size, 
        PROT_READ | PROT_WRITE,
        MAP_SHARED, 
        shm_fd, 
        0);
    // Mapping failed
    if (lmem == MAP_FAILED)
    {
        return SHM_FAILURE;
    }
    // Close the shared memory object file descriptor
    // This does not free the memory mapped file
    close(shm_fd);
    // Save the name of the mapped region
    if (strlen(name) > (SHM_NAME_LEN - 1))
    {
        return SHM_NAME_TOO_LONG;
    }
    memset(memory->name, 0, SHM_NAME_LEN);
    strncpy(memory->name, name, SHM_NAME_LEN - 1);
    // Save the pointer to shared memory
    memory->memory = lmem;
    // Save the size of the mapped region
    memory->size = size;
#elif defined _WIN32
    HANDLE lmap = NULL;
    void *lmem = NULL;
    BOOL init = FALSE;
    if (memory == NULL)
    {
        return SHM_NULL;
    }
    lmap = CreateFileMappingA(
        INVALID_HANDLE_VALUE,   // use paging file
        NULL,                   // default security
        PAGE_READWRITE,         // read/write access
        0,                      // size: high 32-bits
        (DWORD)size,            // size: low 32-bits
        name);                  // name of the map
    // The first process to attach initializes memory
    init = (GetLastError() != ERROR_ALREADY_EXISTS);
    if (lmap == NULL)
    {
        return SHM_FAILURE;
    }
    lmem = MapViewOfFile(
        lmap,                   // object to map a view of
        FILE_MAP_ALL_ACCESS,    // read/write access
        0,                      // high offset: map from beginning
        0,                      // low offset: map from beginning
        0);                     // default: map entire file
    if (lmem == NULL)
    {
        return SHM_FAILURE;
    }
    // Initialize memory if this is the first process
    if (init)
    {
        ZeroMemory(lmem, size);
    }
    // Save the name of the mapped region
    if (strlen(name) > (SHM_NAME_LEN - 1))
    {
        return SHM_NAME_TOO_LONG;
    }
    memset(memory->name, 0, SHM_NAME_LEN);
    strncpy_s(memory->name, SHM_NAME_LEN, name, SHM_NAME_LEN - 1);
    // Save pointer to mapped memory
    memory->memory = lmem;
    // Save the size of the mapped region
    memory->size = size;
    // Save the handle to the file mapping
    memory->handle = lmap;
#endif
    // We created this shared memory
    if (init) 
    {
        return SHM_CREATED;
    }
    // We obtained an existing copy
    else 
    {
        return SHM_SUCCESS;
    }
}

/// <summary>
/// Close a SharedMemory object
/// </summary>
/// <param name="memory">Pointer to Shared memory structure</param>
/// <returns>Status as defined in SharedMemoryStatus</returns>
POINTLIB_API int32_t shared_memory_close(
    SharedMemory* memory)
{
#ifdef __linux__
    bool success = true;
    if (memory == NULL || memory->memory == NULL)
    {
        return SHM_NULL;
    }
    if (munmap(memory->memory, memory->size) != 0)
    {
        success = false;
    }
    if (shm_unlink(memory->name) == -1)
    {
        success = false;
    }
    if (success)
        return SHM_SUCCESS;
    return SHM_FAILURE;
#elif defined _WIN32
    if (memory == NULL || memory->memory == NULL || memory->handle == NULL)
        return SHM_NULL;
    FlushViewOfFile(memory->memory, memory->size);
    UnmapViewOfFile(memory->memory);
    CloseHandle(memory->handle);
    return SHM_SUCCESS;
#endif
}
