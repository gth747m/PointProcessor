#include "NamedMutex.h"

#include <cstdint>
#include <iostream>
#include <sstream>

#ifdef __linux__
#    include <errno.h>
#    include <fcntl.h>
#    include <limits.h>
#    include <stdlib.h>
#    include <sys/ipc.h>
#    include <sys/sem.h>
#    include <sys/stat.h>
#endif

NamedMutexException::NamedMutexException(const char* msg) :
    error_message(std::string(msg))
{
}

NamedMutexException::NamedMutexException(std::string msg) :
    error_message(msg)
{
}

NamedMutexException::NamedMutexException(std::stringstream& msg) :
    error_message(msg.str())
{
}

const char* NamedMutexException::what() const throw()
{
    return error_message.c_str();
}

/// <summary>
/// Create or get an existing named mutex object
/// </summary>
/// <param name="name">Mutex name</param>
NamedMutex::NamedMutex(const char* name) :
    name(std::string(name)),
    mutex(nullptr)
{
#ifdef __linux__
    // local copy of the name, prepend /tmp for temporary file
    std::string lname = "/tmp/" + this->name;
    if (lname.length() > NAME_MAX)
    {
        // Name too long
        std::stringstream ss;
        ss << "Failed to create or get NamedMutex '"
            << this->name << "' its name is too long.";
        throw NamedMutexException(ss);
    }
    // Try to create the temp file needed for the semaphore
    int fd = creat(lname.c_str(), 0660); 
    if (fd == -1)
    {
        std::stringstream ss;
        ss << "Failed to create NamedMutex '"
            << this->name << "'.";
        throw NamedMutexException(ss);
    }
    close(fd);
    key_t s_key = ftok(lname.c_str(), 69);
    if (s_key == -1)
    {
        std::stringstream ss;
        ss << "Failed to create NamedMutex '"
            << this->name << "'.";
        throw NamedMutexException(ss);
    }
    // Try to create the mutex 
    int sem_id = semget(s_key, 1, IPC_EXCL | IPC_CREAT | 0660);
    // Failed to create semaphore
    if (sem_id == -1)
    {
        // Failed because it already exists
        if (errno == EEXIST)
        {
            // Get it as is
            sem_id = semget(s_key, 1, IPC_CREAT | 0660);
            // Failed again
            if (sem_id == -1)
            {
                std::stringstream ss;
                ss << "Failed to get NamedMutex '"
                    << this->name << "'.";
                throw NamedMutexException(ss);
            }
        }
        // Some other error occurred
        else
        {
            std::stringstream ss;
            ss << "Failed to create NamedMutex '"
                << this->name << "'.";
            throw NamedMutexException(ss);
        }
    }
    // Got the semaphore, we're the first
    else
    {
        // Initialize semaphore
        semctl(sem_id, 0, SETVAL, 1);
    }
    // Success, store it 
    this->mutex = std::make_unique<int>(sem_id);
#elif defined _WIN32
    if (this->name.length() > MAX_PATH)
    {
        // Name too long
        std::stringstream ss;
        ss << "Failed to create or get NamedMutex '"
            << this->name << "' its name is too long.";
        throw NamedMutexException(ss);
    }
    HANDLE lmutex = nullptr;
    lmutex = CreateMutexA(
        NULL,
        FALSE,
        this->name.c_str()
    );
    if (lmutex == nullptr)
    {
        // Failed
        std::stringstream ss;
        ss << "Failed to create or get NamedMutex '"
            << this->name << "'.";
        throw NamedMutexException(ss);
    }
    this->mutex = lmutex;
#endif
}

/// <summary>
/// Create or get an existing named mutex object
/// </summary>
/// <param name="name">Mutex name</param>
NamedMutex::NamedMutex(std::string name)
    : NamedMutex(name.c_str())
{
}

/// <summary>
/// Destructor, if the mutex isn't released it
/// releases it like release() but noexcept
/// </summary>
NamedMutex::~NamedMutex()
{
    if (this->mutex != nullptr)
    {
#ifdef __linux__
        close(*this->mutex);
#elif defined _WIN32
        CloseHandle(this->mutex);
#endif
    }
}

/// <summary>
/// Try to lock (aquire) a named mutex
/// </summary>
void NamedMutex::lock()
{
    if (this->mutex == nullptr)
    {
        std::stringstream ss;
        ss << "Failed to lock NamedMutex '" << this->name
            << "', it was a nullptr.";
        throw NamedMutexException(ss);
    }
#ifdef __linux__
    struct sembuf sops;
    sops.sem_num = 0;
    // Lock mutex
    sops.sem_op = -1;
    // Release lock on program exit
    sops.sem_flg = SEM_UNDO; 
    if (semop(*this->mutex, &sops, 1) != 0)
    {
#elif defined _WIN32
    switch (WaitForSingleObject(this->mutex, INFINITE))
    {
    case WAIT_OBJECT_0:
        return;
    case WAIT_ABANDONED:
#endif
        // Failed
        std::stringstream ss;
        ss << "Failed to lock NamedMutex '" << this->name
            << "', wait abandoned.";
        throw NamedMutexException(ss);
    }
}

/// <summary>
/// Try to lock the named mutex, don't wait for it to unlock
/// </summary>
/// <returns>Returns true on success and false on failure</returns>
bool NamedMutex::try_lock()
{
#ifdef __linux__
    struct sembuf sops;
    sops.sem_num = 0;
    // Lock mutex
    sops.sem_op = -1; 
    // Release lock on program exit, don't wait for lock 
    sops.sem_flg = SEM_UNDO | IPC_NOWAIT; 
    return (semop(*this->mutex, &sops, 1) == 0);
#elif defined _WIN32
    switch (WaitForSingleObject(this->mutex, 0))
    {
    case WAIT_OBJECT_0:
        return true;
    default:
        return false;
    }
#endif
}

/// <summary>
/// Try to lock the named mutex, give up after wait milliseconds
/// </summary>
/// <param name="wait">Milliseconds to wait to lock</param>
/// <returns>Returns true on success and false on timeout</returns>
bool NamedMutex::try_lock(std::chrono::duration<long, std::milli> wait)
{
#ifdef __linux__
    struct timespec wait_timespec;
    auto secs = std::chrono::duration_cast<std::chrono::seconds>(wait);
    wait_timespec.tv_sec = secs.count();
    wait_timespec.tv_nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(wait - secs).count();
    struct sembuf sops;
    sops.sem_num = 0;
    // Lock mutex
    sops.sem_op = -1; 
    // Release lock on program exit, wait for lock 
    sops.sem_flg = SEM_UNDO;
    return (semtimedop(*this->mutex, &sops, 1, &wait_timespec) == 0);
#elif defined _WIN32
    switch (WaitForSingleObject(this->mutex, wait.count()))
    {
    case WAIT_OBJECT_0:
        return true;
    default:
        return false;
    }
#endif
}

/// <summary>
/// Unlock a named mutex
/// </summary>
void NamedMutex::unlock()
{
    if (this->mutex == nullptr)
    {
        std::stringstream ss;
        ss << "Failed to unlock NamedMutex '" << this->name
            << "', it was a nullptr.";
        throw NamedMutexException(ss);
    }
#ifdef __linux__
    struct sembuf sops;
    sops.sem_num = 0;
    // Unlock Mutex
    sops.sem_op = 1; 
    sops.sem_flg = 0;
    if (semop(*this->mutex, &sops, 1) != 0)
#elif defined _WIN32
    if (!ReleaseMutex(this->mutex))
#endif
    {
        std::stringstream ss;
        ss << "Failed to unlock NamedMutex '" << this->name << "'.";
        throw NamedMutexException(ss);
    }
    return;
}

/// <summary
/// Close handle to a NamedMutex
/// </summary>
void NamedMutex::release()
{
    if (this->mutex == nullptr)
    {
        std::stringstream ss;
        ss << "Failed to release NamedMutex '" << this->name
            << "', it was a nullptr.";
        throw NamedMutexException(ss);
    }
#ifdef __linux__
    this->mutex.reset();
#elif defined _WIN32
    if (!CloseHandle(this->mutex))
    {
        std::stringstream ss;
        ss << "Failed to release NamedMutex '" << this->name << "'.";
        throw NamedMutexException(ss);
    }
    this->mutex = nullptr;
#endif
}

/// <summary>
/// Remove this mutex from the system
/// </summary>
void NamedMutex::remove()
{
#ifdef __linux__
    if (this->mutex == nullptr)
    {
        std::stringstream ss;
        ss << "Failed to remove NamedMutex '" << this->name
            << "', it was a nullptr.";
        throw NamedMutexException(ss);
    }
    // Unlink the mutex
    if (semctl(*this->mutex, 0, IPC_RMID) == -1)
    {
        // If it didn't exist, that's okay
        if (errno == ENOENT) {
            return;
        // Else we failed
        } else {
            std::stringstream ss;
            ss << "Failed to remove NamedMutex '" << this->name << "'.";
            throw NamedMutexException(ss);
        }
    }
    // Remove the tmp file
    // local copy of the name, prepend /tmp for temporary file
    std::string lname = "/tmp/" + this->name;
    if (unlink(lname.c_str()) == -1)
    {
        std::stringstream ss;
        ss << "Failed to remove NamedMutex '" << this->name << "' /tmp file.";
        throw NamedMutexException(ss);
    }
#elif defined _WIN32
    return;
#endif
}
