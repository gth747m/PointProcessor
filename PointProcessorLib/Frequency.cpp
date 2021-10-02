#include "PointProcessorLib.h"

namespace point_processor
{
    namespace frequency
    {
        /// <summary>
        /// Converts a frequency int (from ime_type) to a Frequency enumerator
        /// </summary>
        /// <param name="frequency">[IN] Frequency int from ime_type</param>
        /// <returns>Frequency enumerator</returns>
        Frequency from(const int frequency)
        {
            switch (frequency)
            {
            case (1): return Frequency::A;
            case (2): return Frequency::B;
            case (3): return Frequency::C;
            case (4): return Frequency::D;
            case (5): return Frequency::E;
            case (6): return Frequency::F;
            case (7): return Frequency::G;
            case (8): return Frequency::H;
            default:  return Frequency::UNKNOWN;
            }
        }

        /// <summary>
        /// Converts a Frequency enumerator to the number of seconds per update
        /// </summary>
        /// <param name="frequency">[IN] Frequency</param>
        /// <returns>Number of seconds between updates</returns>
        float to_seconds(const Frequency frequency)
        {
            switch (frequency)
            {
            case (Frequency::A): return (0.1f);
            case (Frequency::B): return (1.0f);
            case (Frequency::C): return (5.0f);
            case (Frequency::D): return (15.0f);
            case (Frequency::E): return (30.0f);
            case (Frequency::F): return (60.0f);
            case (Frequency::G): return (120.0f);
            case (Frequency::H): return (900.0f);
            default:             return (0.0f);
            }
        }
    }
}