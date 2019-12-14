#include "PidTable.h"

#include <stddef.h>
#include <string.h>

/// <summary>
/// Initialize a PidTable
/// </summary>
void init_pid_table(PidTable * table) { memset(table, 0, sizeof(PidTable)); }

/// <summary>
/// Get the index of the PID (before resolving collisions)
/// using MurmurHash3_32 by Austin Appleby (given to public domain)
/// </summary>
/// <param name="">PID name to hash</param>
/// <returns>PID index</returns>
int32_t hash_pid(const char * const pid, uint32_t *index)
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
    if (len > 3) {
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
    if (len & 3) {
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
/// Insert a new PID into the table
/// </summary>
/// <param name="table">PID table to insert into</param>
/// <param name="pid">Name of PID to insert</param>
/// <param name="pid">PID index to insert</param>
/// <returns>PidTableStatus</returns>
int32_t insert_pid(PidTable * table, const char * const pid, uint32_t index)
{
    uint32_t count = 0;
    // If our pid table isn't there
    if (table == NULL)
    {
        return PID_TABLE_NULL;
    }
    // If you didn't pass anything
    if (pid == NULL)
        return PID_NULL;
    // The PID is too long to store 
    if (strlen(pid) > PID_LEN - 1)
        return PID_TOO_LONG;
    // Hash the PID to get the insert_index
    uint32_t insert_index = 0;
    hash_pid(pid, &insert_index);
    insert_index = insert_index % MAX_PIDS;
    // If the insert_index is out of bounds (should never happen)
    if (table->size >= MAX_PIDS)
    {
        return PID_INVALID_INDNEX;
    }
    // If there is a collision
    if (table->entries[insert_index].is_used)
    {
        // Find the next open space or if this 
        // pid already exists
        for (uint32_t i = 0; i < MAX_PIDS; i++)
        {
            count++;
            // If this insert_index is used
            if (table->entries[insert_index].is_used)
            {
                // If this insert_index matches this pid
                if (strncmp(table->entries[insert_index].pid, pid, PID_LEN) == 0)
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
                strncpy(table->entries[insert_index].pid, pid, PID_LEN);
#elif defined _WIN32
                strncpy_s(table->entries[insert_index].pid, PID_LEN, pid, PID_LEN);
#endif
                // Ensure its null terminated
                table->entries[insert_index].pid[PID_LEN - 1] = 0;
                // Set the index
                table->entries[insert_index].index = index;
                // Set it as in use
                table->entries[insert_index].is_used = true;
                // Return success
                return PID_SUCCESS;
            }
            // Move to the next insert_index or 
            // wrap back to the start
            if (insert_index < (MAX_PIDS - 1))
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
        strncpy(table->entries[insert_index].pid, pid, PID_LEN);
#elif defined _WIN32
        strncpy_s(table->entries[insert_index].pid, PID_LEN, pid, PID_LEN);
#endif
        // Ensure its null terminated
        table->entries[insert_index].pid[PID_LEN - 1] = 0;
        // Set the insert_index
        table->entries[insert_index].index = index;
        // Set it as in use
        table->entries[insert_index].is_used = true;
        // Return success
        return PID_SUCCESS;
    }
    // The table is full
    if (count >= MAX_PIDS)
        return PID_TABLE_FULL;
    // Shouldn't get here
    return PID_FAILURE;
}

/// <summary>
/// Get the index of a PID in the table
/// </summary>
/// <param name="table">PID table to insert into</param>
/// <param name="pid">Name of PID</param>
/// <param name="index">PID index from table</param>
/// <returns>PidTableStatus</returns>
int32_t get_pid_index(const PidTable * table, const char * const pid, uint32_t * index)
{
    // If our pid table isn't there
    if (table == NULL)
    {
        return PID_TABLE_NULL;
    }
    // If you didn't pass anything
    if (pid == NULL)
        return PID_NULL;
    // The PID is too long to store 
    if (strlen(pid) > PID_LEN - 1)
        return PID_TOO_LONG;
    // Hash the PID to get the insert_index
    uint32_t insert_index = 0;
    hash_pid(pid, &insert_index);
    insert_index = insert_index % MAX_PIDS;
    // If the insert_index is out of bounds (should never happen)
    if (insert_index >= MAX_PIDS)
    {
        return PID_FAILURE;
    }
    // Index in use, may have found the PID
    if (table->entries[insert_index].is_used)
    {
        // Find the next open space or if this pid already exists
        for (uint32_t i = 0; i < MAX_PIDS; i++)
        {
            // If this insert_index is used
            if (table->entries[insert_index].is_used)
            {
                // If this insert_index matches this pid, 
                // we found it!
                if (strncmp(table->entries[insert_index].pid, pid, PID_LEN) == 0)
                {
                    // We found the PID
                    *index = table->entries[insert_index].index;
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
            if (insert_index < (MAX_PIDS - 1))
            {
                insert_index++;
            }
            else
            {
                insert_index = 0;
            }
        }
    }
    return PID_FAILURE;
}

