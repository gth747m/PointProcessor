#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "PointLib/Data.h"
#include "PointLib/System/SharedMemory.h"
#include "Points/PointIdTest.h"
#include "System/NamedMutexTest.h"
#include "System/SharedMemoryTest.h"

int main(void)
{
    assert(data != NULL);
    shared_memory_test();
    named_mutex_test();
    pid_table_test();
}
