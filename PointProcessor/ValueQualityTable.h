#pragma once

#include <stdint.h>

#include "Constants.h"
#include "Quality.h"

///<summary>
/// Value/Quality pair
///</summary>
typedef struct ValueQuality
{
    int32_t value[MAX_POINTS];
    Quality quality[MAX_POINTS];
} ValueQuality;

///<summary>
/// Current point values and qualities
///</summary>
typedef struct ValueQualityTable
{
    ValueQuality value_quality[MAX_POINTS];
} ValueQualityTable;