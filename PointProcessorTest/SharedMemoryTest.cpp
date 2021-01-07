#include "pch.h"

static const char* const NAME = "MyTestSharedMemory";

/// <summary>
/// Test creating shared memory
/// </summary>
TEST(SharedMemory, Create)
{
    std::unique_ptr<SharedMemory<int>> shm;
    SharedMemory<int>* shm2;
    bool threw_exception = false;
    try
    {
        shm = std::make_unique<SharedMemory<int>>(NAME);
    }
    catch (SharedMemoryException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(!threw_exception);
    try
    {
        shm2 = new SharedMemory<int>(NAME);
    }
    catch (SharedMemoryException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(!threw_exception);
    try
    {
        delete shm2;
    }
    catch (SharedMemoryException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(!threw_exception);
}

TEST(SharedMemory, SharedIntIncrement)
{
    SharedMemory<int> shm(NAME);
    SharedMemory<int> shm2(NAME);
    bool threw_exception = false;
    try
    {
        ASSERT_EQ(*shm.get(), 0);
        ASSERT_EQ(*shm2.get(), 0);
        (*shm.get())++;
        ASSERT_EQ(*shm.get(), 1);
        ASSERT_EQ(*shm2.get(), 1);
        (*shm2.get())++;
        ASSERT_EQ(*shm.get(), 2);
        ASSERT_EQ(*shm2.get(), 2);
    }
    catch (SharedMemoryException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(!threw_exception);
}
