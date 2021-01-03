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
    is_owner(false),
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
    is_owner(false),
    mutex(nullptr)
{
}

/// <summary>
/// Try to create a new named mutex, it cannot already exist
/// </summary>
void NamedMutex::create()
{
#ifdef __linux__
    // local copy of mutex name
    char* lname = nullptr;
    // local pointer to mutex
    sem_t* lmutex = nullptr;
    // length of name
    size_t name_len = 0;
    if (mutex == nullptr)
    {
        return MUTEX_NULL;
    }
    if (name == nullptr)
    {
        return MUTEX_NULL_NAME;
    }
    // Create a local copy of name and prepend "/" if not there
    memset(this->name, 0, MUTEX_NAME_LEN);
    name_len = strlen(name);
    if (name[0] != '/')
    {
        lname = (char *)calloc(name_len + 2, sizeof(char));
        lname[0] = '/';
        strcpy(lname + 1, name);
    }
    else
    {
        lname = (char *)calloc(name_len + 1, sizeof(char));
    }
    if (strlen(lname) > (MUTEX_NAME_LEN - 1))
    {
        if (lname)
        {
            free(lname);
        }
        return MUTEX_NAME_TOO_LONG;
    }
    memset(this->name, 0, MUTEX_NAME_LEN);
    strncpy(this->name, lname, MUTEX_NAME_LEN - 1);
    if (lname)
    {
        free(lname);
    }
    // Try to create the mutex
    lmutex = sem_open(
        name, 
        O_CREAT | O_EXCL, 
        S_IRUSR | S_IWUSR, 
        1);
    // Success, we are the first to create this mutex
    if (lmutex != SEM_FAILED)
    {
        // Store it 
        this->mutex = lmutex;
        return MUTEX_CREATED;
    }
    // Failed to create the mutex
    else
    {
        // Mutex already exists
        if (errno == EEXIST)
        {
            // Connect to the preexisting mutex
            lmutex = sem_open(name, O_CREAT);
            // Store it
            this->mutex = lmutex;
            return MUTEX_SUCCESS;
        }
        else
        {
            return MUTEX_FAILURE;
        }
    }
#elif defined _WIN32
    if (this->mutex != nullptr)
    {
        std::stringstream ss;
        ss << "Failed to create NamedMutex '"
            << this->name << "', NamedMutex->mutex is not null.";
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
        ss << "Failed to create NamedMutex '"
            << this->name << "'.";
        throw NamedMutexException(ss);
    }
    this->mutex = std::make_unique<HANDLE>(lmutex);
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
#ifdef __linux__
    // local copy of mutex name
    char* lname = nullptr;
    // local pointer to mutex
    sem_t* lmutex = nullptr;
    // length of name
    size_t name_len = 0;
    if (mutex == nullptr)
    {
        return MUTEX_NULL;
    }
    if (name == nullptr)
    {
        return MUTEX_NULL_NAME;
    }
    // Create a local copy of name and prepend "/" if not there
    memset(this->name, 0, MUTEX_NAME_LEN);
    name_len = strlen(name);
    if (name[0] != '/')
    {
        lname = (char *)calloc(name_len + 2, sizeof(char));
        lname[0] = '/';
        strcpy(lname + 1, name);
    }
    else
    {
        lname = (char *)calloc(name_len + 1, sizeof(char));
    }
    if (strlen(lname) > (MUTEX_NAME_LEN - 1))
    {
        if (lname)
        {
            free(lname);
        }
        return MUTEX_NAME_TOO_LONG;
    }
    memset(this->name, 0, MUTEX_NAME_LEN);
    strncpy(this->name, lname, MUTEX_NAME_LEN - 1);
    if (lname)
    {
        free(lname);
    }
    // Try to create the mutex
    lmutex = sem_open(
        name, 
        O_CREAT | O_EXCL, 
        S_IRUSR | S_IWUSR, 
        1);
    // Success, we are the first to create this mutex
    if (lmutex != SEM_FAILED)
    {
        // Store it 
        this->mutex = std::make_unique<HANDLE>(lmutex);
        return MUTEX_CREATED;
    }
    // Failed to create the mutex
    else
    {
        // Mutex already exists
        if (errno == EEXIST)
        {
            // Connect to the preexisting mutex
            lmutex = sem_open(name, O_CREAT);
            // Store it
            this->mutex = std::make_unique<HANDLE>(lmutex);
            return MUTEX_SUCCESS;
        }
        else
        {
            return MUTEX_FAILURE;
        }
    }
#elif defined _WIN32
    if (this->mutex != nullptr)
    {
        std::stringstream ss;
        ss << "Failed to create NamedMutex '"
            << this->name << "', NamedMutex->mutex is not null.";
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
    this->mutex = std::make_unique<HANDLE>(lmutex);
#endif
}

/// <summary>
/// Try to get a handle to an already created named mutex
/// </summary>
void NamedMutex::get_existing()
{
#ifdef __linux__
    // local copy of mutex name
    char* lname = NULL;
    // local pointer to mutex
    sem_t* lmutex = NULL;
    // length of name
    size_t name_len = 0;
    if (mutex == NULL)
    {
        return MUTEX_NULL;
    }
    if (name == NULL)
    {
        return MUTEX_NULL_NAME;
    }
    // Create a local copy of name and prepend "/" if not there
    memset(this->name, 0, MUTEX_NAME_LEN);
    name_len = strlen(name);
    if (name[0] != '/')
    {
        lname = (char *)calloc(name_len + 2, sizeof(char));
        lname[0] = '/';
        strcpy(lname + 1, name);
    }
    else
    {
        lname = (char *)calloc(name_len + 1, sizeof(char));
    }
    if (strlen(lname) > (MUTEX_NAME_LEN - 1))
    {
        if (lname)
        {
            free(lname);
        }
        return MUTEX_NAME_TOO_LONG;
    }
    memset(this->name, 0, MUTEX_NAME_LEN);
    strncpy(this->name, lname, MUTEX_NAME_LEN - 1);
    if (lname)
    {
        free(lname);
    }
    // Try to create the mutex
    lmutex = sem_open(
        name, 
        O_CREAT | O_EXCL, 
        S_IRUSR | S_IWUSR, 
        1);
    // Success, we are the first to create this mutex
    if (lmutex != SEM_FAILED)
    {
        // Store it 
        this->mutex = std::make_unique<HANDLE>(lmutex);
        return MUTEX_CREATED;
    }
    // Failed to create the mutex
    else
    {
        // Mutex already exists
        if (errno == EEXIST)
        {
            // Connect to the preexisting mutex
            lmutex = sem_open(name, O_CREAT);
            // Store it
            this->mutex = std::make_unique<HANDLE>(lmutex);
            return MUTEX_SUCCESS;
        }
        else
        {
            return MUTEX_FAILURE;
        }
    }
#elif defined _WIN32
    if (this->mutex != nullptr)
    {
        std::stringstream ss;
        ss << "Failed to create NamedMutex '"
            << this->name << "', NamedMutex->mutex is not null.";
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
        ss << "Failed to get handle to NamedMutex '"
            << this->name << "'.";
        throw NamedMutexException(ss);
    }
    this->mutex = std::make_unique<HANDLE>(lmutex);
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
    switch (WaitForSingleObject(*this->mutex, INFINITE))
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
    if (!ReleaseMutex(*this->mutex))
    {
        throw NamedMutexException("Failed to unlock mutex");
    }
#endif
    return;
}

/// <summary>
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
        return MUTEX_FAILURE;
    }
#elif defined _WIN32
    BOOL ignore = CloseHandle(*this->mutex);
    UNREFERENCED_PARAMETER(ignore);
#endif
}

/// <summary>
/// Remove this mutex from the system
/// </summary>
void NamedMutex::remove()
{
#ifdef __linux__
    // local copy of mutex name
    char* lname = nullptr;
    // length of name
    size_t name_len = 0;
    if (name == nullptr)
    {
        return MUTEX_nullptr_NAME;
    }
    if (strlen(name) >= MUTEX_NAME_LEN)
    {
        return MUTEX_NAME_TOO_LONG;
    }
    // Create a local copy of name and prepend "/" if not there
    name_len = strlen(name);
    if (name[0] != '/')
    {
        lname = (char *)calloc(name_len + 2, sizeof(char));
        lname[0] = '/';
        strcpy(lname + 1, name);
    }
    else
    {
        lname = (char *)calloc(name_len + 1, sizeof(char));
    }
    // Unlink the mutex
    if (sem_unlink(lname) == -1)
    {
        if (lname)
        {
            free(lname);
        }
        // If it didn't exist, that's okay
        if (errno == ENOENT) {
            return MUTEX_SUCCESS;
        // Else we failed
        } else {
            return MUTEX_FAILURE;
        }
    }
    if (lname)
    {
        free(lname);
    }
#elif defined _WIN32
    return;
#endif
}

