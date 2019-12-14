#pragma once

#include <stdbool.h>
#include <stdint.h>

/// <summary>
/// Name to pass to the OS for shared memory
/// </summary>
#define PID_TABLE_NAME "PIDTABLE"
/// <summary>
/// Max string length for a PID
/// </summary>
#define PID_LEN 32
/// <summary>
/// Max number of PIDs 
/// As # of PIDs approaches MAX_PIDS the performance 
/// of the insertions and lookups will degrade
/// </summary>
#define MAX_PIDS 50000

/// <summary>
/// Point ID structure
/// </summary>
typedef struct PidEntry {
    char pid[PID_LEN];
    uint32_t index;
    bool is_used;
} PidEntry;

enum PidTableStatus
{
    PID_NULL            = -8,
    PID_TABLE_NULL      = -7,
    PID_TOO_LONG        = -6,
    PID_DUPLICATE       = -5,
    PID_INVALID_INDNEX  = -4,
    PID_TABLE_FULL      = -3,
    PID_NOT_FOUND       = -2,
    PID_FAILURE         = -1,
    PID_SUCCESS         = 0
};

typedef struct PidTable
{
    PidEntry entries[MAX_PIDS];
    uint32_t size;
} PidTable;

/// <summary>
/// Initialize a PidTable
/// </summary>
void init_pid_table(PidTable * table);

/// <summary>
/// Get the index of the PID (before resolving collisions)
/// using MurmurHash3_32 by Austin Appleby (given to public domain)
/// </summary>
int32_t hash_pid(const char * pid, uint32_t * index);

/// <summary>
/// Insert a new PID into the table
/// </summary>
/// <param name="table">PID table to insert into</param>
/// <param name="pid">Name of PID to insert</param>
/// <param name="index">PID index to insert</param>
/// <returns>PidTableStatus</returns>
int32_t insert_pid(PidTable * table, const char * const pid, uint32_t index);

/// <summary>
/// Get the index of a PID in the table
/// </summary>
/// <param name="table">PID table to insert into</param>
/// <param name="pid">Name of PID</param>
/// <param name="index">PID index from table</param>
/// <returns>PidTableStatus</returns>
int32_t get_pid_index(const PidTable * table, const char * const pid, uint32_t * index);
