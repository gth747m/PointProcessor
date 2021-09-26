#pragma once

#include <iostream>

namespace ModbusLib
{
    enum class FunctionCode : unsigned char
    {
        /// <summary>
        /// Default code when one is not specified
        /// </summary>
        NOT_SET = 0,
        /// <summary>
        /// Function code to read from 1 to 2000 contiguous status of coils
        /// </summary>
        READ_COIL_STATUS = 1,
        /// <summary>
        /// Function code to read from 1 to 2000 contiguous status of descrete inputs
        /// </summary>
        READ_INPUT_STATUS = 2,
        /// <summary>
        /// Function code to read the contents of a contiguous block of holding registers
        /// (register data in the response message are packed as two bytes per register in Big Endian format)
        /// </summary>
        READ_HOLDING_REGISTER = 3,
        /// <summary>
        /// Function code to read from 1 to approx. 125 contiguous input registers
        /// (register data in the response message are packed as two bytes per register in Big Endian format)
        /// </summary>
        READ_INPUT_REGISTER = 4,
        /// <summary>
        /// Function code to write a single output to either ON or OFF
        /// </summary>
        WRITE_SINGLE_COIL = 5,
        /// <summary>
        /// Function code to write a single holding register
        /// </summary>
        WRITE_SINGLE_REGISTER = 6,
        /// <summary>
        /// Function code is used to force each coil in a sequence of coils to either ON or OFF
        /// </summary>
        WRITE_MULTIPLE_COILS = 15,
        /// <summary>
        /// Function code to write a block of contiguous register (1 to approx. 120 registers)
        /// </summary>
        WRITE_MULTIPLE_REGISTERS = 16
    };
}