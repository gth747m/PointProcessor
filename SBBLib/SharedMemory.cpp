#include "SharedMemory.h"

#include <cstdint>

#ifdef __linux__
#    include <unistd.h>
#    include <errno.h>
#    include <fcntl.h>
#    include <sys/mman.h>
#    include <sys/stat.h>
#endif

namespace sbb
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