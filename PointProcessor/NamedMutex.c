#include "NamedMutex.h"

#ifdef __linux__
#    include <errno.h>
#    include <fcntl.h>
#    include <stdlib.h>
#    include <string.h>
#    include <sys/stat.h>
#endif

/// <summary>
/// Create or get a named mutex
/// </summary>
/// <param name=mutex>Pointer to a mutex structure</param>
/// <param name=name>Name of the mutex</param>
/// <returns>Status as defined in NamedMutexStatus</returns>
int32_t named_mutex_create(NamedMutex* mutex, const char* const name)
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
    memset(mutex->name, 0, MUTEX_NAME_LEN);
    name_len = strlen(name);
    if (name[0] != '/')
    {
        lname = (char *)malloc(sizeof(char) * (name_len + 2));
        lname[0] = '/';
        strcpy(lname + 1, name);
    }
    else
    {
        lname = (char *)malloc(sizeof(char) * (name_len + 1));
    }
    if (strlen(lname) > (MUTEX_NAME_LEN - 1))
    {
        return MUTEX_NAME_TOO_LONG;
    }
    memset(mutex->name, 0, MUTEX_NAME_LEN);
    strncpy(mutex->name, lname, MUTEX_NAME_LEN - 1);
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
        mutex->mutex = lmutex;
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
            mutex->mutex = lmutex;
            return MUTEX_SUCCESS;
        }
        else
        {
            return MUTEX_FAILURE;
        }
    }
#elif defined _WIN32
    if (mutex == NULL)
    {
        return MUTEX_NULL;
    }
    if (name == NULL)
    {
        return MUTEX_NULL_NAME;
    }
    if (strlen(name) >= MUTEX_NAME_LEN)
    {
        return MUTEX_NAME_TOO_LONG;
    }
    HANDLE lmutex = NULL;
    lmutex = CreateMutexA(
        NULL,
        FALSE,
        name
    );
    if (lmutex == NULL)
    {
        // Failed
        return MUTEX_FAILURE;
    }
    mutex->mutex = lmutex;
    if (strlen(name) > (MUTEX_NAME_LEN - 1))
    {
        return MUTEX_NAME_TOO_LONG;
    }
    memset(mutex->name, 0, MUTEX_NAME_LEN);
    strncpy_s(mutex->name, MUTEX_NAME_LEN, name, MUTEX_NAME_LEN - 1);
    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        return MUTEX_SUCCESS;
    }
    return MUTEX_CREATED;
#endif
}

/// <summary>
/// Try to lock (aquire) a named mutex
/// </summary>
/// <param name=mutex>Pointer to a mutex structure</param>
/// <returns>Status as defined in NamedMutexStatus</returns>
int32_t named_mutex_lock(NamedMutex* mutex)
{
    if (mutex == NULL)
    {
        return MUTEX_NULL;
    }
#ifdef __linux__
    sem_wait(mutex->mutex);
#elif defined _WIN32
    switch (WaitForSingleObject(mutex->mutex, INFINITE))
    {
    case WAIT_OBJECT_0:
        return MUTEX_SUCCESS;
    case WAIT_ABANDONED:
        // Failed
        return MUTEX_FAILURE;
    }
#endif
    return MUTEX_SUCCESS;
}

/// <summary>
/// Unlock a named mutex
/// </summary>
/// <param name=mutex>Pointer to a mutex structure</param>
/// <returns>Status as defined in NamedMutexStatus</returns>
int32_t named_mutex_unlock(NamedMutex* mutex)
{
    if (mutex == NULL || mutex->mutex == NULL)
    {
        return MUTEX_NULL;
    }
#ifdef __linux__
    sem_post(mutex->mutex);
#elif defined _WIN32
    if (!ReleaseMutex(mutex->mutex))
    {
        return MUTEX_FAILURE;
    }
#endif
    return MUTEX_SUCCESS;
}

/// <summary>
/// Close handle to a NamedMutex
/// </summary>
/// <param name=mutex>Pointer to a mutex structure</param>
/// <returns>Status as defined in NamedMutexStatus</returns>
int32_t named_mutex_release(NamedMutex* mutex)
{
    if (mutex == NULL || mutex->mutex == NULL)
    {
        return MUTEX_NULL;
    }
#ifdef __linux__
    if (sem_close(mutex->mutex) == -1)
    {
        return MUTEX_FAILURE;
    }
#elif defined _WIN32
    BOOL ignore = CloseHandle(mutex->mutex);
    UNREFERENCED_PARAMETER(ignore);
#endif
    return MUTEX_SUCCESS;
}

/// <summary>
/// Remove a named mutex from the system
/// </summary>
/// <param name=name>Name of mutex to remove</param>
/// <returns>Status as defined in NamedMutexStatus</returns>
int32_t named_mutex_remove(const char* const name)
{
#ifdef __linux__
    // local copy of mutex name
    char* lname = NULL;
    // length of name
    size_t name_len = 0;
    if (name == NULL)
    {
        return MUTEX_NULL_NAME;
    }
    // Create a local copy of name and prepend "/" if not there
    name_len = strlen(name);
    if (name[0] != '/')
    {
        lname = (char *)malloc(sizeof(char) * (name_len + 2));
        lname[0] = '/';
        strcpy(lname + 1, name);
    }
    else
    {
        lname = (char *)malloc(sizeof(char) * (name_len + 1));
    }
    // Unlink the mutex
    if (sem_unlink(lname) == -1)
    {
        return MUTEX_FAILURE;
    }
#elif defined _WIN32
    if (name == NULL)
    {
        return MUTEX_NULL_NAME;
    }
    if (strlen(name) >= MUTEX_NAME_LEN)
    {
        return MUTEX_NAME_TOO_LONG;
    }
#endif
    return MUTEX_SUCCESS;
}
