#pragma once

#include "PointProcessorLib.h"

namespace point_processor
{
    /// <summary>
    /// Alias to a string stored in shared memory
    /// </summary>
    using ShmString = std::basic_string<char, std::char_traits<char>, ShmAllocator<char>>;
    /// <summary>
    /// Alias to a vector who's entries are stored in shared memory
    /// </summary>
    template<class T>
    using ShmVector = std::vector<T, ShmAllocator<T>>;
    /// <summary>
    /// Alias to a dictionary who's entries are stored in shared memory
    /// </summary>
    template<class T, class U, class less = std::less<T>>
    using ShmMap = std::map<T, U, less, ShmAllocator<std::pair<const T, U>>>;
}
