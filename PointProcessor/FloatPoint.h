#pragma once

#include <stdint.h>

/// <summary>
/// Possible Float statuses
/// </summary>
enum FloatStatusCode
{
    /// <summary>
    /// Argument was null
    /// </summary>
    FLOAT_POINT_NULL          = -4,
    /// <summary>
    /// Point is not a Float
    /// </summary>
    FLOAT_POINT_INVALID_TYPE  = -3,
    /// <summary>
    /// Index was out of range
    /// </summary>
    FLOAT_POINT_INVALID_INDEX = -2,
    /// <summary>
    /// Generic failure
    /// </summary>
    FLOAT_POINT_FAILURE       = -1,
    /// <summary>
    /// Success
    /// </summary>
    FLOAT_POINT_SUCCESS       = 0
};

///<summary>
/// Get the current value of a float point
///</summary>
///<param name="index">Point index</param>
///<param name="value">Current value</param>
///<returns>FloatStatusCode</returns>
int32_t float_get_value(
    uint32_t index,
    float*   value);

///<summary>
/// Get the current quality of a float point
///</summary>
///<param name="index">Point index</param>
///<param name="quality">Current quality</param>
///<returns>FloatStatusCode</returns>
int32_t float_get_quality(
    uint32_t index, 
    int32_t* quality);

///<summary>
/// Get the current value/quality of a float point
///</summary>
///<param name="index">Point index</param>
///<param name="value">Current value</param>
///<param name="quality">Current quality</param>
///<returns>FloatStatusCode</returns>
int32_t float_get_value_quality(
    uint32_t index,
    float*   value,
    int32_t* quality);

///<summary>
/// Set the current value of a float point
///</summary>
///<param name="index">Point index</param>
///<param name="value">Current value</param>
///<returns>FloatStatusCode</returns>
int32_t float_set_value(
    uint32_t index, 
    float    value);

///<summary>
/// Set the current quality of a float point
///</summary>
///<param name="index">Point index</param>
///<param name="quality">Current quality</param>
///<returns>FloatStatusCode</returns>
int32_t float_set_quality(
    uint32_t index, 
    int32_t  quality);

///<summary>
/// Set the current value/quality of a float point
///</summary>
///<param name="index">Point index</param>
///<param name="value">Current value</param>
///<param name="quality">Current quality</param>
///<returns>FloatStatusCode</returns>
int32_t float_set_value_quality(
    uint32_t index,
    float    value,
    int32_t  quality);
