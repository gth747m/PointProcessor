#pragma once

#include "PointProcessorLib.h"

#include <ostream>

namespace point_processor
{
    /// <summary>
    /// Point Processing Frequency
    /// </summary>
    enum class Frequency : int
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
        B = 2,
        /// <summary>
        /// 5 seconds
        /// </summary>
        C = 3,
        /// <summary>
        /// 15 seconds
        /// </summary>
        D = 4,
        /// <summary>
        /// 30 seconds
        /// </summary>
        E = 5,
        /// <summary>
        /// 1 minute
        /// </summary>
        F = 6,
        /// <summary>
        /// 2 minutes
        /// </summary>
        G = 7,
        /// <summary>
        /// 15 minutes
        /// </summary>
        H = 8
    };

    /// <summary>
    /// Auto convert enumerator to string
    /// </summary>
    inline std::ostream& operator<<(std::ostream& os, Frequency freq)
    {
        switch ((int)freq)
        {
            case (0): os << "UNKNOWN";  break;
            case (1): os << "A";        break;
            case (2): os << "B";        break;
            case (3): os << "C";        break;
            case (4): os << "D";        break;
            case (5): os << "E";        break;
            case (6): os << "F";        break;
            case (7): os << "G";        break;
            case (8): os << "H";        break;
        }
        return os;
    }

    namespace frequency
    {
        /// <summary>
        /// Converts a frequency int (from ime_type) to a Frequency enumerator
        /// </summary>
        /// <param name="frequency">[IN] Frequency int from ime_type</param>
        /// <returns>Frequency enumerator</returns>
        Frequency from(const int frequency);

        /// <summary>
        /// Converts a Frequency enumerator to the number of seconds per update
        /// </summary>
        /// <param name="frequency">[IN] Frequency</param>
        /// <returns>Number of seconds between updates</returns>
        float to_seconds(const Frequency frequency);
    }
}
