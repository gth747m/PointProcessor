#pragma once

#include "ModbusLib.h"

namespace modbus
{
    /// <summary>
    /// Class for handling Modbus requests
    /// </summary>
    class Request
    {
    public:
        /// <summary>
        /// Create a Modbus message to request reading a number of registers
        /// </summary>
        /// <param name="slave_address">Slave Address</param>
        /// <param name="start_address">Starting register address (>= 400001)</param>
        /// <param name="num_registers">Number of registers to read</param>
        /// <param name="msg">Modbus message buffer requesting a read of registers</param>
        static void build_read_request(int slave_address, int start_address, int num_registers, std::vector<unsigned char>* msg);

        /// <summary>
        /// Create a Modbus message to request writing a number of registers
        /// </summary>
        /// <param name="slave_address">Slave Address</param>
        /// <param name="start_address">Starting register address (>= 400001)</param>
        /// <param name="values">Array of values to set the registers to</param>
        /// <param name="msg">Modbus message buffer requesting a write of registers</param>
        static void build_write_request(int slave_address, int start_address, std::vector<int>* values, std::vector<unsigned char>* msg);

        /// <summary>
        /// Create a Modbus message to request writing a number of registers
        /// </summary>
        /// <param name="slave_address">Slave Address</param>
        /// <param name="start_address">Starting register address (>= 400001)</param>
        /// <param name="values">Array of values to set the registers to</param>
        /// <param name="msg">Modbus message buffer requesting a write of registers</param>
        static void build_write_request(int slave_address, int start_address, std::vector<float>* values, std::vector<unsigned char>* msg);
    };
}
