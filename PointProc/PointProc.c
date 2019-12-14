#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "PidTable.h"

int main()
{
    PidTable *table = (PidTable *)malloc(sizeof(PidTable));
    FILE *fp = fopen("pids.txt", "r");
    char pids[25000][PID_LEN] = { { '\0' } };
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    uint32_t total = 0;
    uint32_t failed = 0;
    uint32_t index = 0;
    uint32_t ret = 0;
    double tdiff = 0;
    struct timespec tstart = {0, 0};
    struct timespec tend = {0, 0};
    if (fp == NULL)
    {
        fprintf(stderr, "Couldn't open pids.txt\n");
        return EXIT_FAILURE;
    }
    init_pid_table(table);
    while ((read = getline(&line, &len, fp)) != -1)
    {
        line[read - 1] = 0;
        if (read > (PID_LEN - 1))
        {
            fprintf(stderr, "PID '%s' is too long.\n", line);
            fprintf(stderr, "read = %ld > %d\n", read, PID_LEN);
            return EXIT_FAILURE;
        }
        memcpy(pids[total], line, read);
        pids[total][read - 1] = 0;
        total++;
    }
    clock_gettime(CLOCK_MONOTONIC, &tstart);
    for (uint32_t i = 0; i < total; i++)
    {
        if (insert_pid(table, pids[i], i) != PID_SUCCESS)
            failed++;
    }
    clock_gettime(CLOCK_MONOTONIC, &tend);
    tdiff = ((double)tend.tv_sec + 1.0e-9 * tend.tv_nsec) -
        ((double)tstart.tv_sec + 1.0e-9 * tstart.tv_nsec);
    printf("Time (us)    = %f\n", tdiff);
    printf("Total        = %d\n", total);
    printf("Failures     = %d\n", failed);
    printf("Avg Ins (us) = %f\n", ((double)tdiff / (double)(total - failed)));
    printf("Done\n");
    clock_gettime(CLOCK_MONOTONIC, &tstart);
    ret = get_pid_index(table, "CALC002", &index);
    clock_gettime(CLOCK_MONOTONIC, &tend);
    tdiff = ((double)tend.tv_sec + 1.0e-9 * tend.tv_nsec) -
        ((double)tstart.tv_sec + 1.0e-9 * tstart.tv_nsec);
    if (index != 0)
        printf("CALC002 found at index %u in '%f' (us)\n",
            index, tdiff);
    else
        fprintf(stderr, "Couldn't find CALC002: Got return code of %d\n", ret);
    index = 0;
    clock_gettime(CLOCK_MONOTONIC, &tstart);
    ret = get_pid_index(table, "STAT017", &index);
    clock_gettime(CLOCK_MONOTONIC, &tend);
    tdiff = ((double)tend.tv_sec + 1.0e-9 * tend.tv_nsec) -
        ((double)tstart.tv_sec + 1.0e-9 * tstart.tv_nsec);
    if (index != 0)
        printf("STAT017 found at index %u in '%f' (us)\n",
            index, tdiff);
    else
        fprintf(stderr, "Couldn't find STAT017: Got return code of %d\n", ret);
    hash_pid("CALC002", &index);
    printf("CALC002 hash_pid = %u\n", index);
}


