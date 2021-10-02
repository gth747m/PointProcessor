#pragma once

#include "PointProcessorLib.h"

namespace point_processor
{
    /// <summary>
    /// Possible point qualities.
    /// </summary>
    enum class Quality : uint32_t
    {
        /// <summary>
        /// Let the point processor determine the quality
        /// </summary>
        AUTO_DETERMINED = 0xFFFFFFFF,
        /// <summary>
        /// Point quality is unkown
        /// </summary>
        UNKNOWN = 0x00000001,
        /// <summary>
        /// Deleted from processing
        /// </summary>
        DELETED = 0x00000002,
        /// <summary>
        /// Couldn't calculate
        /// </summary>
        NOT_CALCULABLE = 0x00000004,
        /// <summary>
        /// Invalid
        /// </summary>
        INVALID = 0x00000008,
        /// <summary>
        /// Sensor read error
        /// </summary>
        READ_ERROR = 0x00000010,
        /// <summary>
        /// Open thermocouple detection
        /// </summary>
        OPEN_THRM_CPL = 0x00000020,
        /// <summary>
        /// Input counts out of sensor range
        /// </summary>
        BAD = 0x00000040,
        /// <summary>
        /// Unreasonably high
        /// </summary>
        HI_RSN_LIMIT = 0x00000080,
        /// <summary>
        /// Unreasonably Low
        /// </summary>
        LOW_RSN_LIMIT = 0x00000100,
        /// <summary>
        /// Old data
        /// </summary>
        OLD = 0x00000200,
        /// <summary>
        /// Suspect value above HIHI limit
        /// </summary>
        SUSPECT_HIHI = 0x00000400,
        /// <summary>
        /// Suspect value below LOLO limit
        /// </summary>
        SUSPECT_LOLO = 0x00000800,
        /// <summary>
        /// Suspect value above HI warning limit
        /// </summary>
        SUSPECT_HI = 0x00001000,
        /// <summary>
        /// Suspect value below LO warning limit
        /// </summary>
        SUSPECT_LO = 0x00002000,
        /// <summary>
        /// Suspect data
        /// </summary>
        SUSPECT = 0x00004000,
        /// <summary>
        /// Digital suspect alarm
        /// </summary>
        SUSPECT_ALARM = 0x00008000,
        /// <summary>
        /// Inserted value above HIHI limit
        /// </summary>
        INSERTED_HIHI = 0x00010000,
        /// <summary>
        /// Inserted value below LOLO limit
        /// </summary>
        INSERTED_LOLO = 0x00020000,
        /// <summary>
        /// Inserted value above HI warning limit
        /// </summary>
        INSERTED_HI = 0x00040000,
        /// <summary>
        /// Inserted value below LO warning limit
        /// </summary>
        INSERTED_LO = 0x00080000,
        /// <summary>
        /// Inserted value
        /// </summary>
        INSERTED = 0x00100000,
        /// <summary>
        /// Digital inserted status in alarm
        /// </summary>
        INSERTED_ALARM = 0x00200000,
        /// <summary>
        /// Logical change-of-state alarm
        /// </summary>
        ALARM = 0x00400000,
        /// <summary>
        /// HI alarm
        /// </summary>
        HIHI = 0x00800000,
        /// <summary>
        /// LO alarm
        /// </summary>
        LOLO = 0x01000000,
        /// <summary>
        /// HI warning
        /// </summary>
        HI = 0x02000000,
        /// <summary>
        /// LO warning
        /// </summary>
        LO = 0x04000000,
        /// <summary>
        /// Deleted from alarm checks
        /// </summary>
        DELETED_ALARM = 0x08000000,
        /// <summary>
        /// Inhibited by cutout point
        /// </summary>
        INHIBITED = 0x10000000,
        /// <summary>
        /// Good
        /// </summary>
        GOOD = 0x20000000
    };

    /// <summary>
    /// Print quality enumerator to an output stream
    /// </summary>
    inline std::ostream& operator<<(std::ostream& os, Quality qual)
    {
        switch ((uint32_t)qual)
        {
            case (0xFFFFFFFF): os << "AUTO_DETERMINED"; break;
            case (0x00000001): os << "UNKNOWN";         break;
            case (0x00000002): os << "DELETED";         break;
            case (0x00000004): os << "NOT_CALCULABLE";  break;
            case (0x00000008): os << "INVALID";         break;
            case (0x00000010): os << "READ_ERROR";      break;
            case (0x00000020): os << "OPEN_THRM_CPL";   break;
            case (0x00000040): os << "BAD";             break;
            case (0x00000080): os << "HI_RSN_LIMIT";    break;
            case (0x00000100): os << "LOW_RSN_LIMIT";   break;
            case (0x00000200): os << "OLD";             break;
            case (0x00000400): os << "SUSPECT_HIHI";    break;
            case (0x00000800): os << "SUSPECT_LOLO";    break;
            case (0x00001000): os << "SUSPECT_HI";      break;
            case (0x00002000): os << "SUSPECT_LO";      break;
            case (0x00004000): os << "SUSPECT";         break;
            case (0x00008000): os << "SUSPECT_ALARM";   break;
            case (0x00010000): os << "INSERTED_HIHI";   break;
            case (0x00020000): os << "INSERTED_LOLO";   break;
            case (0x00040000): os << "INSERTED_HI";     break;
            case (0x00080000): os << "INSERTED_LO";     break;
            case (0x00100000): os << "INSERTED";        break;
            case (0x00200000): os << "INSERTED_ALARM";  break;
            case (0x00400000): os << "ALARM";           break;
            case (0x00800000): os << "HIHI";            break;
            case (0x01000000): os << "LOLO";            break;
            case (0x02000000): os << "HI";              break;
            case (0x04000000): os << "LO";              break;
            case (0x08000000): os << "DELETED_ALARM";   break;
            case (0x10000000): os << "INHIBITED";       break;
            case (0x20000000): os << "GOOD";            break;
        }
        return os;
    }

    namespace quality
    {
        /// <summary>
        /// Converts a Quality int into a Quality enumerator.
        /// </summary>
        /// <param name="qual">[IN] Integer value of the PMS quality.</param>
        /// <returns>Quality enumerator</returns>
        Quality from(const uint32_t qual);

        /// <summary>
        /// Check if this quality is usable for calculations
        /// <summary>
        /// <param name="qual">[IN] Quality to test</param>
        /// <returns>Whether or not the quality is usable for calculation</returns>
        bool is_usable(const Quality qual);
    }
}
