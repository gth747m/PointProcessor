#include "SharedMemoryTest.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "System/SharedMemory.h"

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
/// Closing any previously open copy of our test shared memory
/// </summary>
static void shared_memory_test_clear()
{
    printf("    Clearing previous...             ");
    SharedMemory shm;
    int32_t status = shared_memory_get(&shm, NAME, sizeof(SharedMemory));
    assert((status == SHM_CREATED) || (status == SHM_SUCCESS));
    status = shared_memory_close(&shm);
    assert(status == SHM_SUCCESS);
    puts("Finished.");
}

/// <summary>
/// Test creating shared memory
/// </summary>
static void shared_memory_test_create_close()
{
    printf("    Test creating and closing...     ");
    SharedMemory shm;
    int32_t status = shared_memory_get(&shm, NAME, sizeof(SharedMemory));
    assert(status == SHM_CREATED);
    status = shared_memory_close(&shm);
    assert(status == SHM_SUCCESS);
    puts("Finished.");
}

/// <summary>
/// Test functions passed a NULL SharedMemory pointer
/// </summary>
static void shared_memory_test_null()
{
    printf("    Test creating NULL...            ");
    int32_t status = shared_memory_get(NULL, NAME, sizeof(SharedMemory));
    assert(status == SHM_NULL);
    status = shared_memory_close(NULL);
    assert(status == SHM_NULL);
    puts("Finished.");
}

/// <summary>
/// Test obtaining existing shared memory
/// </summary>
static void shared_memory_test_get()
{
    printf("    Test getting existing...         ");
    SharedMemory shm;
    SharedMemory shm2;
    int32_t status = shared_memory_get(&shm, NAME, sizeof(SharedMemory));
    assert(status == SHM_CREATED);
    status = shared_memory_get(&shm2, NAME, sizeof(SharedMemory));
    assert(status == SHM_SUCCESS);
    status = shared_memory_close(&shm);
    assert(status == SHM_SUCCESS);
    puts("Finished.");
}

/// <summary>
/// Test shared memory passed too long of a name
/// </summary>
static void shared_memory_test_long_name()
{
    printf("    Test creating long name...       ");
    SharedMemory shm;
    char name[(SHM_NAME_LEN * 2) + 1] = { 0 };
    int32_t status = 0;
    random_name(name, (SHM_NAME_LEN * 2) + 1);
    status = shared_memory_get(&shm, name, sizeof(SharedMemory));
    assert(status == SHM_NAME_TOO_LONG);
    puts("Finished.");
}

/// <summary>
/// Run a suite of SharedMemory unit tests
/// </summary>
void shared_memory_test()
{
    puts("Testing SharedMemory...");
    shared_memory_test_clear();
    shared_memory_test_create_close();
    shared_memory_test_null();
    shared_memory_test_get();
    shared_memory_test_long_name();
    puts("Finished testing SharedMemory.");
}
