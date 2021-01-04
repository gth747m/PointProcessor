#pragma once

#include <cstdint>
#include <exception>
#include <memory>
#include <sstream>
#include <string>

#ifdef __linux__
#    include <semaphore.h>
#elif defined _WIN32
#    define WIN32_LEAN_AND_MEAN
#    include <Windows.h>
#endif

class NamedMutexException : public std::exception
{
public:
    NamedMutexException(const char* msg);
    NamedMutexException(std::string msg);
    NamedMutexException(std::stringstream& msg);
    virtual const char* what() const throw();
protected:
    std::string error_message;
};

class NamedMutex
{
public:
    /// <summary>
    /// Create a named mutex object, this does not create or obtain a handle
    /// to the mutex, it simply constructs the object
    /// </summary>
    /// <param name="name">Mutex name</param>
    NamedMutex(const char* name);
    /// <summary>
    /// Create a named mutex object, this does not create or obtain a handle
    /// to the mutex, it simply constructs the object
    /// </summary>
    /// <param name="name">Mutex name</param>
    NamedMutex(std::string name);
    /// <summary>
    /// Try to create a new named mutex, it cannot already exist
    /// </summary>
    void create();
    /// <summary>
    /// Create a new named mutex or get a handle to one that already exists
    /// </summary>
    void create_or_get();
    /// <summary>
    /// Try to get a handle to an already created named mutex
    /// </summary>
    void get_existing();
    /// <summary>
    /// Try to lock (aquire) a named mutex
    /// </summary>
    void lock();
    /// <summary>
    /// Unlock a named mutex
    /// </summary>
    void unlock();
    /// <summary>
    /// Close handle to a NamedMutex
    /// </summary>
    void release();
    /// <summary>
    /// Remove this mutex from the system
    /// </summary>
    void remove();
protected:
private:
    /// <summary>
    /// Mutex name
    /// </summary>
    std::string name;
#ifdef __linux__
    /// <summary>
    /// Linux semaphore
    /// </summary>
    sem_t* mutex;
#elif defined _WIN32
    /// <summary>
    /// Windows mutex
    /// </summary>
    HANDLE mutex;
#endif
};

