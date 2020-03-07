#include "NamedMutexTest.h"

#include "NamedMutex.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
#include <pthread.h>
#endif

static const char* const NAME = "MyNamedMutex";

/// <summary>
/// Get a random ASCII character
/// </summary>
/// <returns>Random ASCII character</returns>
static char random_char()
{
    const char* chars = "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    return chars[rand() % 62];
}

/// <summary>
/// Put a random string of length len in name
/// </summary>
/// <param name="name">Name string to fill in</param>
/// <param name="len">String length</param>
static void random_name(char* name, size_t len)
{
    for (size_t i = 0; i < (len - 1); i++)
    {
        name[i] = random_char();
    }
    name[(len - 1)] = '\0';
}

#ifdef __linux__
/// <summary>
/// Helper thread function for incrementing an integer
/// </summary>
/// <param name="i">Pointer to int to increment</param>
/// <returns></returns>
static void * mutex_increment_int(int32_t *i)
{
    NamedMutex mutex;
    int32_t status = named_mutex_create(&mutex, NAME);
    assert(status == MUTEX_SUCCESS);
    status = named_mutex_lock(&mutex);
    assert(status == MUTEX_SUCCESS);
    if (i)
    {
        (*i)++;
    }
    status = named_mutex_unlock(&mutex);
    assert(status == MUTEX_SUCCESS);
    status = named_mutex_release(&mutex);
    assert(status == MUTEX_SUCCESS);
    return NULL;
}
#elif defined _WIN32
/// <summary>
/// Helper thread function for incrementing an integer
/// </summary>
/// <param name="i">Pointer to int to increment</param>
/// <returns></returns>
static void mutex_increment_int(int32_t *i)
{
    NamedMutex mutex;
    int32_t status = named_mutex_create(&mutex, NAME);
    assert(status == MUTEX_SUCCESS);
    status = named_mutex_lock(&mutex);
    assert(status == MUTEX_SUCCESS);
    if (i)
    {
        (*i)++;
    }
    status = named_mutex_unlock(&mutex);
    assert(status == MUTEX_SUCCESS);
    status = named_mutex_release(&mutex);
    assert(status == MUTEX_SUCCESS);
}
#endif

/// <summary>
/// Test NamedMutex creation
/// </summary>
static void named_mutex_test_create()
{
    printf("    Test creating named mutex...         ");
    NamedMutex mutex;
    NamedMutex mutex2;
    int32_t status = named_mutex_remove(NAME);
    assert(status == MUTEX_SUCCESS);
    status = named_mutex_create(&mutex, NAME);
    assert(status == MUTEX_CREATED);
    status = named_mutex_create(&mutex2, NAME);
    assert(status == MUTEX_SUCCESS);
    status = named_mutex_release(&mutex);
    assert(status == MUTEX_SUCCESS);
    status = named_mutex_release(&mutex2);
    assert(status == MUTEX_SUCCESS);
    status = named_mutex_remove(NAME);
    assert(status == MUTEX_SUCCESS);
    puts("Finished.");
}

/// <summary>
/// Test NamedMutex functions passed a NULL mutex
/// </summary>
static void named_mutex_test_null_mutex()
{
    printf("    Test creating NULL mutex...          ");
    int32_t status = named_mutex_remove(NAME);
    assert(status == MUTEX_SUCCESS);
    status = named_mutex_create(NULL, NAME);
    assert(status == MUTEX_NULL);
    status = named_mutex_lock(NULL);
    assert(status == MUTEX_NULL);
    status = named_mutex_unlock(NULL);
    assert(status == MUTEX_NULL);
    puts("Finished.");
}

/// <summary>
/// Test NamedMutex functions passed a NULL name
/// </summary>
static void named_mutex_test_null_name()
{
    printf("    Test creating NULL named mutex...    ");
    NamedMutex mutex;
    int32_t status = named_mutex_remove(NULL);
    assert(status == MUTEX_NULL_NAME);
    status = named_mutex_create(&mutex, NULL);
    assert(status == MUTEX_NULL_NAME);
    status = named_mutex_remove(NULL);
    assert(status == MUTEX_NULL_NAME);
    puts("Finished.");
}

/// <summary>
/// Test NamedMutex functions passed too long of a name
/// </summary>
static void named_mutex_test_long_name()
{
    printf("    Test creating long named mutex...    ");
    NamedMutex mutex;
    char name[(MUTEX_NAME_LEN * 2) + 1] = { 0 };
    random_name(name, (MUTEX_NAME_LEN * 2) + 1);
    int32_t status = named_mutex_remove(name);
    assert(status == MUTEX_NAME_TOO_LONG);
    status = named_mutex_create(&mutex, name);
    assert(status == MUTEX_NAME_TOO_LONG);
    status = named_mutex_remove(name);
    assert(status == MUTEX_NAME_TOO_LONG);
    puts("Finished.");
}

/// <summary>
/// Test NamedMutex locking/unlocking (non-parallel)
/// </summary>
static void named_mutex_test_lock_serial()
{
    printf("    Test serial locking named mutex...   ");
    NamedMutex mutex;
    int32_t status = named_mutex_remove(NAME);
    assert(status == MUTEX_SUCCESS);
    status = named_mutex_create(&mutex, NAME);
    assert(status == MUTEX_CREATED);
    status = named_mutex_lock(&mutex);
    assert(status == MUTEX_SUCCESS);
    status = named_mutex_unlock(&mutex);
    assert(status == MUTEX_SUCCESS);
    status = named_mutex_release(&mutex);
    assert(status == MUTEX_SUCCESS);
    status = named_mutex_remove(NAME);
    assert(status == MUTEX_SUCCESS);
    puts("Finished.");
}

/// <summary>
/// Test NamedMutex locking/unlocking (non-parallel)
/// </summary>
static void named_mutex_test_lock_parallel()
{
    printf("    Test parallel locking named mutex... ");
    NamedMutex mutex;
    int32_t i = 0;
    int32_t status = named_mutex_remove(NAME);
    assert(status == MUTEX_SUCCESS);
    status = named_mutex_create(&mutex, NAME);
    assert(status == MUTEX_CREATED);
    // Lock the mutex
    status = named_mutex_lock(&mutex);
    assert(status == MUTEX_SUCCESS);
    // Start thread to increment i
#ifdef __linux__
    pthread_t thread;
    pthread_create(&thread, NULL, 
            (void *(*)(void *))mutex_increment_int, &i);
#elif defined _WIN32
    DWORD threadId;
    HANDLE thread = CreateThread(
        NULL,   // Default security
        0,      // Default stack size
        (LPTHREAD_START_ROUTINE)mutex_increment_int,
        (LPVOID)&i,
        0,
        &threadId);
    assert(thread != NULL);
#endif
    // Check that thread is 0 still
    assert(i == 0);
    // increment i
    i++;
    // Check that i is 1 now
    assert(i == 1);
    // unlock mutex
    status = named_mutex_unlock(&mutex);
    assert(status == MUTEX_SUCCESS);
    // Wait for the threads to finish
#ifdef __linux__
    assert(pthread_join(thread, NULL) == 0);
#elif defined _WIN32
    WaitForSingleObject(thread, INFINITE);
#endif
    // Check that i is now 2
    assert(i == 2);
    status = named_mutex_release(&mutex);
    assert(status == MUTEX_SUCCESS);
    status = named_mutex_remove(NAME);
    assert(status == MUTEX_SUCCESS);
    puts("Finished.");
}

/// <summary>
/// Run a suite of NamedMutex unit tests
/// </summary>
void named_mutex_test()
{
    puts("Testing NamedMutex...");
    named_mutex_test_create();
    named_mutex_test_null_mutex();
    named_mutex_test_null_name();
    named_mutex_test_long_name();
    named_mutex_test_lock_serial();
    named_mutex_test_lock_parallel();
    puts("Finished testing NamedMutex.");
}
