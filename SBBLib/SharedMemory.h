#pragma once

#include "SBBLib.h"

namespace sbb
{
    class SharedMemoryException : public std::exception
    {
    public:
        SharedMemoryException(const char* msg);
        SharedMemoryException(std::string msg);
        SharedMemoryException(std::stringstream& msg);
        virtual const char* what() const throw();
    protected:
        std::string error_message;
    };

    template <typename T, size_t n = 1>
    class SharedMemory
    {
    public:
        /// <summary>
        /// Created a shared memory ojbect
        /// </summary>
        /// <typeparam name="T">Type of object to be stored in shared memory</typeparam>
        SharedMemory(const char* name) :
            name(name),
            shm_size(n * sizeof(T)),
            shm_ptr(nullptr)
    #if defined _WIN32
            ,handle(nullptr)
    #endif
        {
    #ifdef __linux__
            bool init = false;
            int shm_fd = -1;
            // Create shared memory object
            shm_fd = shm_open(
                this->name.c_str(), 
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
                        std::stringstream ss;
                        ss << "Failed to create SharedMemory '"
                            << this->name << "'.";
                        throw SharedMemoryException(ss);
                    }
                }
                // OH NO, WTF HAPPENED?!?!?!
                else
                {
                    std::stringstream ss;
                    ss << "Failed to create SharedMemory '"
                        << this->name << "'.";
                    throw SharedMemoryException(ss);
                }
            }
            // Created shared memory object (first one to do so)
            else
            {
                init = true;
                // Resize shared region
                if (ftruncate(shm_fd, this->shm_size) == -1)
                {
                    std::stringstream ss;
                    ss << "Failed to size SharedMemory '"
                        << this->name << "'.";
                    throw SharedMemoryException(ss);
                }
            }
            // Map shared memory object
            this->shm_ptr = (T*)mmap(
                NULL, 
                this->shm_size, 
                PROT_READ | PROT_WRITE,
                MAP_SHARED, 
                shm_fd, 
                0);
            // Mapping failed
            if (this->shm_ptr == MAP_FAILED)
            {
                std::stringstream ss;
                ss << "Failed to map SharedMemory '"
                    << this->name << "'.";
                throw SharedMemoryException(ss);
            }
            // Close the shared memory object file descriptor
            // This does not free the memory mapped file
            close(shm_fd);
            // Zero out memory if this is the first instance to be created
            if (init)
            {
                memset(this->shm_ptr, 0, this->shm_size);
            }
    #elif defined _WIN32
            BOOL init = FALSE;
            // Save the handle to the file mapping
            // TODO: Add support for 64bit size
            this->handle = CreateFileMappingA(
                INVALID_HANDLE_VALUE,   // use paging file
                NULL,                   // default security
                PAGE_READWRITE,         // read/write access
                0,                      // size: high 32-bits
                (DWORD)this->shm_size,  // size: low 32-bits
                this->name.c_str());    // name of the map
            // The first process to attach initializes memory
            init = (GetLastError() != ERROR_ALREADY_EXISTS);
            if (this->handle == nullptr)
            {
                std::stringstream ss;
                ss << "Failed to create SharedMemory '"
                    << this->name << "'.";
                throw SharedMemoryException(ss);
            }
            // TODO: store typeof and throw exception if typeof doesn't match
            // Save pointer to mapped memory
            this->shm_ptr = (T*)MapViewOfFile(
                this->handle,           // object to map a view of
                FILE_MAP_ALL_ACCESS,    // read/write access
                0,                      // high offset: map from beginning
                0,                      // low offset: map from beginning
                0);                     // default: map entire file
            if (this->shm_ptr == nullptr)
            {
                std::stringstream ss;
                ss << "Failed to map a view to SharedMemory '"
                    << this->name << "'.";
                throw SharedMemoryException(ss);
            }
            // Initialize memory if this is the first process
            if (init)
            {
                ZeroMemory(this->shm_ptr, this->shm_size);
            }
    #endif
        }
        /// <summary>
        /// Created a shared memory ojbect
        /// </summary>
        /// <typeparam name="T">Type of object to be stored in shared memory</typeparam>
        SharedMemory(std::string name) :
            SharedMemory(name.c_str()) {}
        /// <summary>
        /// Destructor, if the handle to shared memory isn't released it
        /// releases it like release() but noexcept
        /// </summary>
        virtual ~SharedMemory()
        {
            if (this->shm_ptr != nullptr)
            {
    #ifdef __linux__
                munmap(this->shm_ptr, this->shm_size);
                shm_unlink(this->name.c_str());
    #elif defined _WIN32
                if (this->shm_ptr != nullptr)
                {
                    FlushViewOfFile(this->shm_ptr, this->shm_size);
                    UnmapViewOfFile(this->shm_ptr);
                }
                if (this->handle != nullptr)
                {
                    CloseHandle(this->handle);
                }
    #endif
            }
        }
        /// <summary>
        /// Get the pointer to object in shared memory
        /// </summary>
        /// <returns>Pointer to object stored in shared memory</returns>
        T* get() const { return this->shm_ptr; }
        /// <summary>
        /// Close handle to shared memory
        /// </summary>
        void release()
        {
    #ifdef __linux__
            if (this->shm_ptr == nullptr)
            {
                std::stringstream ss;
                ss << "Failed to release SharedMemory '"
                    << this->name << "', it was a null pointer.";
                throw SharedMemoryException(ss);
            }
            if (munmap(this->shm_ptr, this->shm_size) != 0)
            {
                std::stringstream ss;
                ss << "Failed to release SharedMemory '"
                    << this->name << "', failed to unmap view of file.";
                throw SharedMemoryException(ss);
            }
            if (shm_unlink(this->name.c_str()) == -1)
            {
                std::stringstream ss;
                ss << "Failed to release SharedMemory '"
                    << this->name << "', failed to unlink shared memory.";
                throw SharedMemoryException(ss);
            }
    #elif defined _WIN32
            if (this->shm_ptr == nullptr || this->handle == nullptr)
            {
                std::stringstream ss;
                ss << "Failed to release SharedMemory '"
                    << this->name << "', it was a null pointer.";
                throw SharedMemoryException(ss);
            }
            if (FlushViewOfFile(this->shm_ptr, this->shm_size) != TRUE)
            {
                std::stringstream ss;
                ss << "Failed to release SharedMemory '"
                    << this->name << "', failed to flush view of file.";
                throw SharedMemoryException(ss);
            }
            if (UnmapViewOfFile(this->shm_ptr) != TRUE)
            {
                std::stringstream ss;
                ss << "Failed to release SharedMemory '"
                    << this->name << "', failed to unmap view of file.";
                throw SharedMemoryException(ss);
            }
            if (CloseHandle(this->handle) != TRUE)
            {
                std::stringstream ss;
                ss << "Failed to release SharedMemory '"
                    << this->name << "', failed to release handle.";
                throw SharedMemoryException(ss);
            }
    #endif
        }
    protected:
        /// <summary>
        /// Name of the shared memory
        /// </summary>
        std::string name;
        /// <summary>
        /// Size of the shared memory
        /// </summary>
        size_t shm_size;
        /// <summary>
        /// Pointer to the start of shared memory
        /// </summary>
        T* shm_ptr;
    #ifdef _WIN32
        /// <summary>
        /// Handle to shared memory
        /// </summary>
        HANDLE handle;
    #endif
    private:
    };
}