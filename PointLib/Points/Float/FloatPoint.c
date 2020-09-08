#include "FloatPoint.h"

#include "../../Data.h"

///<summary>
/// Get the current value of a float point
///</summary>
///<param name="index">Point index</param>
///<param name="value">Current value</param>
///<returns>FloatStatusCode</returns>
POINT_API int32_t float_get_value(
    uint32_t index, 
    float*   value)
{
    if (index >= data->pointCount)
        return FLOAT_POINT_INVALID_INDEX;
    *value = data->valuesQualities[index].value.float_value;
    return FLOAT_POINT_SUCCESS;
}

///<summary>
/// Get the current quality of a float point
///</summary>
///<param name="index">Point index</param>
///<param name="quality">Current quality</param>
///<returns>FloatStatusCode</returns>
POINT_API int32_t float_get_quality(
    uint32_t index, 
    int32_t* quality)
{
    if (quality == NULL)
        return FLOAT_POINT_NULL;
    if (index >= data->pointCount)
        return FLOAT_POINT_INVALID_INDEX;
    *quality = data->valuesQualities[index].quality;
    return 0;
}

///<summary>
/// Get the current value/quality of a float point
///</summary>
///<param name="index">Point index</param>
///<param name="value">Current value</param>
///<param name="quality">Current quality</param>
///<returns>FloatStatusCode</returns>
POINT_API int32_t float_get_value_quality(
    uint32_t index,
    float*   value,
    int32_t* quality)
{
    if (value == NULL || quality == NULL)
        return FLOAT_POINT_NULL;
    if (index >= data->pointCount)
        return FLOAT_POINT_INVALID_INDEX;
    *value = data->valuesQualities[index].value.float_value;
    *quality = data->valuesQualities[index].quality;
    return FLOAT_POINT_SUCCESS;
}

///<summary>
/// Set the current value of a float point
///</summary>
///<param name="index">Point index</param>
///<param name="value">Current value</param>
///<returns>FloatStatusCode</returns>
POINT_API int32_t float_set_value(
    uint32_t index, 
    float    value)
{
    if (index >= data->pointCount)
        return FLOAT_POINT_INVALID_INDEX;
    data->valuesQualities[index].value.float_value = value;
    return FLOAT_POINT_SUCCESS;
}

///<summary>
/// Set the current quality of a float point
///</summary>
///<param name="index">Point index</param>
///<param name="quality">Current quality</param>
///<returns>FloatStatusCode</returns>
POINT_API int32_t float_set_quality(
    uint32_t index, 
    int32_t  quality)
{
    if (index >= data->pointCount)
        return FLOAT_POINT_INVALID_INDEX;
    data->valuesQualities[index].quality = quality;
    return FLOAT_POINT_SUCCESS;
}

///<summary>
/// Set the current value/quality of a float point
///</summary>
///<param name="index">Point index</param>
///<param name="value">Current value</param>
///<param name="quality">Current quality</param>
///<returns>FloatStatusCode</returns>
POINT_API int32_t float_set_value_quality(
    uint32_t index,
    float    value,
    int32_t  quality)
{
    if (index >= data->pointCount)
        return FLOAT_POINT_INVALID_INDEX;
    data->valuesQualities[index].value.float_value = value;
    data->valuesQualities[index].quality = quality;
    return FLOAT_POINT_SUCCESS;
}
