#pragma once

#include <stdint.h>

#include "PointLib/PointLib.h"

/// <summary>
/// Possible Int statuses
/// </summary>
enum IntStatusCode
{
    /// <summary>
    /// Argument was null
    /// </summary>
    INT_POINT_NULL          = -4,
    /// <summary>
    /// Point is not a Integer
    /// </summary>
    INT_POINT_INVALID_TYPE  = -3,
    /// <summary>
    /// Index was out of range
    /// </summary>
    INT_POINT_INVALID_INDEX = -2,
    /// <summary>
    /// Generic failure
    /// </summary>
    INT_POINT_FAILURE       = -1,
    /// <summary>
    /// Success
    /// </summary>
    INT_POINT_SUCCESS       = 0
};

///<summary>
/// Get the current value of a integer point
///</summary>
///<param name="index">Point index</param>
///<param name="value">Current value</param>
///<returns>IntStatusCode</returns>
POINTLIB_API int32_t int_get_value(
    uint32_t index,
    int32_t* value);

///<summary>
/// Get the current quality of a integer point
///</summary>
///<param name="index">Point index</param>
///<param name="quality">Current quality</param>
///<returns>IntStatusCode</returns>
POINTLIB_API int32_t int_get_quality(
    uint32_t index, 
    int32_t* quality);

///<summary>
/// Get the current value/quality of a integer point
///</summary>
///<param name="index">Point index</param>
///<param name="value">Current value</param>
///<param name="quality">Current quality</param>
///<returns>IntStatusCode</returns>
POINTLIB_API int32_t int_get_value_quality(
    uint32_t index,
    int32_t* value,
    int32_t* quality);

///<summary>
/// Set the current value of a integer point
///</summary>
///<param name="index">Point index</param>
///<param name="value">Current value</param>
///<returns>IntStatusCode</returns>
POINTLIB_API int32_t int_set_value(
    uint32_t index, 
    int32_t  value);

///<summary>
/// Set the current quality of a integer point
///</summary>
///<param name="index">Point index</param>
///<param name="quality">Current quality</param>
///<returns>IntStatusCode</returns>
POINTLIB_API int32_t int_set_quality(
    uint32_t index, 
    int32_t  quality);

///<summary>
/// Set the current value/quality of a integer point
///</summary>
///<param name="index">Point index</param>
///<param name="value">Current value</param>
///<param name="quality">Current quality</param>
///<returns>IntStatusCode</returns>
POINTLIB_API int32_t int_set_value_quality(
    uint32_t index,
    int32_t  value,
    int32_t  quality);
