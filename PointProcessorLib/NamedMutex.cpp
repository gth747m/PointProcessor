#include "NamedMutex.h"

#include <cstdint>
#include <iostream>
#include <sstream>

#ifdef __linux__
#    include <errno.h>
#    include <fcntl.h>
#    include <limits.h>
#    include <stdlib.h>
#    include <string.h>
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
/// Create a named mutex object, this does not create or obtain a handle
/// to the mutex, it simply constructs the object
/// </summary>
/// <param name="name">Mutex name</param>
NamedMutex::NamedMutex(const char* name) :
    name(std::string(name)),
    mutex(nullptr)
{
#ifdef __linux__
    // local copy of mutex name
    std::string lname = "/" + this->name;
    if (lname.length() > NAME_MAX)
    {
        // Name too long
        std::stringstream ss;
        ss << "Failed to create or get NamedMutex '"
            << this->name << "' its name is too long.";
        throw NamedMutexException(ss);
    }
    // local pointer to mutex
    sem_t* lmutex = nullptr;
    // Try to create the mutex
    lmutex = sem_open(
        lname.c_str(), 
        O_CREAT | O_EXCL, 
        S_IRUSR | S_IWUSR, 
        1);
    // Success, we are the first to create this mutex
    if (lmutex != SEM_FAILED)
    {
        // Store it 
        this->mutex = lmutex;
        return;
    }
    // Failed to create the mutex
    else
    {
        // Mutex already exists
        if (errno == EEXIST)
        {
            // Connect to the preexisting mutex
            lmutex = sem_open(lname.c_str(), O_CREAT);
            // Store it 
            this->mutex = lmutex;
            return;
        }
        else
        {
            // Failed
            std::stringstream ss;
            ss << "Failed to create NamedMutex '"
                << this->name << "'.";
            throw NamedMutexException(ss);
        }
    }
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
/// Create a named mutex object, this does not create or obtain a handle
/// to the mutex, it simply constructs the object
/// </summary>
/// <param name="name">Mutex name</param>
NamedMutex::NamedMutex(std::string name)
    : NamedMutex(name.c_str())
{
}

/// <summary>
/// Destructor
/// </summary>
NamedMutex::~NamedMutex()
{
    if (this->mutex != nullptr)
        this->release();
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
    sem_wait(this->mutex);
#elif defined _WIN32
    switch (WaitForSingleObject(this->mutex, INFINITE))
    {
    case WAIT_OBJECT_0:
        return;
    case WAIT_ABANDONED:
        // Failed
        std::stringstream ss;
        ss << "Failed to lock NamedMutex '" << this->name
            << "', wait abandoned.";
        throw NamedMutexException(ss);
    }
#endif
}

/// <summary>
/// Try to lock the named mutex, don't wait for it to unlock
/// </summary>
/// <returns>Returns true on success and false on failure</returns>
bool NamedMutex::try_lock()
{
#ifdef __linux__
    return (sem_trywait(this->mutex, &wait_timespec) == 0);
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
/// <param name="wait"></param>
/// <returns>Returns true on success and false on timeout</returns>
bool NamedMutex::try_lock(std::chrono::duration<long, std::milli> wait)
{
#ifdef __linux__
    const auto timeout = std::chrono::system_clock::now() + wait;
    struct timespec wait_timespec;
    wait_timespec.tv_sec = std::chrono::system_clock::to_time_t(timeout);
    wait_timespec.tv_nsec = std::chrono::duration_cast<std::chrono::nanoseconds, long>(
        timeout.time_since_epoch() - std::chrono::duration_cast<std::chrono::seconds, long>(
        timeout.time_since_epoch())).count();
    return (sem_timedwait(this->mutex, &wait_timespec) == 0);
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
    if (sem_post(this->mutex) != 0)
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
    if (sem_close(this->mutex) == -1)
#elif defined _WIN32
    if (!CloseHandle(this->mutex))
#endif
    {
        std::stringstream ss;
        ss << "Failed to release NamedMutex '" << this->name << "'.";
        throw NamedMutexException(ss);
    }
    this->mutex = nullptr;
}

/// <summary>
/// Remove this mutex from the system
/// </summary>
void NamedMutex::remove()
{
#ifdef __linux__
    // local copy of mutex name
    std::string lname = "/" + this->name;
    // Unlink the mutex
    if (sem_unlink(lname.c_str()) == -1)
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
#elif defined _WIN32
    return;
#endif
}

#ifdef __linux__
/// <summary>
/// Get the underlying semaphore
/// </summary>
sem_t* NamedMutex::get_sem() const
{
    return this->mutex;
}
#elif defined _WIN32
/// <summary>
/// Get the underlying handle to the Windows mutex
/// </summary>
HANDLE NamedMutex::get_handle() const
{
    return this->mutex;
}
#endif

