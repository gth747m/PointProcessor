#include "Response.h"

#include "Crc16.h"

namespace ModbusLib
{
    /// <summary>
    /// Parse the Modbus response to a read request
    /// </summary>
    /// <param name="msg">Response message buffer</param>
    /// <returns>New Response object with parsed data</returns>
    Response* parse_read_response(std::vector<char>* msg)
    {
        auto response = new Response();
        response->success = true;
        if (msg->size() < 5)
        {
            response->success = false;
            response->error_message = "Message too short to parse";
            return response;
        }
        response->slave_address = static_cast<int>(msg->at(0));
        response->function_code = static_cast<FunctionCode>(msg->at(1));
        if (response->function_code != FunctionCode::READ_INPUT_REGISTER)
        {
            response->success = false;
            response->error_message = "Parsed message has wrong FunctionCode.";
            return response;
        }
        response->register_count = static_cast<int>(msg->at(2)) / 2;
        int valueCount = response->register_count / 2;
        for (int i = 0; i < valueCount; i++)
        {
            union {
                char swap_float_bytes[4];
                float swap_float;
            };
            swap_float_bytes[0] = msg->at(3 + 1 + (4 * i));
            swap_float_bytes[1] = msg->at(3 + 1 + (4 * i));
            swap_float_bytes[2] = msg->at(3 + 1 + (4 * i));
            swap_float_bytes[3] = msg->at(3 + 1 + (4 * i));
            response->values.push_back(swap_float);
        }
        union {
            char crc_bytes[2];
            uint16_t crc;
        };
        crc_bytes[0] = msg->at(msg->size() - 2);
        crc_bytes[1] = msg->at(msg->size() - 1);
        response->crc = crc;
        // Calculate the transferred message to compare CRC values
        if (Crc16::validate_msg_with_crc(msg))
        {
            return response;
        }
        else
        {
            response->success = false;
            response->error_message = "CRC check failed parsing Modbus response message.";
            return response;
        }
    }

    /// <summary>
    /// Parse the Modbus response to a write request
    /// </summary>
    /// <param name="msg">Response message buffer</param>
    /// <param name="expected_register_count">Response message buffer</param>
    /// <returns>New Response object with parsed data</returns>
    Response* parse_write_reponse(std::vector<char>* msg, int expected_register_count)
    {
        auto response = new Response();
        response->success = true;
        if (msg->size() < 5)
        {
            response->success = false;
            response->error_message = "Message too short to parse";
            return response;
        }
        response->slave_address = static_cast<int>(msg->at(0));
        response->function_code = static_cast<FunctionCode>(msg->at(1));
        if (response->function_code != FunctionCode::WRITE_MULTIPLE_REGISTERS)
        {
            response->success = false;
            response->error_message = "Parsed message has wrong FunctionCode.";
            return response;
        }
        union {
            char swap_int_bytes[4];
            int swap_int;
        };
        swap_int = 0;
        swap_int_bytes[2] = msg->at(3);
        swap_int_bytes[3] = msg->at(2);
        response->start_address = swap_int;
        swap_int = 0;
        swap_int_bytes[2] = msg->at(5);
        swap_int_bytes[3] = msg->at(4);
        response->register_count = swap_int;
        if (response->register_count != expected_register_count)
        {
            response->success = false;
            response->error_message = "Parsed message register count does "
                    "not match expected register count.";
        }
        union {
            char crc_bytes[2];
            uint16_t crc;
        };
        crc_bytes[0] = msg->at(msg->size() - 2);
        crc_bytes[1] = msg->at(msg->size() - 1);
        response->crc = crc;
        // Calculate the transferred message to compare CRC values
        if (Crc16::validate_msg_with_crc(msg))
        {
            return response;
        }
        else
        {
            response->success = false;
            response->error_message = "CRC check failed parsing Modbus response message.";
            return response;
        }
    }

}