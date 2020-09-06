#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Data.h"
#include "PidTableTest.h"
#include "NamedMutexTest.h"
#include "SharedMemoryTest.h"

int main(void)
{
    data = (Data*)calloc(1, sizeof(Data));
    assert(data != NULL);
    shared_memory_test();
    named_mutex_test();
    pid_table_test();
    free(data);
}
