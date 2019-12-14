#pragma once

#ifdef __linux__
#    include <semaphore.h>
#elif defined _WIN32
#    define WIN32_LEAN_AND_MEAN
#    include <Windows.h>
#endif

#define MUTEX_NAME_LEN 32

typedef struct NamedMutex
{
    char name[MUTEX_NAME_LEN];
#ifdef __linux__
    sem_t *mutex;
#elif defined _WIN32
    HANDLE mutex
#endif
} NamedMutex;

enum NamedMutexStatus
{
    MUTEX_FAILURE    = -3, // Generic Failure
    MUTEX_NULL       = -2, // Mutex was null
    MUTEX_NULL_NAME  = -1, // Mutex name was null
    MUTEX_SUCCESS    = 0,  // Mutex operation successful
    MUTEX_CREATED    = 1   // Mutex created
};

/// <summary>
/// Create or get a named mutex
/// </summary>
/// <param name=mutex>Pointer to a mutex structure</param>
/// <param name=name>Name of the mutex</param>
/// <returns>Status as defined in NamedMutexStatus</returns>
int32_t get_named_mutex(NamedMutex *mutex, const char * const name);

/// <summary>
/// Try to lock (aquire) a named mutex
/// </summary>
/// <param name=mutex>Pointer to a mutex structure</param>
/// <returns>Status as defined in NamedMutexStatus</returns>
int32_t lock_named_mutex(NamedMutex *mutex);

/// <summary>
/// Unlock a named mutex
/// </summary>
/// <param name=mutex>Pointer to a mutex structure</param>
/// <returns>Status as defined in NamedMutexStatus</returns>
int32_t unlock_named_mutex(NamedMutex *mutex);

/// <summary>
/// Remove a named mutex from the system
/// </summary>
/// <param name=mutex>Pointer to a mutex structure</param>
/// <returns>Status as defined in NamedMutexStatus</returns>
int32_t remove_named_mutex(const char * const name);
