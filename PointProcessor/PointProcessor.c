
#ifdef __linux__
#    define _GNU_SOURCE
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "PidTable.h"

#define TOTAL_PIDS 60000

static char random_char()
{
    const char* chars = "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    return chars[rand() % 62];
}

static void random_pid(char* pid, size_t len)
{
    for (size_t i = 0; i < (len - 1); i++)
    {
        pid[i] = random_char();
    }
    pid[(len - 1)] = '\0';
}

int main()
{
    PidTable *table = (PidTable *)malloc(sizeof(PidTable));
    char** pids = (char**)malloc(sizeof(char *) * TOTAL_PIDS);
    uint32_t failed = 0;
    uint32_t index = 0;
    uint32_t ret = 0;
    double tdiff = 0;
    struct timespec tstart = {0, 0};
    struct timespec tend = {0, 0};
    if (table == NULL || pids == NULL)
    {
        fprintf(stderr, "Failed to allocate memory.");
        exit(1);
    }
    init_pid_table(table);
    for (size_t i = 0; i < TOTAL_PIDS; i++)
    {
        pids[i] = (char*)malloc(sizeof(char) * PID_LEN);
        if (pids[i] == NULL)
        {
            fprintf(stderr, "Failed to allocate memory.");
            exit(1);
        }
        random_pid(pids[i], PID_LEN);
    }
    clock_gettime(CLOCK_MONOTONIC, &tstart);
    for (uint32_t i = 0; i < TOTAL_PIDS; i++)
    {
        if (insert_pid(table, pids[i], i) != PID_SUCCESS)
            failed++;
    }
    clock_gettime(CLOCK_MONOTONIC, &tend);
    tdiff = ((double)tend.tv_sec + 1.0e-9 * tend.tv_nsec) -
        ((double)tstart.tv_sec + 1.0e-9 * tstart.tv_nsec);
    printf("Time (us)    = %f\n", tdiff);
    printf("Total        = %d\n", TOTAL_PIDS);
    printf("Failures     = %d\n", failed);
    printf("Avg Ins (us) = %f\n", ((double)tdiff / (double)(TOTAL_PIDS - failed)));
    printf("Done\n");
    clock_gettime(CLOCK_MONOTONIC, &tstart);
    ret = get_pid_index(table, pids[2345], &index);
    clock_gettime(CLOCK_MONOTONIC, &tend);
    tdiff = ((double)tend.tv_sec + 1.0e-9 * tend.tv_nsec) -
        ((double)tstart.tv_sec + 1.0e-9 * tstart.tv_nsec);
    if (index != 0)
        printf("'%s' found with index %u in '%f' (us)\n",
            pids[2345], index, tdiff);
    else
        fprintf(stderr, "Couldn't find '%s': Got return code of %d\n", pids[2345], ret);
    index = 0;
    clock_gettime(CLOCK_MONOTONIC, &tstart);
    ret = get_pid_index(table, pids[5432], &index);
    clock_gettime(CLOCK_MONOTONIC, &tend);
    tdiff = ((double)tend.tv_sec + 1.0e-9 * tend.tv_nsec) -
        ((double)tstart.tv_sec + 1.0e-9 * tstart.tv_nsec);
    if (index != 0)
        printf("'%s' found with index %u in '%f' (us)\n",
            pids[5432], index, tdiff);
    else
        fprintf(stderr, "Couldn't find '%s': Got return code of %d\n", pids[5432], ret);
}
