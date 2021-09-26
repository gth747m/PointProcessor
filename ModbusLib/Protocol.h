#pragma once

namespace ModbusLib
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