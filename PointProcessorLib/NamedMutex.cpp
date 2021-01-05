#include "NamedMutex.h"

#include <cstdint>
#include <iostream>
#include <sstream>

#ifdef __linux__
#    include <errno.h>
#    include <fcntl.h>
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

NamedMutex::NamedMutex(const char* name) :
    name(std::string(name)),
    mutex(nullptr)
{
}

/// <summary>
/// Create a named mutex object, this does not create or obtain a handle
/// to the mutex, it simply constructs the object
/// </summary>
/// <param name="name">Mutex name</param>
NamedMutex::NamedMutex(std::string name) :
    name(name),
    mutex(nullptr)
{
}

/// <summary>
/// Try to create a new named mutex, it cannot already exist
/// </summary>
void NamedMutex::create()
{
    if (this->mutex != nullptr)
    {
        std::stringstream ss;
        ss << "Failed to create NamedMutex '"
            << this->name << "', NamedMutex->mutex is not null.";
        throw NamedMutexException(ss);
    }
#ifdef __linux__
    // local copy of mutex name
    std::string lname = "/" + this->name;
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
            std::stringstream ss;
            ss << "NamedMutex '" << this->name << "' already exists.";
            throw NamedMutexException(ss);
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
    HANDLE lmutex = nullptr;
    SetLastError(ERROR_SUCCESS);
    lmutex = CreateMutexA(
        NULL,
        FALSE,
        this->name.c_str()
    );
    if (lmutex == nullptr)
    {
        // Failed
        std::stringstream ss;
        ss << "Failed to create NamedMutex '"
            << this->name << "'.";
        throw NamedMutexException(ss);
    }
    this->mutex = lmutex;
    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        std::stringstream ss;
        ss << "NamedMutex '" << this->name << "' already exists.";
        throw NamedMutexException(ss);
    }
#endif
}

/// <summary>
/// Create a new named mutex or get a handle to one that already exists
/// </summary>
void NamedMutex::create_or_get()
{
    if (this->mutex != nullptr)
    {
        std::stringstream ss;
        ss << "Failed to create NamedMutex '"
            << this->name << "', NamedMutex->mutex is not null.";
        throw NamedMutexException(ss);
    }
#ifdef __linux__
    // local copy of mutex name
    std::string lname = "/" + this->name;
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
    HANDLE lmutex = nullptr;
    SetLastError(ERROR_SUCCESS);
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
/// Try to get a handle to an already created named mutex
/// </summary>
void NamedMutex::get_existing()
{
    if (this->mutex != nullptr)
    {
        std::stringstream ss;
        ss << "Failed to create NamedMutex '"
            << this->name << "', NamedMutex->mutex is not null.";
        throw NamedMutexException(ss);
    }
#ifdef __linux__
    // local copy of mutex name
    std::string lname = "/" + this->name;
    // local pointer to mutex
    sem_t* lmutex = nullptr;
    // Try to create the mutex
    lmutex = sem_open(
        lname.c_str(), 
        O_CREAT | O_EXCL, 
        S_IRUSR | S_IWUSR, 
        1);
    // We are the first to create this mutex, this is a failure, since
    // we expected it to already exist
    if (lmutex != SEM_FAILED)
    {
        // We shouldn't have created it, release it then throw exception
        this->release();
        std::stringstream ss;
        ss << "Failed to get NamedMutex '" << this->name 
		    << "' it doesn't exist.";
        throw NamedMutexException(ss);
    }
    // Failed to create the mutex
    else
    {
        // Mutex already exists, this is what we expect
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
            // Failed to create or get it
            std::stringstream ss;
            ss << "Failed to get NamedMutex '"
                << this->name << "'.";
            throw NamedMutexException(ss);
        }
    }
#elif defined _WIN32
    HANDLE lmutex = nullptr;
    SetLastError(ERROR_SUCCESS);
    lmutex = CreateMutexA(
        NULL,
        FALSE,
        this->name.c_str()
    );
    if (lmutex == nullptr)
    {
        // Failed
        std::stringstream ss;
        ss << "Failed to get handle to NamedMutex '"
            << this->name << "'.";
        throw NamedMutexException(ss);
    }
    this->mutex = lmutex;
    if (GetLastError() != ERROR_ALREADY_EXISTS)
    {
        // We shouldn't have created it, release it then throw exception
        this->release();
        std::stringstream ss;
        ss << "NamedMutex '" << this->name << "' doesn't exists.";
        throw NamedMutexException(ss);
    }
#endif
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
/// Unlock a named mutex
/// </summary>
void NamedMutex::unlock()
{
    if (this->mutex == nullptr)
    {
        throw NamedMutexException("Failed to unlock mutex, it was a nullptr.");
    }
#ifdef __linux__
    sem_post(this->mutex);
#elif defined _WIN32
    if (!ReleaseMutex(this->mutex))
    {
        throw NamedMutexException("Failed to unlock mutex");
    }
#endif
    return;
}

/// <summary
/// Close handle to a NamedMutex
/// </summary>
void NamedMutex::release()
{
    if (this->mutex == nullptr)
    {
        throw NamedMutexException("Failed to release mutex, it was a nullptr.");
    }
#ifdef __linux__
    if (sem_close(this->mutex) == -1)
    {
        throw NamedMutexException("Failed to release mutex.");
    }
#elif defined _WIN32
    BOOL ignore = CloseHandle(this->mutex);
    UNREFERENCED_PARAMETER(ignore);
#endif
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
            throw NamedMutexException("Failed to remove mutex.");
        }
    }
#elif defined _WIN32
    return;
#endif
}

