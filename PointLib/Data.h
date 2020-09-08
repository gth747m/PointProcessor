#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "PointLib/PointLib.h"
#include "PointLib/Constants.h"
#include "PointLib/Points/PointId.h"
#include "PointLib/Points/PointType.h"
#include "PointLib/Points/Quality.h"
#include "PointLib/System/SharedMemory.h"

///<summary>
/// Value/Quality pair
///</summary>
typedef struct ValueQuality
{
    /// <summary>
    /// Union of bool, float, & int values
    /// </summary>
    union Value
    {
        /// <summary>
        /// Boolean value
        /// </summary>
        bool    bool_value;
        /// <summary>
        /// Floating point value
        /// </summary>
        float   float_value;
        /// <summary>
        /// Integer value
        /// </summary>
        int32_t int_value;
    } value;
    /// <summary>
    /// Quality
    /// </summary>
    int32_t quality;
} ValueQuality;

/// <summary>
/// Global shared data
/// </summary>
typedef struct Data
{
    /// <summary>
    /// Current number of points
    /// </summary>
    size_t pointCount;
    /// <summary>
    /// Point IDs
    /// </summary>
    PidEntry pointIds[MAX_POINTS];
    /// <summary>
    /// Point Value Types
    /// </summary>
    int32_t pointValueTypes[MAX_POINTS];
    /// <summary>
    /// Point Types
    /// </summary>
    int32_t pointTypes[MAX_POINTS];
    /// <summary>
    /// CVT Table
    /// </summary>
    ValueQuality valuesQualities[MAX_POINTS];
} Data;


/// <summary>
/// Global shared memory instance
/// </summary>
extern POINTLIB_API SharedMemory shm;

/// <summary>
/// Global data instance
/// </summary>
extern POINTLIB_API volatile Data* data;
