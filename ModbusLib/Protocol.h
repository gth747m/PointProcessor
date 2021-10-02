#pragma once

#include "ModbusLib.h"

namespace modbus
{
    enum class Protocol : int
    {
        /// <summary>
        /// ASCII Mode
        /// </summary>
        ASCII = 1,
        /// <summary>
        /// Remote Terminal Unit Mode (requires CRC)
        /// </summary>
        RTU = 2
    };
}