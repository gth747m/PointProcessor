#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "PointLib/Constants.h"
#include "PointLib/PointLib.h"

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
/// Initialize a PidTable
/// </summary>
POINTLIB_API void pid_table_init();

/// <summary>
/// Insert a new PID into the table
/// </summary>
/// <param name="pid">Name of PID to insert</param>
/// <param name="index">PID index to insert</param>
/// <returns>Status as defined in PidTableStatus</returns>
POINTLIB_API int32_t pid_table_insert(
    const char* const pid, 
    uint32_t          index);

/// <summary>
/// Get the index of a PID in the table
/// </summary>
/// <param name="pid">Name of PID</param>
/// <param name="index">PID index from table</param>
/// <returns>Status as defined in PidTableStatus</returns>
POINTLIB_API int32_t pid_table_get_index(
    const char* const pid, 
    uint32_t*         index);
