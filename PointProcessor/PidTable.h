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
#define MAX_PIDS 500000

/// <summary>
/// Point ID structure
/// </summary>
typedef struct PidEntry {
    /// <summary>
    /// Point ID
    /// </summary>
    char pid[PID_LEN];
    /// <summary>
    /// Index of this PID in some other table
    /// </summary>
    uint32_t index;
    /// <summary>
    /// Is this entry in use?
    /// </summary>
    bool is_used;
} PidEntry;

/// <summary>
/// Possible PidTable statuses
/// </summary>
enum PidTableStatus
{
    /// <summary>
    /// PID name provided was null
    /// </summary>
    PID_NULL            = -8,
    /// <summary>
    /// PidTable provided was null
    /// </summary>
    PID_TABLE_NULL      = -7,
    /// <summary>
    /// PID name was too long
    /// </summary>
    PID_TOO_LONG        = -6,
    /// <summary>
    /// PID name is a duplicate
    /// </summary>
    PID_DUPLICATE       = -5,
    /// <summary>
    /// PID index calculated was out of range (should never happen)
    /// </summary>
    PID_INVALID_INDEX  = -4,
    /// <summary>
    /// PidTable is full
    /// </summary>
    PID_TABLE_FULL      = -3,
    /// <summary>
    /// PID name doesn't exist in PidTable
    /// </summary>
    PID_NOT_FOUND       = -2,
    /// <summary>
    /// Generic failure
    /// </summary>
    PID_FAILURE         = -1,
    /// <summary>
    /// PidTable operation successful
    /// </summary>
    PID_SUCCESS         = 0
};

/// <summary>
/// Table of PIDs
/// </summary>
typedef struct PidTable
{
    /// <summary>
    /// PidEntry array
    /// </summary>
    PidEntry entries[MAX_PIDS];
    /// <summary>
    /// Current count of entries
    /// </summary>
    uint32_t count;
} PidTable;

/// <summary>
/// Create a PidTable in local memory
/// </summary>
/// <returns>Pointer to a PidTable</returns>
PidTable* pid_table_create();

/// <summary>
/// Initialize a PidTable
/// </summary>
void pid_table_init(PidTable* table);

/// <summary>
/// Free memory allocated by pid_table_create
/// </summary>
/// <param name="table">Pointer to a PidTable</param>
void pid_table_free(PidTable* table);

/// <summary>
/// Insert a new PID into the table
/// </summary>
/// <param name="table">PID table to insert into</param>
/// <param name="pid">Name of PID to insert</param>
/// <param name="index">PID index to insert</param>
/// <returns>Status as defined in PidTableStatus</returns>
int32_t pid_table_insert(PidTable* table, const char* const pid, uint32_t index);

/// <summary>
/// Get the index of a PID in the table
/// </summary>
/// <param name="table">PID table to insert into</param>
/// <param name="pid">Name of PID</param>
/// <param name="index">PID index from table</param>
/// <returns>Status as defined in PidTableStatus</returns>
int32_t pid_table_get_index(const PidTable* table, const char* const pid, uint32_t* index);
