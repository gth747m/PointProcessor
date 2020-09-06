#include "BoolPoint.h"

#include "Data.h"

///<summary>
/// Get the current value of a boolean point
///</summary>
///<param name="index">Point index</param>
///<param name="value">Current value</param>
///<returns>BoolStatusCode</returns>
int32_t bool_get_value(
    int32_t index, 
    bool*   value)
{
    if (index < 0 || index >= data->pointCount)
        return BOOL_POINT_INVALID_INDEX;
    *value = data->valuesQualities[index].value.bool_value;
    return BOOL_POINT_SUCCESS;
}

///<summary>
/// Get the current quality of a boolean point
///</summary>
///<param name="index">Point index</param>
///<param name="quality">Current quality</param>
///<returns>BoolStatusCode</returns>
int32_t bool_get_quality(
    int32_t  index, 
    int32_t* quality)
{
    if (quality == NULL)
        return BOOL_POINT_NULL;
    if (index < 0 || index >= data->pointCount)
        return BOOL_POINT_INVALID_INDEX;
    *quality = data->valuesQualities[index].quality;
    return BOOL_POINT_SUCCESS;
}

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
    int32_t* quality)
{
    if (value == NULL || quality == NULL)
        return BOOL_POINT_NULL;
    if (index < 0 || index >= data->pointCount)
        return BOOL_POINT_INVALID_INDEX;
    *value = data->valuesQualities[index].value.bool_value;
    *quality = data->valuesQualities[index].quality;
    return BOOL_POINT_SUCCESS;
}

///<summary>
/// Set the current value of a boolean point
///</summary>
///<param name="index">Point index</param>
///<param name="value">Current value</param>
///<returns>BoolStatusCode</returns>
int32_t bool_set_value(
    int32_t index, 
    bool    value)
{
    if (index < 0 || index >= data->pointCount)
        return BOOL_POINT_INVALID_INDEX;
    data->valuesQualities[index].value.bool_value = value;
    return BOOL_POINT_SUCCESS;
}

///<summary>
/// Set the current quality of a boolean point
///</summary>
///<param name="index">Point index</param>
///<param name="quality">Current quality</param>
///<returns>BoolStatusCode</returns>
int32_t bool_set_quality(
    int32_t index, 
    int32_t quality)
{
    if (index < 0 || index >= data->pointCount)
        return BOOL_POINT_INVALID_INDEX;
    data->valuesQualities[index].quality = quality;
    return BOOL_POINT_SUCCESS;
}

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
    int32_t quality)
{
    if (index < 0 || index >= data->pointCount)
        return BOOL_POINT_INVALID_INDEX;
    data->valuesQualities[index].value.bool_value = value;
    data->valuesQualities[index].quality = quality;
    return BOOL_POINT_SUCCESS;
}
