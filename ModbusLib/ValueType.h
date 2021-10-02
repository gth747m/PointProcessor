#pragma once

#include "ModbusLib.h"

namespace modbus
{
    enum class ValueType : int
    {
        /// <summary>
        /// Counts
        /// </summary>
        COUNT = 1,
        /// <summary>
        /// Integer
        /// </summary>
        INT = 2,
        /// <summary>
        /// IEEE floating point
        /// </summary>
        FLOAT = 3,
        /// <summary>
        /// Digital bit
        /// </summary>
        DIGITAL = 4
    };
}