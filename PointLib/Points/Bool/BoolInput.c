#include "BoolInput.h"

#include "../../Data.h"
#include "../PointType.h"
#include "../Quality.h"

/// <summary>
/// Initialize an index to a boolean input point
/// </summary>
/// <param name="index">index</param>
/// <returns>BoolInputStatusCode</returns>
POINT_API int32_t bool_input_init_value_quality(
    uint32_t index)
{
    if (index >= data->pointCount)
        return BOOL_INP_INVALID_INDEX;
    data->pointValueTypes[index] = BOOL_VALUE;
    data->pointTypes[index] = BOOL_INP;
    data->valuesQualities[index].value.bool_value = false;
    data->valuesQualities[index].quality = QUAL_UNK;
    return BOOL_INP_SUCCESS;
}

///<summary>
/// Get the current value of a boolean input point
///</summary>
///<param name="index">Point index</param>
///<param name="value">Current value</param>
///<returns>BoolInputStatusCode</returns>
POINT_API int32_t bool_input_get_value(
    uint32_t index, 
    bool*    value)
{
    if (value == NULL)
        return BOOL_INP_NULL;
    if (index >= data->pointCount)
        return BOOL_INP_INVALID_INDEX;
    if (data->pointTypes[index] != BOOL_INP)
        return BOOL_INP_INVALID_TYPE;
    *value = data->valuesQualities[index].value.bool_value;
    return BOOL_INP_SUCCESS;
}

///<summary>
/// Get the current quality of a boolean input point
///</summary>
///<param name="index">Point index</param>
///<param name="quality">Current quality</param>
///<returns>BoolInputStatusCode</returns>
POINT_API int32_t bool_input_get_quality(
    uint32_t   index, 
    int32_t*   quality)
{
    if (quality == NULL)
        return BOOL_INP_NULL;
    if (index >= data->pointCount)
        return BOOL_INP_INVALID_INDEX;
    if (data->pointTypes[index] != BOOL_INP)
        return BOOL_INP_INVALID_TYPE;
    *quality = data->valuesQualities[index].quality;
    return BOOL_INP_SUCCESS;
}

///<summary>
/// Get the current value/quality of a boolean input point
///</summary>
///<param name="index">Point index</param>
///<param name="value">Current value</param>
///<param name="quality">Current quality</param>
///<returns>BoolInputStatusCode</returns>
POINT_API int32_t bool_input_get_value_quality(
    uint32_t   index,
    bool*      value,
    int32_t*   quality)
{
    if (value == NULL || quality == NULL)
        return BOOL_INP_NULL;
    if (index >= data->pointCount)
        return BOOL_INP_INVALID_INDEX;
    if (data->pointTypes[index] != BOOL_INP)
        return BOOL_INP_INVALID_TYPE;
    *value = data->valuesQualities[index].value.bool_value;
    *quality = data->valuesQualities[index].quality;
    return BOOL_INP_SUCCESS;
}

///<summary>
/// Set the current value of a boolean input point
///</summary>
///<param name="index">Point index</param>
///<param name="value">Current value</param>
///<returns>BoolInputStatusCode</returns>
POINT_API int32_t bool_input_set_value(
    uint32_t index, 
    bool     value)
{
    if (index >= data->pointCount)
        return BOOL_INP_INVALID_INDEX;
    if (data->pointTypes[index] != BOOL_INP)
        return BOOL_INP_INVALID_TYPE;
    data->valuesQualities[index].value.bool_value = value;
    return BOOL_INP_SUCCESS;
}

///<summary>
/// Set the current quality of a boolean input point
///</summary>
///<param name="index">Point index</param>
///<param name="quality">Current quality</param>
///<returns>BoolInputStatusCode</returns>
POINT_API int32_t bool_input_set_quality(
    uint32_t index, 
    int32_t  quality)
{
    if (index >= data->pointCount)
        return BOOL_INP_INVALID_INDEX;
    if (data->pointTypes[index] != BOOL_INP)
        return BOOL_INP_INVALID_TYPE;
    data->valuesQualities[index].quality = quality;
    return BOOL_INP_SUCCESS;
}

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
    int32_t  quality)
{
    if (index >= data->pointCount)
        return BOOL_INP_INVALID_INDEX;
    if (data->pointTypes[index] != BOOL_INP)
        return BOOL_INP_INVALID_TYPE;
    data->valuesQualities[index].value.bool_value = value;
    data->valuesQualities[index].quality = quality;
    return BOOL_INP_SUCCESS;
}

