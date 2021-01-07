#pragma once

#include <chrono>
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
    /// Create or get an existing named mutex object
    /// </summary>
    /// <param name="name">Mutex name</param>
    NamedMutex(const char* name);
    /// <summary>
    /// Create or get an existing named mutex object
    /// </summary>
    /// <param name="name">Mutex name</param>
    NamedMutex(std::string name);
    /// <summary>
    /// Destructor, release the mutex if it hasn't been already
    /// </summary>
    virtual ~NamedMutex();
    /// <summary>
    /// Try to lock (aquire) a named mutex
    /// </summary>
    void lock();
    /// <summary>
    /// Try to lock the named mutex, don't wait for it to unlock
    /// </summary>
    /// <returns>Returns true on success and false on failure</returns>
    bool try_lock();
    /// <summary>
    /// Try to lock the named mutex, give up after wait milliseconds
    /// </summary>
    /// <param name="wait"></param>
    /// <returns>Returns true on success and false on timeout</returns>
    bool try_lock(std::chrono::duration<long, std::milli> wait);
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
#ifdef __linux__
    /// <summary>
    /// Get the underlying semaphore
    /// </summary>
    sem_t* get_sem() const;
#elif defined _WIN32
    /// <summary>
    /// Get the underlying handle to the Windows mutex
    /// </summary>
    HANDLE get_handle() const;
#endif
protected:
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
private:
};

