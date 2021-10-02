#pragma once

#include "ModbusLib.h"

namespace modbus
{
    enum class Parameter : int
    {
        /// <summary>
        /// Register number offset
        /// </summary>
        MODBUS_REGISTER_OFFSET = 400001
    };
}