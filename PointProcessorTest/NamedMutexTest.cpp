#include "pch.h"

#include <iostream>
#include <thread>

static const char* const NAME = "MyNamedMutex";

/// <summary>
/// Helper thread function for incrementing an integer
/// </summary>
/// <param name="i">Pointer to int to increment</param>
static void mutex_increment_int(int32_t *i)
{
    NamedMutex mutex(NAME);
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
TEST(NamedMutex, Create)
{
    bool threw_exception = false;
    std::unique_ptr<NamedMutex> mutex;
    NamedMutex* mutex2 = nullptr;
    // Create a new mutex
    try
    {
        mutex = std::make_unique<NamedMutex>(NAME);
    }
    catch (NamedMutexException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(!threw_exception);
    // Try to create or get the same mutex and succeed
    try
    {
        mutex2 = new NamedMutex(NAME);
    }
    catch (NamedMutexException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(!threw_exception);
    threw_exception = false;
    // Try to release the second mutex and succeed
    try
    {
        mutex2->release();
        delete mutex2;
    }
    catch (NamedMutexException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(!threw_exception);
    threw_exception = false;
    // Try to release and remove the first mutex and succeed
    try
    {
        mutex->release();
        mutex->remove();
    }
    catch (NamedMutexException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(!threw_exception);
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
        mutex.lock();
        mutex.unlock();
        mutex.release();
        mutex.remove();
    }
    catch (NamedMutexException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(!threw_exception);
}

TEST(NamedMutex, LockParallel)
{
    int32_t i = 0;
    NamedMutex mutex(NAME);
    bool threw_exception = false;
    try
    {
        mutex.lock();
    }
    catch (NamedMutexException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(!threw_exception);
    // Create child thread to increment i
    std::thread child (mutex_increment_int, &i);
    // Check that thread is 0 still because mutex is locked
    ASSERT_EQ(i, 0);
    // increment i
    i++;
    // Check that i is 1 now
    ASSERT_EQ(i, 1);
    // unlock mutex
    try 
    {
        mutex.unlock();
    }
    catch (NamedMutexException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(!threw_exception);
    // Wait for the threads to finish
    child.join();
    // Check that i is 2 because the child can now increment it
    ASSERT_EQ(i, 2);
    try 
    {
        mutex.release();
        mutex.remove();
    }
    catch (NamedMutexException&)
    {
        threw_exception = true;
    }
}