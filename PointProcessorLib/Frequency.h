#pragma once

#include "PointProcessorLib.h"

namespace point_processor
{
    /// <summary>
    /// Point Processing Frequency
    /// </summary>
    enum class Frequency : uint64_t
    {
        /// <summary>
        /// Unknown Point Processing Frequency
        /// </summary>
        UNKNOWN = 0,
        /// <summary>
        /// 0.1 second
        /// </summary>
        A = 1,
        /// <summary>
        /// 1 second
        /// </summary>
        B = 1 << 1,
        /// <summary>
        /// 5 seconds
        /// </summary>
        C = 1 << 2,
        /// <summary>
        /// 15 seconds
        /// </summary>
        D = 1 << 3,
        /// <summary>
        /// 30 seconds
        /// </summary>
        E = 1 << 4,
        /// <summary>
        /// 1 minute
        /// </summary>
        F = 1 << 5,
        /// <summary>
        /// 2 minutes
        /// </summary>
        G = 1 << 6,
        /// <summary>
        /// 15 minutes
        /// </summary>
        H = 1 << 7
    };

    /// <summary>
    /// Auto convert enumerator to string
    /// </summary>
    inline std::ostream& operator<<(std::ostream& os, Frequency freq)
    {
        switch (freq)
        {
        case (Frequency::UNKNOWN):  os << "UNKNOWN";  break;
        case (Frequency::A):        os << "A";        break;
        case (Frequency::B):        os << "B";        break;
        case (Frequency::C):        os << "C";        break;
        case (Frequency::D):        os << "D";        break;
        case (Frequency::E):        os << "E";        break;
        case (Frequency::F):        os << "F";        break;
        case (Frequency::G):        os << "G";        break;
        case (Frequency::H):        os << "H";        break;
        }
        return os;
    }

    namespace frequency
    {
        /// <summary>
        /// Converts a Frequency enumerator to the number of seconds per update
        /// </summary>
        /// <param name="frequency">[IN] Frequency</param>
        /// <returns>Number of seconds between updates</returns>
        float to_seconds(const Frequency frequency);
    }
}
