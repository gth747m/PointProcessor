#include "PointProcessorLib.h"

namespace point_processor
{
    SharedMemoryException::SharedMemoryException(const char* msg) :
        error_message(std::string(msg))
    {
    }

    SharedMemoryException::SharedMemoryException(std::string msg) :
        error_message(msg)
    {
    }

    SharedMemoryException::SharedMemoryException(std::stringstream& msg) :
        error_message(msg.str())
    {
    }

    const char* SharedMemoryException::what() const throw()
    {
        return error_message.c_str();
    }
}