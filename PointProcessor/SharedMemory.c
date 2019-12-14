#include "SharedMemory.h"

#ifdef __linux__
#    include <errno.h>
#    include <fcntl.h>
#    include <sys/stat.h>
#endif

/// <summary>
/// Get or create a shared section of memory by name and 
/// </summary>
/// <param name="memory">Pointer to SharedMemory structure</param>
/// <param name="name">Name of shared memory segment</param>
/// <param name="size">Size of shared memory segment</param>
/// <returns>Status as defined in SharedMemoryStatus</returns>
int32_t get_shared_memory(SharedMemory* memory, const char* const name, size_t size)
{
#ifdef __linux__
    // Create shared memory object
    int shm_fd = shm_open(
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
    // Save the pointer to shared memory
    mem = lmem;
    // Make a shared pointer to the mapping view
    // store the mapping in the destructor lambda and unmap it
    // when no one is using this pointer anymore
    this->mem = std::shared_ptr<T>(static_cast<T*>(lmem),
        [mem_ptr = this->mem, size = size, name = name](T *mem) { 
            if (mem_ptr.use_count() == 0)
            {
                if ((mem != nullptr) && (mem != MAP_FAILED))
                {
                    if (munmap(mem, size) != 0)
                    {
                        perror("Failed to unmap shared memory mapping");
                        exit(errno);
                    }
                }
                // TODO: Open an counter semaphore and only unlink when
                // there are no more users of this memory map
                if (shm_unlink(name.c_str()) == -1)
                {
                    perror("Failed to unlink the shared memory object");
                    exit(errno);
                }
            }
        });
#elif defined _WIN32
    HANDLE lmap = NULL;
    void *lmem = NULL;
    BOOL init = FALSE;
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
    return SHM_SUCCESS;
}

/// <summary>
/// Close a SharedMemory object
/// </summary>
/// <param name="memory">Pointer to Shared memory structure</param>
/// <returns>Status as defined in SharedMemoryStatus</returns>
int32_t close_shared_memory(SharedMemory* memory)
{
#ifdef __linux__
    bool success = true;
    if (memory == NULL || memory->memory == NULL)
    {
        return SHM_NULL;
    }
    if (munmap(mem, size) != 0)
    {
        success = false;
    }
    if (shm_unlink(name.c_str()) == -1)
    {
        success = false;
    }
    if (success)
        return SHM_FAILURE;
    return SHM_SUCCESS;
#elif defined _WIN32
    if (memory == NULL || memory->memory == NULL || memory->handle == NULL)
        return SHM_NULL;
    UnmapViewOfFile(memory->memory);
    CloseHandle(memory->handle);
    return SHM_SUCCESS;
#endif
}
