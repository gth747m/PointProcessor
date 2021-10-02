#pragma once

#include "ModbusLib.h"

namespace modbus
{
    class Crc16
    {
    public:
        /// <summary>
        /// Compute the CRC for a message
        /// </summary>
        /// <param name="msg">Message to calculate CRC for</param>
        /// <returns>Two-byte array of calculated CRC in Big-Endian format</returns>
        static uint16_t compute(std::vector<unsigned char>* msg);
        /// <summary>
        /// Compute the CRC for a message that already has a CRC as the last two bytes
        /// </summary>
        /// <param name="msg">Message to calculate CRC for</param>
        /// <returns>Two-byte array of calculated CRC in Big-Endian format</returns>
        static bool validate_msg_with_crc(std::vector<unsigned char>* msg);
    };
}
