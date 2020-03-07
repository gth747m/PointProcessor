#include "PidTableTest.h"

#include "PidTable.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
/// Put a random string of length len in pid
/// </summary>
/// <param name="pid">PID string to fill in</param>
/// <param name="len">String length</param>
static void random_pid(char* pid, size_t len)
{
    for (size_t i = 0; i < (len - 1); i++)
    {
        pid[i] = random_char();
    }
    pid[(len - 1)] = '\0';
}

/// <summary>
/// Insert a number of random strings into a PidTable
/// </summary>
/// <param name="table">PidTable to insert into</param>
/// <param name="num_inserts">Number of random strings to insert</param>
/// <param name="insert_successes">Number of successful inserts</param>
/// <param name="insert_failures">Number of failed inserts</param>
static void pid_table_insert_random(
    PidTable* table, 
    uint32_t  num_inserts,
    uint32_t* insert_successes,
    uint32_t* insert_failures)
{
    char** pids = (char**)malloc(sizeof(char *) * num_inserts);
    uint32_t failed = 0;
    uint32_t succeeded = 0;
    assert(table != NULL);
    assert(pids != NULL);
    for (size_t i = 0; i < num_inserts; i++)
    {
        pids[i] = (char*)malloc(sizeof(char) * PID_LEN);
        assert(pids[i] != NULL);
        random_pid(pids[i], PID_LEN);
    }
    for (uint32_t i = 0; i < num_inserts; i++)
    {
        if (pid_table_insert(table, pids[i], i) == PID_SUCCESS)
            succeeded++;
        else
            failed++;
    }
    *insert_successes = succeeded;
    *insert_failures = failed;
}

/// <summary>
/// Test PidTable functions passed a NULL table
/// </summary>
static void pid_table_test_null_table()
{
    printf("    Test NULL PidTable...            ");
    int32_t status = 0;
    pid_table_init(NULL);
    pid_table_free(NULL);
    status = pid_table_insert(NULL, "TEST", 0);
    assert(status == PID_TABLE_NULL);
    status = pid_table_get_index(NULL, "TEST", 0);
    assert(status == PID_TABLE_NULL);
    puts("Finished.");
}

/// <summary>
/// Test PidTable functions passed a NULL PID
/// </summary>
static void pid_table_test_null_pid()
{
    printf("    Test NULL PID...                 ");
    int32_t status = 0;
    PidTable* table = pid_table_create();
    status = pid_table_insert(table, NULL, 0);
    assert(status == PID_NULL);
    status = pid_table_get_index(table, NULL, 0);
    assert(status == PID_NULL);
    puts("Finished.");
}

/// <summary>
/// Test PidTable functions passed a too long PID
/// </summary>
static void pid_table_test_long_pid()
{
    printf("    Test PID too long...             ");
    int32_t status = 0;
    PidTable* table = pid_table_create();
    char pid[PID_LEN + 1] = { 0 };
    for (uint32_t i = 0; i < PID_LEN + 1; i++)
    {
        pid[i] = 'a';
    }
    status = pid_table_insert(table, pid, 0);
    assert(status == PID_TOO_LONG);
    status = pid_table_get_index(table, pid, 0);
    assert(status == PID_TOO_LONG);
    puts("Finished.");
}

/// <summary>
/// Test looking up a PID not in the table
/// </summary>
static void pid_table_test_not_found()
{
    printf("    Test PID not found...            ");
    char pid[PID_LEN] = { 0 };
    int32_t status = 0;
    uint32_t index = rand();
    uint32_t lookup = 0;
    PidTable* table = pid_table_create();
    random_pid(pid, PID_LEN);
    status = pid_table_insert(table, pid, index);
    assert(status == PID_SUCCESS);
    status = pid_table_get_index(table, "a", &lookup);
    assert(status == PID_NOT_FOUND);
    pid_table_free(table);
    puts("Finished.");
}

/// <summary>
/// Test looking up a PID
/// </summary>
static void pid_table_test_lookup()
{
    printf("    Test PID lookup...               ");
    char pid[PID_LEN] = { 0 };
    int32_t status = 0;
    uint32_t index = rand();
    uint32_t lookup = 0;
    PidTable* table = pid_table_create();
    random_pid(pid, PID_LEN);
    status = pid_table_insert(table, pid, index);
    assert(status == PID_SUCCESS);
    status = pid_table_get_index(table, pid, &lookup);
    assert(status == PID_SUCCESS);
    assert(index == lookup);
    pid_table_free(table);
    puts("Finished.");
}

/// <summary>
/// Test trying to add a duplicate PID
/// </summary>
static void pid_table_test_duplicate()
{
    printf("    Test inserting duplicate PID...  ");
    PidTable* table = pid_table_create();
    char pid[PID_LEN] = { 0 };
    int32_t status = 0;
    random_pid(pid, PID_LEN);
    status = pid_table_insert(table, pid, 0);
    assert(status == PID_SUCCESS);
    status = pid_table_insert(table, pid, 0);
    assert(status == PID_DUPLICATE);
    pid_table_free(table);
    puts("Finished.");
}

/// <summary>
/// Test filling table to half full
/// </summary>
static void pid_table_test_half()
{
    printf("    Test half filling table...       ");
    PidTable* table = pid_table_create();
    uint32_t failures = 0;
    uint32_t num_pids = (int)(MAX_PIDS / 2);
    uint32_t successes = 0;
    pid_table_insert_random(
        table, num_pids, &successes, &failures);
    assert(successes == num_pids);
    assert(failures == 0);
    assert(table->count == num_pids);
    pid_table_free(table);
    puts("Finished.");
}

/// <summary>
/// Test filling to table to max
/// </summary>
static void pid_table_test_full()
{
    printf("    Test filling table...            ");
    PidTable* table = pid_table_create();
    uint32_t failures = 0;
    uint32_t successes = 0;
    pid_table_insert_random(
        table, MAX_PIDS, &successes, &failures);
    assert(successes == MAX_PIDS);
    assert(failures == 0);
    assert(table->count == MAX_PIDS);
    pid_table_free(table);
    puts("Finished.");
}

/// <summary>
/// Test overfilling the table by half
/// </summary>
static void pid_table_test_overfill()
{
    printf("    Test overfilling table...        ");
    PidTable* table = pid_table_create();
    uint32_t failures = 0;
    uint32_t num_pids = (int)(MAX_PIDS / 2);
    uint32_t successes = 0;
    pid_table_insert_random(
        table, MAX_PIDS + num_pids, &successes, &failures);
    assert(successes == MAX_PIDS);
    assert(failures == num_pids);
    assert(table->count == MAX_PIDS);
    pid_table_free(table);
    puts("Finished.");
}

/// <summary>
/// Run a suite of PidTable unit tests
/// </summary>
void pid_table_test()
{
    puts("Testing PidTable...");
    srand((unsigned)time(NULL));
    pid_table_test_null_table();
    pid_table_test_null_pid();
    pid_table_test_long_pid();
    pid_table_test_not_found();
    pid_table_test_lookup();
    pid_table_test_duplicate();
    pid_table_test_half();
    pid_table_test_full();
    pid_table_test_overfill();
    puts("Finished testing PidTable.");
}

