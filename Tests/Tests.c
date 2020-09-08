#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Data.h"
#include "System/SharedMemory.h"
#include "Points/PointIdTest.h"
#include "System/NamedMutexTest.h"
#include "System/SharedMemoryTest.h"

#define SHARED_MEM_NAME "PointLibShm"

int main(void)
{
    SharedMemory shm;
    shared_memory_get(&shm, SHARED_MEM_NAME, sizeof(Data));
    data = shm.memory;
    assert(data != NULL);
    shared_memory_test();
    named_mutex_test();
    pid_table_test();
    shared_memory_close(&shm);
}
