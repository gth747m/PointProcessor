#include "IntPoint.h"

#include "Data.h"

///<summary>
/// Get the current value of a integer point
///</summary>
///<param name="index">Point index</param>
///<param name="value">Current value</param>
///<returns>IntStatusCode</returns>
int32_t int_get_value(
    uint32_t index, 
    int32_t* value)
{
    if (index >= data->pointCount)
        return INT_POINT_INVALID_INDEX;
    *value = data->valuesQualities[index].value.int_value;
    return INT_POINT_SUCCESS;
}

///<summary>
/// Get the current quality of a integer point
///</summary>
///<param name="index">Point index</param>
///<param name="quality">Current quality</param>
///<returns>IntStatusCode</returns>
int32_t int_get_quality(
    uint32_t index, 
    int32_t* quality)
{
    if (quality == NULL)
        return INT_POINT_NULL;
    if (index >= data->pointCount)
        return INT_POINT_INVALID_INDEX;
    *quality = data->valuesQualities[index].quality;
    return 0;
}

///<summary>
/// Get the current value/quality of a integer point
///</summary>
///<param name="index">Point index</param>
///<param name="value">Current value</param>
///<param name="quality">Current quality</param>
///<returns>IntStatusCode</returns>
int32_t int_get_value_quality(
    uint32_t index,
    int32_t* value,
    int32_t* quality)
{
    if (value == NULL || quality == NULL)
        return INT_POINT_NULL;
    if (index >= data->pointCount)
        return INT_POINT_INVALID_INDEX;
    *value = data->valuesQualities[index].value.int_value;
    *quality = data->valuesQualities[index].quality;
    return INT_POINT_SUCCESS;
}

///<summary>
/// Set the current value of a integer point
///</summary>
///<param name="index">Point index</param>
///<param name="value">Current value</param>
///<returns>IntStatusCode</returns>
int32_t int_set_value(
    uint32_t index, 
    int32_t  value)
{
    if (index >= data->pointCount)
        return INT_POINT_INVALID_INDEX;
    data->valuesQualities[index].value.int_value = value;
    return INT_POINT_SUCCESS;
}

///<summary>
/// Set the current quality of a integer point
///</summary>
///<param name="index">Point index</param>
///<param name="quality">Current quality</param>
///<returns>IntStatusCode</returns>
int32_t int_set_quality(
    uint32_t index, 
    int32_t  quality)
{
    if (index >= data->pointCount)
        return INT_POINT_INVALID_INDEX;
    data->valuesQualities[index].quality = quality;
    return INT_POINT_SUCCESS;
}

///<summary>
/// Set the current value/quality of a integer point
///</summary>
///<param name="index">Point index</param>
///<param name="value">Current value</param>
///<param name="quality">Current quality</param>
///<returns>IntStatusCode</returns>
int32_t int_set_value_quality(
    uint32_t index,
    int32_t  value,
    int32_t  quality)
{
    if (index >= data->pointCount)
        return INT_POINT_INVALID_INDEX;
    data->valuesQualities[index].value.int_value = value;
    data->valuesQualities[index].quality = quality;
    return INT_POINT_SUCCESS;
}
