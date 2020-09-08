#pragma once

#include <stdint.h>

#ifdef __linux__
#    include <semaphore.h>
#elif defined _WIN32
#    define WIN32_LEAN_AND_MEAN
#    include <Windows.h>
#endif

#include "PointLib/PointLib.h"

/// <summary>
/// Max name length for a named mutex
/// </summary>
#define MUTEX_NAME_LEN 32

/// <summary>
/// Named mutex structure
/// </summary>
typedef struct NamedMutex
{
    /// <summary>
    /// Name of this mutex
    /// </summary>
    char name[MUTEX_NAME_LEN];
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
} NamedMutex;

/// <summary>
/// Possible status messages from NamedMutex
/// </summary>
enum NamedMutexStatus
{
    /// <summary>
    /// Mutex name is too long
    /// </summary>
    MUTEX_NAME_TOO_LONG = -4,
    /// <summary>
    /// Mutex provided was null
    /// </summary>
    MUTEX_NULL = -3,
    /// <summary>
    /// Mutex name provided was null
    /// </summary>
    MUTEX_NULL_NAME = -2,
    /// <summary>
    /// Generic Failure
    /// </summary>
    MUTEX_FAILURE = -1,
    /// <summary>
    /// Mutex operation successful
    /// </summary>
    MUTEX_SUCCESS = 0,
    /// <summary>
    /// Mutex didn't exist, so it was created
    /// </summary>
    MUTEX_CREATED = 1
};

/// <summary>
/// Create or get a named mutex
/// </summary>
/// <param name=mutex>Pointer to a mutex structure</param>
/// <param name=name>Name of the mutex</param>
/// <returns>Status as defined in NamedMutexStatus</returns>
POINTLIB_API int32_t named_mutex_create(NamedMutex* mutex, const char* const name);

/// <summary>
/// Try to lock (aquire) a named mutex
/// </summary>
/// <param name=mutex>Pointer to a mutex structure</param>
/// <returns>Status as defined in NamedMutexStatus</returns>
POINTLIB_API int32_t named_mutex_lock(NamedMutex* mutex);

/// <summary>
/// Unlock a named mutex
/// </summary>
/// <param name=mutex>Pointer to a mutex structure</param>
/// <returns>Status as defined in NamedMutexStatus</returns>
POINTLIB_API int32_t named_mutex_unlock(NamedMutex* mutex);

/// <summary>
/// Close handle to a NamedMutex
/// </summary>
/// <param name=mutex>Pointer to a mutex structure</param>
/// <returns>Status as defined in NamedMutexStatus</returns>
POINTLIB_API int32_t named_mutex_release(NamedMutex* mutex);

/// <summary>
/// Remove a named mutex from the system
/// </summary>
/// <param name=mutex>Pointer to a mutex structure</param>
/// <returns>Status as defined in NamedMutexStatus</returns>
POINTLIB_API int32_t named_mutex_remove(const char* const name);
