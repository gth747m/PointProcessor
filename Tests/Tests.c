#include <stdio.h>

#include "PidTableTest.h"
#include "NamedMutexTest.h"
#include "SharedMemoryTest.h"

int main(void)
{
    pid_table_test();
    named_mutex_test();
    shared_memory_test();
}
