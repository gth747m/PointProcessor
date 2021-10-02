#include "ModbusLib.h"

namespace modbus
{
    /// <summary>
    /// Create a Modbus message to request reading a number of registers
    /// </summary>
    /// <param name="slave_address">Slave Address</param>
    /// <param name="start_address">Starting register address (>= 400001)</param>
    /// <param name="num_registers">Number of registers to read</param>
    /// <param name="msg">Modbus message buffer requesting a read of registers</param>
    void build_read_request(int slave_address, int start_address, int num_registers, std::vector<unsigned char>* msg)
    {
        union {
            unsigned char swap_int_bytes[4];
            int swap_int;
        };
        msg->clear();
        // Set the slave address
        msg->push_back(static_cast<unsigned char>(slave_address));
        // Set the function we want from the remote device
        msg->push_back(static_cast<unsigned char>(FunctionCode::READ_HOLDING_REGISTER));
        // Set the starting address 
        swap_int = (start_address - static_cast<int>(Parameter::MODBUS_REGISTER_OFFSET));
        // Swap endianess: Windows/Linux = little endian, Modbus = big endian
        msg->push_back(swap_int_bytes[3]);
        msg->push_back(swap_int_bytes[2]);
        // Set the number of registers we want to read
        swap_int = num_registers;
        msg->push_back(swap_int_bytes[3]);
        msg->push_back(swap_int_bytes[2]);
        // Calculate the CRC of the message up to this point
        swap_int = static_cast<int>(Crc16::compute(msg));
        // Append the CRC as the last 2 bytes (don't swap, it's already big endian)
        msg->push_back(swap_int_bytes[2]);
        msg->push_back(swap_int_bytes[3]);
    }

    /// <summary>
    /// Create a Modbus message to request writing a number of registers
    /// </summary>
    /// <param name="slave_address">Slave Address</param>
    /// <param name="start_address">Starting register address (>= 400001)</param>
    /// <param name="values">Array of values to set the registers to</param>
    /// <param name="msg">Modbus message buffer requesting a write of registers</param>
    void build_write_request(int slave_address, int start_address, std::vector<int>* values, std::vector<unsigned char>* msg)
    {
        union {
            unsigned char swap_int_bytes[4];
            int swap_int;
        };
        msg->clear();
        // Set the slave address
        msg->push_back(static_cast<unsigned char>(slave_address));
        // Set the function we want from the remote device
        msg->push_back(static_cast<unsigned char>(FunctionCode::WRITE_MULTIPLE_REGISTERS));
        // Set the starting address 
        swap_int = (start_address - static_cast<int>(Parameter::MODBUS_REGISTER_OFFSET));
        // Swap endianess: Windows/Linux = little endian, Modbus = big endian
        msg->push_back(swap_int_bytes[3]);
        msg->push_back(swap_int_bytes[2]);
        // Set the number of registers we're sending
        swap_int = static_cast<int>(values->size()) * 2;
        msg->push_back(swap_int_bytes[3]);
        msg->push_back(swap_int_bytes[2]);
        // Set the number of bytes we're sending
        msg->push_back(static_cast<unsigned char>(values->size() * 4));
        // Data loop
        for (auto value = values->cbegin(); value != values->cend(); values++)
        {
            swap_int = *value;
            msg->push_back(swap_int_bytes[1]);
            msg->push_back(swap_int_bytes[0]);
            msg->push_back(swap_int_bytes[3]);
            msg->push_back(swap_int_bytes[2]);
        }
        // Calculate the CRC of the message up to this point
        swap_int = static_cast<int>(Crc16::compute(msg));
        // Append the CRC as the last 2 bytes (don't swap, it's already big endian)
        msg->push_back(swap_int_bytes[2]);
        msg->push_back(swap_int_bytes[3]);
    }

    /// <summary>
    /// Create a Modbus message to request writing a number of registers
    /// </summary>
    /// <param name="slave_address">Slave Address</param>
    /// <param name="start_address">Starting register address (>= 400001)</param>
    /// <param name="values">Array of values to set the registers to</param>
    /// <param name="msg">Modbus message buffer requesting a write of registers</param>
    void build_write_request(int slave_address, int start_address, std::vector<float>* values, std::vector<unsigned char>* msg)
    {
        union {
            unsigned char swap_int_bytes[4];
            int swap_int;
        };
        union {
            unsigned char swap_float_bytes[4];
            float swap_float;
        };
        msg->clear();
        // Set the slave address
        msg->push_back(static_cast<unsigned char>(slave_address));
        // Set the function we want from the remote device
        msg->push_back(static_cast<unsigned char>(FunctionCode::WRITE_MULTIPLE_REGISTERS));
        // Set the starting address 
        swap_int = (start_address - static_cast<int>(Parameter::MODBUS_REGISTER_OFFSET));
        // Swap endianess: Windows/Linux = little endian, Modbus = big endian
        msg->push_back(swap_int_bytes[3]);
        msg->push_back(swap_int_bytes[2]);
        // Set the number of registers we're sending
        swap_int = static_cast<int>(values->size()) * 2;
        msg->push_back(swap_int_bytes[3]);
        msg->push_back(swap_int_bytes[2]);
        // Set the number of bytes we're sending
        msg->push_back(static_cast<unsigned char>(values->size() * 4));
        // Data loop
        for (auto value = values->cbegin(); value != values->cend(); values++)
        {
            swap_float = *value;
            msg->push_back(swap_float_bytes[1]);
            msg->push_back(swap_float_bytes[0]);
            msg->push_back(swap_float_bytes[3]);
            msg->push_back(swap_float_bytes[2]);
        }
        // Calculate the CRC of the message up to this point
        swap_int = static_cast<int>(Crc16::compute(msg));
        // Append the CRC as the last 2 bytes (don't swap, it's already big endian)
        msg->push_back(swap_int_bytes[2]);
        msg->push_back(swap_int_bytes[3]);
    }
}