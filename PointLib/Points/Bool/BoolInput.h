#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "PointLib.h"

/// <summary>
/// Possible BoolInput statuses
/// </summary>
enum BoolInputStatusCode
{
    /// <summary>
    /// Argument was null
    /// </summary>
    BOOL_INP_NULL          = -4,
    /// <summary>
    /// Point is not a Boolean Input
    /// </summary>
    BOOL_INP_INVALID_TYPE  = -3,
    /// <summary>
    /// Index was out of range
    /// </summary>
    BOOL_INP_INVALID_INDEX = -2,
    /// <summary>
    /// Generic failure
    /// </summary>
    BOOL_INP_FAILURE       = -1,
    /// <summary>
    /// Success
    /// </summary>
    BOOL_INP_SUCCESS       = 0
};

///<summary>
/// Get the current value of a boolean input point
///</summary>
///<param name="index">Point index</param>
///<param name="value">Current value</param>
///<returns>BoolInputStatusCode</returns>
POINT_API int32_t bool_input_get_value(
    uint32_t index, 
    bool*    value);

///<summary>
/// Get the current quality of a boolean input point
///</summary>
///<param name="index">Point index</param>
///<param name="quality">Current quality</param>
///<returns>BoolInputStatusCode</returns>
POINT_API int32_t bool_input_get_quality(
    uint32_t index, 
    int32_t* quality);

///<summary>
/// Get the current value/quality of a boolean input point
///</summary>
///<param name="index">Point index</param>
///<param name="value">Current value</param>
///<param name="quality">Current quality</param>
///<returns>BoolInputStatusCode</returns>
POINT_API int32_t bool_input_get_value_quality(
    uint32_t index, 
    bool*    value,
    int32_t* quality);

///<summary>
/// Set the current value of a boolean input point
///</summary>
///<param name="index">Point index</param>
///<param name="value">Current value</param>
///<returns>BoolInputStatusCode</returns>
POINT_API int32_t bool_input_set_value(
    uint32_t index, 
    bool     value);

///<summary>
/// Set the current quality of a boolean input point
///</summary>
///<param name="index">Point index</param>
///<param name="quality">Current quality</param>
///<returns>BoolInputStatusCode</returns>
POINT_API int32_t bool_input_set_quality(
    uint32_t index, 
    int32_t  quality);

///<summary>
/// Set the current value/quality of a boolean input point
///</summary>
///<param name="index">Point index</param>
///<param name="value">Current value</param>
///<param name="quality">Current quality</param>
///<returns>BoolInputStatusCode</returns>
POINT_API int32_t bool_input_set_value_quality(
    uint32_t index, 
    bool     value,
    int32_t  quality);

