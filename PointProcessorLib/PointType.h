#pragma once

#include "PointProcessorLib.h"

namespace point_processor
{
    enum class PointType : uint32_t
    {
        UNKNOWN                     = 0,
        AVERAGE                     = 1,
        CHAUVENET_AVERAGE           = 1 << 1,
        COUNTER                     = 1 << 2,
        C_TO_F                      = 1 << 3,
        DIGITAL_FILTER              = 1 << 4,
        DIVIDE                      = 1 << 5,
        EQUAL_SELECT                = 1 << 6,
        EXTERNAL                    = 1 << 7,
        F_TO_C                      = 1 << 8,
        GREATER_THAN_EQUAL_SELECT   = 1 << 9,
        GREATER_THAN_SELECT         = 1 << 10,
        MULTIPLY                    = 1 << 11,
        POLYNOMIAL                  = 1 << 12,
        POWER                       = 1 << 13,
        SELECT                      = 1 << 14,
        SUBTRACT                    = 1 << 15,
        SUM                         = 1 << 16,
    };
}
