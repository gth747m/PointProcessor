#include "pch.h"

static const char* const NAME = "MyTestNamedMutex";

/// <summary>
/// Test NamedMutex creation
/// </summary>
TEST(NamedMutex, Create)
{
    bool threw_exception = false;
    std::unique_ptr<sbb::NamedMutex> mutex;
    sbb::NamedMutex* mutex2 = nullptr;
    // Create a new mutex
    try
    {
        mutex = std::make_unique<sbb::NamedMutex>(NAME);
    }
    catch (sbb::NamedMutexException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(!threw_exception);
    // Try to create or get the same mutex and succeed
    try
    {
        mutex2 = new sbb::NamedMutex(NAME);
    }
    catch (sbb::NamedMutexException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(!threw_exception);
    // Try to release the second mutex and succeed
    try
    {
        delete mutex2;
    }
    catch (sbb::NamedMutexException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(!threw_exception);
    // Try to release and remove the first mutex and succeed
    try
    {
        mutex->remove();
    }
    catch (sbb::NamedMutexException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(!threw_exception);
}

/// <summary>
/// Test NamedMutex locking/unlocking (non-parallel)
/// </summary>
TEST(NamedMutex, LockAndUnlock)
{
    sbb::NamedMutex mutex(NAME);
    bool threw_exception = false;
    try
    {
        mutex.lock();
        mutex.unlock();
        mutex.remove();
    }
    catch (sbb::NamedMutexException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(!threw_exception);
}

/// <summary>
/// Test NamedMutex locking with child thread
/// </summary>
TEST(NamedMutex, LockParallel)
{
    int32_t i = 0;
    sbb::NamedMutex mutex(NAME);
    bool threw_exception = false;
    try
    {
        mutex.lock();
    }
    catch (sbb::NamedMutexException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(!threw_exception);
    // Mutex locked increment function
    auto func = [](int32_t* i) -> void {
        sbb::NamedMutex mutex2(NAME);
        mutex2.lock();
        if (i)
        {
            (*i)++;
        }
        mutex2.unlock();
    };
    // Create child thread to increment i
    std::thread child (func, &i);
    // Check that thread is 0 still because mutex is locked
    EXPECT_EQ(i, 0);
    // increment i
    i++;
    // Check that i is 1 now
    EXPECT_EQ(i, 1);
    // unlock mutex
    try 
    {
        mutex.unlock();
    }
    catch (sbb::NamedMutexException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(!threw_exception);
    // Wait for the threads to finish
    child.join();
    // Check that i is 2 because the child can now increment it
    EXPECT_EQ(i, 2);
    try 
    {
        mutex.remove();
    }
    catch (sbb::NamedMutexException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(!threw_exception);
}

/// <summary>
/// Test NamedMutex try locking
/// </summary>
TEST(NamedMutex, TryLock)
{
    // Create a mutex and lock it
    sbb::NamedMutex mutex(NAME);
    int32_t i = 0;
    bool threw_exception = false;
    try
    {
        mutex.lock();
    }
    catch (sbb::NamedMutexException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(!threw_exception);
    // Create a thread that tries to unlock the mutex 
    // and increment i if it succeeds
    auto func = [](int32_t* i) -> void {
        sbb::NamedMutex mutex2(NAME);
        if (mutex2.try_lock())
        { 
            if (i)
            {
                (*i)++;
            }
            mutex2.unlock();
        }
    };
    // Increment i if the mutex is free, this should fail
    {
        std::thread child(func, &i);
        child.join();
    }
    EXPECT_EQ(i, 0);
    // Unlock the mutex
    try
    {
        mutex.unlock();
    }
    catch (sbb::NamedMutexException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(!threw_exception);
    // Increment i if the mutex is free, this should succeed
    {
        std::thread child(func, &i);
        child.join();
    }
    EXPECT_EQ(i, 1);
    try 
    {
        mutex.remove();
    }
    catch (sbb::NamedMutexException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(!threw_exception);
}

/// <summary>
/// Test NamedMutex timed locking
/// </summary>
TEST(NamedMutex, TimedLock)
{
    sbb::NamedMutex mutex(NAME);
    int32_t i = 0;
    bool threw_exception = false;
    try
    {
        mutex.lock();
    }
    catch (sbb::NamedMutexException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(!threw_exception);
    // Create a thread that tries to unlock the mutex 
    // and increment i if it succeeds
    auto func = [](int32_t* i) -> void {
        sbb::NamedMutex mutex2(NAME);
        if (mutex2.try_lock(std::chrono::milliseconds(10)))
        { 
            if (i)
            {
                (*i)++;
            }
            mutex2.unlock();
        }
    };
    {
        std::thread child(func, &i);
        child.join();
    }
    EXPECT_EQ(i, 0);
    try
    {
        mutex.unlock();
    }
    catch (sbb::NamedMutexException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(!threw_exception);
    {
        std::thread child(func, &i);
        child.join();
    }
    EXPECT_EQ(i, 1);
    try
    {
        mutex.remove();
    }
    catch (sbb::NamedMutexException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(!threw_exception);
}
