#include "pch.h"

static const char* const NAME = "MyTestSharedMemory";

/// <summary>
/// Test creating shared memory
/// </summary>
TEST(SharedMemory, Create)
{
    std::unique_ptr<sbb::SharedMemory<int>> shm;
    sbb::SharedMemory<int>* shm2;
    bool threw_exception = false;
    try
    {
        shm = std::make_unique<sbb::SharedMemory<int>>(NAME);
    }
    catch (sbb::SharedMemoryException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(!threw_exception);
    try
    {
        shm2 = new sbb::SharedMemory<int>(NAME);
    }
    catch (sbb::SharedMemoryException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(!threw_exception);
    try
    {
        delete shm2;
    }
    catch (sbb::SharedMemoryException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(!threw_exception);
}

TEST(SharedMemory, SharedIntIncrement)
{
    sbb::SharedMemory<int> shm(NAME);
    sbb::SharedMemory<int> shm2(NAME);
    bool threw_exception = false;
    try
    {
        EXPECT_EQ(*shm.get(), 0);
        EXPECT_EQ(*shm2.get(), 0);
        (*shm.get())++;
        EXPECT_EQ(*shm.get(), 1);
        EXPECT_EQ(*shm2.get(), 1);
        (*shm2.get())++;
        EXPECT_EQ(*shm.get(), 2);
        EXPECT_EQ(*shm2.get(), 2);
    }
    catch (sbb::SharedMemoryException&)
    {
        threw_exception = true;
    }
    ASSERT_TRUE(!threw_exception);
}
