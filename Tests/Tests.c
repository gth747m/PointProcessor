#include <stdio.h>

#include "PidTableTest.h"
#include "NamedMutexTest.h"
#include "SharedMemoryTest.h"

int main(void)
{
    shared_memory_test();
    named_mutex_test();
    pid_table_test();
}
