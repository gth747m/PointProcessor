#pragma once

#include <stdbool.h>
#include <stdint.h>

/// <summary>
/// Possible Bool statuses
/// </summary>
enum BoolStatusCode
{
    /// <summary>
    /// Argument was null
    /// </summary>
    BOOL_POINT_NULL          = -4,
    /// <summary>
    /// Point is not a Boolean
    /// </summary>
    BOOL_POINT_INVALID_TYPE  = -3,
    /// <summary>
    /// Index was out of range
    /// </summary>
    BOOL_POINT_INVALID_INDEX = -2,
    /// <summary>
    /// Generic failure
    /// </summary>
    BOOL_POINT_FAILURE       = -1,
    /// <summary>
    /// Success
    /// </summary>
    BOOL_POINT_SUCCESS       = 0
};

///<summary>
/// Get the current value of a boolean point
///</summary>
///<param name="index">Point index</param>
///<param name="value">Current value</param>
///<returns>BoolStatusCode</returns>
int32_t bool_get_value(
    int32_t index,
    bool*   value);

///<summary>
/// Get the current quality of a boolean point
///</summary>
///<param name="index">Point index</param>
///<param name="quality">Current quality</param>
///<returns>BoolStatusCode</returns>
int32_t bool_get_quality(
    int32_t  index, 
    int32_t* quality);

///<summary>
/// Get the current value/quality of a boolean point
///</summary>
///<param name="index">Point index</param>
///<param name="value">Current value</param>
///<param name="quality">Current quality</param>
///<returns>BoolStatusCode</returns>
int32_t bool_get_value_quality(
    int32_t  index,
    bool*    value,
    int32_t* quality);

///<summary>
/// Set the current value of a boolean point
///</summary>
///<param name="index">Point index</param>
///<param name="value">Current value</param>
///<returns>BoolStatusCode</returns>
int32_t bool_set_value(
    int32_t index, 
    bool    value);

///<summary>
/// Set the current quality of a boolean point
///</summary>
///<param name="index">Point index</param>
///<param name="quality">Current quality</param>
///<returns>BoolStatusCode</returns>
int32_t bool_set_quality(
    int32_t index, 
    int32_t quality);

///<summary>
/// Set the current value/quality of a boolean point
///</summary>
///<param name="index">Point index</param>
///<param name="value">Current value</param>
///<param name="quality">Current quality</param>
///<returns>BoolStatusCode</returns>
int32_t bool_set_value_quality(
    int32_t index,
    bool    value,
    int32_t quality);