#pragma once

/// <summary>
/// Shared memory name for this libraries data
/// </summary>
#define SHARED_MEM_NAME "PointLibShm"

/// <summary>
/// Max number of PIDs 
/// As # of PIDs approaches MAX_POINTS the performance 
/// of the insertions and lookups will degrade
/// </summary>
#define MAX_POINTS 500000

/// <summary>
/// Max string length for a PID
/// </summary>
#define PID_LEN 32