#include "pch.h"

#include <iostream>

static const char* const NAME = "MyNamedMutex";

/// <summary>
/// Helper thread function for incrementing an integer
/// </summary>
/// <param name="i">Pointer to int to increment</param>
static void mutex_increment_int(int32_t *i)
{
    NamedMutex mutex(NAME);
    mutex.get_existing();
    mutex.lock();
    if (i)
    {
        (*i)++;
    }
    mutex.unlock();
    mutex.release();
}

/// <summary>
/// Test NamedMutex create twice
/// </summary>
TEST(NamedMutex, CreateTwice)
{
    bool threw_exception = false;
    NamedMutex mutex(NAME);
    // Create a new mutex
    try
    {
        // Remove any prexisting mutex from the system (linux)
        mutex.remove();
        mutex.create();
    }
    catch (NamedMutexException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(!threw_exception);
    // Try to create the same mutex again and fail
    try
    {
        mutex.create();
    }
    catch (NamedMutexException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(threw_exception);
    threw_exception = false;
    // Try to create or get the same mutex and succeed
    try
    {
        mutex.create_or_get();
    }
    catch (NamedMutexException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(!threw_exception);
    threw_exception = false;
    // Try to get the existing mutex and succeed
    try
    {
        mutex.get_existing();
    }
    catch (NamedMutexException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(!threw_exception);
    threw_exception = false;
    // Try to release and remove the mutex and succeed
    try
    {
        mutex.release();
	std::cout << "Released mutex." << std::endl;
        mutex.remove();
	std::cout << "Removed mutex." << std::endl;
    }
    catch (NamedMutexException& ex)
    {
        threw_exception = true;
	std::cout << ex.what() << std::endl;
    }
    ASSERT_TRUE(!threw_exception);
}

/// <summary>
/// Test NamedMutex locking a mutex without obtaining it first
/// </summary>
TEST(NamedMutex, NullLock)
{
    NamedMutex mutex(NAME);
    bool threw_exception = false;
    try
    {
        // Remove any prexisting mutex from the system (linux)
        mutex.remove();
        // Lock the mutex without obtaining it
        mutex.lock();
    }
    catch (NamedMutexException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(threw_exception);
}

/// <summary>
/// Test NamedMutex releasing a mutex without obtaining it first
/// </summary>
TEST(NamedMutex, NullRelease)
{
    NamedMutex mutex(NAME);
    bool threw_exception = false;
    try
    {
        // Remove any prexisting mutex from the system (linux)
        mutex.remove();
        // Release the mutex without obtaining it
        mutex.release();
    }
    catch (NamedMutexException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(threw_exception);
}

/// <summary>
/// Test NamedMutex unlocking a mutex without obtaining it first
/// </summary>
TEST(NamedMutex, NullUnlock)
{
    NamedMutex mutex(NAME);
    bool threw_exception = false;
    try
    {
        // Remove any prexisting mutex from the system (linux)
        mutex.remove();
        // Unlock the mutex without obtaining it
        mutex.unlock();
    }
    catch (NamedMutexException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(threw_exception);
}

/// <summary>
/// Test NamedMutex locking/unlocking (non-parallel)
/// </summary>
TEST(NamedMutex, LockSerial)
{
    NamedMutex mutex(NAME);
    bool threw_exception = false;
    try
    {
        // Remove any prexisting mutex from the system (linux)
        mutex.remove();
        mutex.create();
        mutex.lock();
        mutex.unlock();
        mutex.release();
        mutex.remove();
    }
    catch (NamedMutexException& ex)
    {
        threw_exception = true;
        std::cout << ex.what() << std::endl;
    }
    ASSERT_TRUE(!threw_exception);
}

/*
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

*/
