#pragma once

#include <vector>

namespace ModbusLib
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
        /// <param name="slaveAddress">Slave Address</param>
        /// <param name="startAddress">Starting register address (>= 400001)</param>
        /// <param name="numRegisters">Number of registers to read</param>
        /// <param name="msg">Modbus message buffer requesting a read of registers</param>
        static void build_read_request(int slaveAddress, int startAddress, int numRegisters, std::vector<char>* msg);

        /// <summary>
        /// Create a Modbus message to request writing a number of registers
        /// </summary>
        /// <param name="slaveAddress">Slave Address</param>
        /// <param name="startAddress">Starting register address (>= 400001)</param>
        /// <param name="values">Array of values to set the registers to</param>
        /// <param name="msg">Modbus message buffer requesting a write of registers</param>
        static void build_write_request(int slaveAddress, int startAddress, std::vector<int>* values, std::vector<char>* msg);

        /// <summary>
        /// Create a Modbus message to request writing a number of registers
        /// </summary>
        /// <param name="slaveAddress">Slave Address</param>
        /// <param name="startAddress">Starting register address (>= 400001)</param>
        /// <param name="values">Array of values to set the registers to</param>
        /// <param name="msg">Modbus message buffer requesting a write of registers</param>
        static void build_write_request(int slaveAddress, int startAddress, std::vector<float>* values, std::vector<char>* msg);
    };
}
