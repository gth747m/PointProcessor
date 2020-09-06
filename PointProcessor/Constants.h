#pragma once

/// <summary>
/// Max number of PIDs 
/// As # of PIDs approaches MAX_POINTS the performance 
/// of the insertions and lookups will degrade
/// </summary>
#define MAX_POINTS 500000

#pragma region PID_TABLE_REGION
/// <summary>
/// Name to pass to the OS for shared memory
/// </summary>
#define PID_TABLE_NAME "PIDTABLE"

/// <summary>
/// Max string length for a PID
/// </summary>
#define PID_LEN 32

#pragma endregion

