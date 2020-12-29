#include "pch.h"

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
/// <returns>NULL</returns>
static void * mutex_increment_int(int32_t *i)
{
    NamedMutex mutex;
    int32_t status = named_mutex_create(&mutex, NAME);
    ASSERT_EQ(status, MUTEX_SUCCESS);
    status = named_mutex_lock(&mutex);
    ASSERT_EQ(status, MUTEX_SUCCESS);
    if (i)
    {
        (*i)++;
    }
    status = named_mutex_unlock(&mutex);
    ASSERT_EQ(status, MUTEX_SUCCESS);
    status = named_mutex_release(&mutex);
    ASSERT_EQ(status, MUTEX_SUCCESS);
    return NULL;
}
#elif defined _WIN32
/// <summary>
/// Helper thread function for incrementing an integer
/// </summary>
/// <param name="i">Pointer to int to increment</param>
static void mutex_increment_int(int32_t *i)
{
    NamedMutex mutex;
    int32_t status = named_mutex_create(&mutex, NAME);
    ASSERT_EQ(status, MUTEX_SUCCESS);
    status = named_mutex_lock(&mutex);
    ASSERT_EQ(status, MUTEX_SUCCESS);
    if (i)
    {
        (*i)++;
    }
    status = named_mutex_unlock(&mutex);
    ASSERT_EQ(status, MUTEX_SUCCESS);
    status = named_mutex_release(&mutex);
    ASSERT_EQ(status, MUTEX_SUCCESS);
}
#endif

/// <summary>
/// Test NamedMutex creation
/// </summary>
TEST(NamedMutex, Create)
{
    NamedMutex mutex;
    NamedMutex mutex2;
    int32_t status = named_mutex_remove(NAME);
    ASSERT_EQ(status, MUTEX_SUCCESS);
    status = named_mutex_create(&mutex, NAME);
    ASSERT_EQ(status, MUTEX_CREATED);
    status = named_mutex_create(&mutex2, NAME);
    ASSERT_EQ(status, MUTEX_SUCCESS);
    status = named_mutex_release(&mutex);
    ASSERT_EQ(status, MUTEX_SUCCESS);
    status = named_mutex_release(&mutex2);
    ASSERT_EQ(status, MUTEX_SUCCESS);
    status = named_mutex_remove(NAME);
    ASSERT_EQ(status, MUTEX_SUCCESS);
}

/// <summary>
/// Test NamedMutex functions passed a NULL mutex
/// </summary>
TEST(NamedMutex, NullMutex)
{
    int32_t status = named_mutex_remove(NAME);
    ASSERT_EQ(status, MUTEX_SUCCESS);
    status = named_mutex_create(NULL, NAME);
    ASSERT_EQ(status, MUTEX_NULL);
    status = named_mutex_lock(NULL);
    ASSERT_EQ(status, MUTEX_NULL);
    status = named_mutex_unlock(NULL);
    ASSERT_EQ(status, MUTEX_NULL);
}

/// <summary>
/// Test NamedMutex functions passed a NULL name
/// </summary>
TEST(NamedMutex, NullName)
{
    NamedMutex mutex;
    int32_t status = named_mutex_remove(NULL);
    ASSERT_EQ(status, MUTEX_NULL_NAME);
    status = named_mutex_create(&mutex, NULL);
    ASSERT_EQ(status, MUTEX_NULL_NAME);
    status = named_mutex_remove(NULL);
    ASSERT_EQ(status, MUTEX_NULL_NAME);
}

/// <summary>
/// Test NamedMutex functions passed too long of a name
/// </summary>
TEST(NamedMutex, LongName)
{
    NamedMutex mutex;
    char name[(MUTEX_NAME_LEN * 2) + 1] = { 0 };
    random_name(name, (MUTEX_NAME_LEN * 2) + 1);
    int32_t status = named_mutex_remove(name);
    ASSERT_EQ(status, MUTEX_NAME_TOO_LONG);
    status = named_mutex_create(&mutex, name);
    ASSERT_EQ(status, MUTEX_NAME_TOO_LONG);
    status = named_mutex_remove(name);
    ASSERT_EQ(status, MUTEX_NAME_TOO_LONG);
}

/// <summary>
/// Test NamedMutex locking/unlocking (non-parallel)
/// </summary>
TEST(NamedMutex, LockSerial)
{
    NamedMutex mutex;
    int32_t status = named_mutex_remove(NAME);
    ASSERT_EQ(status, MUTEX_SUCCESS);
    status = named_mutex_create(&mutex, NAME);
    ASSERT_EQ(status, MUTEX_CREATED);
    status = named_mutex_lock(&mutex);
    ASSERT_EQ(status, MUTEX_SUCCESS);
    status = named_mutex_unlock(&mutex);
    ASSERT_EQ(status, MUTEX_SUCCESS);
    status = named_mutex_release(&mutex);
    ASSERT_EQ(status, MUTEX_SUCCESS);
    status = named_mutex_remove(NAME);
    ASSERT_EQ(status, MUTEX_SUCCESS);
}

/// <summary>
/// Test NamedMutex locking/unlocking (non-parallel)
/// </summary>
TEST(NamedMutex, LockParallel)
{
    NamedMutex mutex;
    int32_t i = 0;
    int32_t status = named_mutex_remove(NAME);
    ASSERT_EQ(status, MUTEX_SUCCESS);
    status = named_mutex_create(&mutex, NAME);
    ASSERT_EQ(status, MUTEX_CREATED);
    // Lock the mutex
    status = named_mutex_lock(&mutex);
    ASSERT_EQ(status, MUTEX_SUCCESS);
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
    ASSERT_TRUE(thread != NULL);
#endif
    // Check that thread is 0 still
    ASSERT_EQ(i, 0);
    // increment i
    i++;
    // Check that i is 1 now
    ASSERT_EQ(i, 1);
    // unlock mutex
    status = named_mutex_unlock(&mutex);
    ASSERT_EQ(status, MUTEX_SUCCESS);
    // Wait for the threads to finish
#ifdef __linux__
    ASSERT_EQ(pthread_join(thread, NULL), 0);
#elif defined _WIN32
    WaitForSingleObject(thread, INFINITE);
#endif
    // Check that i is now 2
    ASSERT_EQ(i, 2);
    status = named_mutex_release(&mutex);
    ASSERT_EQ(status, MUTEX_SUCCESS);
    status = named_mutex_remove(NAME);
    ASSERT_EQ(status, MUTEX_SUCCESS);
}

