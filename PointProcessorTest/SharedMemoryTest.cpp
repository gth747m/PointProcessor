#include "pch.h"

static const char* const NAME = "MySharedMemory";

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

/// <summary>
/// Test closing shared memory
/// </summary>
TEST(SharedMemory, Clear)
{
    SharedMemory shm;
    int32_t status = shared_memory_get(&shm, NAME, sizeof(SharedMemory));
    ASSERT_TRUE((status == SHM_CREATED) || (status == SHM_SUCCESS));
    status = shared_memory_close(&shm);
    ASSERT_EQ(status, SHM_SUCCESS);
}

/// <summary>
/// Test creating shared memory
/// </summary>
TEST(SharedMemory, Create)
{
    SharedMemory shm;
    int32_t status = shared_memory_get(&shm, NAME, sizeof(SharedMemory));
    ASSERT_EQ(status, SHM_CREATED);
    status = shared_memory_close(&shm);
    ASSERT_EQ(status, SHM_SUCCESS);
}

/// <summary>
/// Test functions passed a NULL SharedMemory pointer
/// </summary>
TEST(SharedMemory, Null)
{
    int32_t status = shared_memory_get(NULL, NAME, sizeof(SharedMemory));
    ASSERT_EQ(status, SHM_NULL);
    status = shared_memory_close(NULL);
    ASSERT_EQ(status, SHM_NULL);
}

/// <summary>
/// Test obtaining existing shared memory
/// </summary>
TEST(SharedMemory, Get)
{
    SharedMemory shm;
    SharedMemory shm2;
    int32_t status = shared_memory_get(&shm, NAME, sizeof(SharedMemory));
    ASSERT_EQ(status, SHM_CREATED);
    status = shared_memory_get(&shm2, NAME, sizeof(SharedMemory));
    ASSERT_EQ(status, SHM_SUCCESS);
    status = shared_memory_close(&shm);
    ASSERT_EQ(status, SHM_SUCCESS);
}

/// <summary>
/// Test shared memory passed too long of a name
/// </summary>
TEST(SharedMemory, LongName)
{
    SharedMemory shm;
    char name[(SHM_NAME_LEN * 2) + 1] = { 0 };
    int32_t status = 0;
    random_name(name, (SHM_NAME_LEN * 2) + 1);
    status = shared_memory_get(&shm, name, sizeof(SharedMemory));
    ASSERT_EQ(status, SHM_NAME_TOO_LONG);
}
