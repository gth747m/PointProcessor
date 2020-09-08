#include "PointId.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Data.h"

/// <summary>
/// Get the index of the PID (before resolving collisions)
/// using MurmurHash3_32 by Austin Appleby (given to public domain)
/// </summary>
/// <param name="">PID name to hash</param>
/// <returns>PID index</returns>
static int32_t hash_pid(
    const char* const pid, 
    uint32_t*         index)
{
    // If our pid table isn't there
    if (pid == NULL)
    {
        return PID_NULL;
    }
    uint8_t pid_copy[PID_LEN] = { 0 };
    const size_t len = strlen(pid);
    memcpy(pid_copy, pid, len);
    const uint8_t* key = (uint8_t *)pid_copy;
    uint32_t h = 0;
    if (len > 3) 
    {
        size_t i = len >> 2;
        do {
            uint32_t k;
            memcpy(&k, key, sizeof(uint32_t));
            key += sizeof(uint32_t);
            k *= 0xcc9e2d51;
            k = (k << 15) | (k >> 17);
            k *= 0x1b873593;
            h ^= k;
            h = (h << 13) | (h >> 19);
            h = h * 5 + 0xe6546b64;
        } while (--i);
    }
    if (len & 3) 
    {
        size_t i = len & 3;
        uint32_t k = 0;
        do {
            k <<= 8;
            k |= key[i - 1];
        } while (--i);
        k *= 0xcc9e2d51;
        k = (k << 15) | (k >> 17);
        k *= 0x1b873593;
        h ^= k;
    }
    h ^= len;
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;
    *index = h;
    return PID_SUCCESS;
}

/// <summary>
/// Initialize a PidTable
/// </summary>
POINT_API void pid_table_init()
{ 
    memset(data->pointIds, 0, sizeof(data->pointIds)); 
}

/// <summary>
/// Insert a new PID into the table
/// </summary>
/// <param name="pid">Name of PID to insert</param>
/// <param name="pid">PID index to insert</param>
/// <returns>Status as defined in PidTableStatus</returns>
POINT_API int32_t pid_table_insert(
    const char* const pid, 
    uint32_t          index)
{
    uint32_t count = 0;
    // If you didn't pass anything
    if (pid == NULL)
        return PID_NULL;
    // The PID is too long to store 
    if (strlen(pid) > PID_LEN - 1)
        return PID_TOO_LONG;
    // If the table is full already
    if (data->pointCount >= MAX_POINTS)
        return PID_TABLE_FULL;
    // Hash the PID to get the insert_index
    uint32_t insert_index = 0;
    hash_pid(pid, &insert_index);
    insert_index = insert_index % MAX_POINTS;
    // If the insert_index is out of bounds (should never happen)
    if (insert_index >= MAX_POINTS)
        return PID_INVALID_INDEX;
    // If there is a collision
    if (data->pointIds[insert_index].is_used)
    {
        // Find the next open space or if this 
        // pid already exists
        for (uint32_t i = 0; i < MAX_POINTS; i++)
        {
            count++;
            // If this insert_index is used
            if (data->pointIds[insert_index].is_used)
            {
                // If this insert_index matches this pid
                if (strncmp(data->pointIds[insert_index].pid, pid, PID_LEN) == 0)
                {
                    // Can't insert, it already exists
                    return PID_DUPLICATE;
                }
            }
            // Found an empty insert_index
            else
            {
                // Copy the PID 
#ifdef __linux__
                strncpy(data->pointIds[insert_index].pid, pid, PID_LEN);
#elif defined _WIN32
                strncpy_s(data->pointIds[insert_index].pid, PID_LEN, pid, PID_LEN);
#endif
                // Ensure its null terminated
                data->pointIds[insert_index].pid[PID_LEN - 1] = 0;
                // Set the index
                data->pointIds[insert_index].index = index;
                // Set it as in use
                data->pointIds[insert_index].is_used = true;
                // Increment table count
                data->pointCount++;
                // Return success
                return PID_SUCCESS;
            }
            // Move to the next insert_index or 
            // wrap back to the start
            if (insert_index < (MAX_POINTS - 1))
            {
                insert_index++;
            }
            else
            {
                insert_index = 0;
            }
        }
    }
    // Else no collision
    else
    {
        // Copy the PID 
#ifdef __linux__
        strncpy(data->pointIds[insert_index].pid, pid, PID_LEN);
#elif defined _WIN32
        strncpy_s(data->pointIds[insert_index].pid, PID_LEN, pid, PID_LEN);
#endif
        // Ensure its null terminated
        data->pointIds[insert_index].pid[PID_LEN - 1] = 0;
        // Set the insert_index
        data->pointIds[insert_index].index = index;
        // Set it as in use
        data->pointIds[insert_index].is_used = true;
        // Increment table count
        data->pointCount++;
        // Return success
        return PID_SUCCESS;
    }
    // The table is full
    if (count >= MAX_POINTS)
        return PID_TABLE_FULL;
    // Shouldn't get here
    return PID_FAILURE;
}

/// <summary>
/// Get the index of a PID in the table
/// </summary>
/// <param name="pid">Name of PID</param>
/// <param name="index">PID index from table</param>
/// <returns>Status as defined in PidTableStatus</returns>
POINT_API int32_t pid_table_get_index(
    const char* const pid, 
    uint32_t*         index)
{
    // If you didn't pass anything
    if (pid == NULL)
        return PID_NULL;
    // The PID is too long to store 
    if (strlen(pid) > PID_LEN - 1)
        return PID_TOO_LONG;
    if (index == NULL)
        return PID_FAILURE;
    // Hash the PID to get the insert_index
    uint32_t insert_index = 0;
    hash_pid(pid, &insert_index);
    insert_index = insert_index % MAX_POINTS;
    // If the insert_index is out of bounds (should never happen)
    if (insert_index >= MAX_POINTS)
    {
        return PID_FAILURE;
    }
    // Index in use, may have found the PID
    if (data->pointIds[insert_index].is_used)
    {
        // Find the next open space or if this pid already exists
        for (uint32_t i = 0; i < MAX_POINTS; i++)
        {
            // If this insert_index is used
            if (data->pointIds[insert_index].is_used)
            {
                // If this insert_index matches this pid, 
                // we found it!
                if (strncmp(data->pointIds[insert_index].pid, pid, PID_LEN) == 0)
                {
                    // We found the PID
                    *index = data->pointIds[insert_index].index;
                    return PID_SUCCESS;
                }
            }
            // Found an empty insert_index, PID must not exist
            else
            {
                return PID_NOT_FOUND;
            }
            // Move to the next insert_index or 
            // wrap back to the start
            if (insert_index < (MAX_POINTS - 1))
            {
                insert_index++;
            }
            else
            {
                insert_index = 0;
            }
        }
    }
    return PID_NOT_FOUND;
}
