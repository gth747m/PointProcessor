#pragma once

#include "ModbusLib.h"

namespace modbus
{
    /// <summary>
    /// Class for handling Modbus responses
    /// </summary>
    class Response
    {
    public:
        /// <summary>
        /// Class constructor
        /// </summary>
        Response();

        /// <summary>
        /// Parse the Modbus response to a read request
        /// </summary>
        /// <param name="msg">Response message buffer</param>
        /// <returns>New Response object with parsed data</returns>
        static Response* parse_read_response(std::vector<unsigned char>* msg);

        /// <summary>
        /// Parse the Modbus response to a write request
        /// </summary>
        /// <param name="msg">Response message buffer</param>
        /// <returns>New Response object with parsed data</returns>
        static Response* parse_write_reponse(std::vector<unsigned char>* msg, int expected_register_count);

        /// <summary>
        /// Slave address
        /// </summary>
        int slave_address;
        /// <summary>
        /// Function code
        /// </summary>
        FunctionCode function_code;
        /// <summary>
        /// Starting register (PARSE_WRITE_REQUEST only)
        /// </summary>
        int start_address;
        /// <summary>
        /// Number of registers written or read
        /// </summary>
        int register_count;
        /// <summary>
        /// Array of Values (PARSE_READ_REQUEST only)
        /// </summary>
        std::vector<float> values;
        /// <summary>
        /// CRC check transmitted
        /// </summary>
        uint16_t crc;
        /// <summary>
        /// Did we succeed?
        /// </summary>
        bool success;
        /// <summary>
        /// If not a success check this message
        /// </summary>
        std::string error_message;

    };
}