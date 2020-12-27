#pragma once

#include <ostream>

namespace PointProcessor
{
    /// <summary>
    /// Possible point qualities.
    /// </summary>
    enum class Quality
    {
        /// <summary>
        /// Let the point processor determine the quality
        /// </summary>
        AUTO_DETERMINED = -1,
        /// <summary>
        /// Point quality is unkown
        /// </summary>
        UNKNOWN = 0,
        /// <summary>
        /// Deleted from processing
        /// </summary>
        DELETED = 1,
        /// <summary>
        /// Couldn't calculate
        /// </summary>
        NOT_CALCULABLE = 2,
        /// <summary>
        /// Invalid
        /// </summary>
        INVALID = 3,
        /// <summary>
        /// Sensor read error
        /// </summary>
        READ_ERROR = 4,
        /// <summary>
        /// Open thermocouple detection
        /// </summary>
        OPEN_THRM_CPL = 5,
        /// <summary>
        ///  Input counts out of sensor range
        /// </summary>
        BAD = 6,
        /// <summary>
        /// Unreasonably high
        /// </summary>
        HI_RSN_LIMIT = 7,
        /// <summary>
        /// Unreasonably Low
        /// </summary>
        LOW_RSN_LIMIT = 8,
        /// <summary>
        /// Old data
        /// </summary>
        OLD = 9,
        /// <summary>
        /// Suspect value above HIHI limit
        /// </summary>
        SUSPECT_HIHI = 10,
        /// <summary>
        /// Suspect value below LOLO limit
        /// </summary>
        SUSPECT_LOLO = 11,
        /// <summary>
        /// Suspect value above HI warning limit
        /// </summary>
        SUSPECT_HI = 12,
        /// <summary>
        /// Suspect value below LO warning limit
        /// </summary>
        SUSPECT_LO = 13,
        /// <summary>
        /// Suspect data
        /// </summary>
        SUSPECT = 14,
        /// <summary>
        /// Digital suspect alarm
        /// </summary>
        SUSPECT_ALARM = 15,
        /// <summary>
        /// Inserted value above HIHI limit
        /// </summary>
        INSERTED_HIHI = 16,
        /// <summary>
        /// Inserted value below LOLO limit
        /// </summary>
        INSERTED_LOLO = 17,
        /// <summary>
        /// Inserted value above HI warning limit
        /// </summary>
        INSERTED_HI = 18,
        /// <summary>
        /// Inserted value below LO warning limit
        /// </summary>
        INSERTED_LO = 19,
        /// <summary>
        /// Inserted value
        /// </summary>
        INSERTED = 20,
        /// <summary>
        /// Digital inserted status in alarm
        /// </summary>
        INSERTED_ALARM = 21,
        /// <summary>
        ///  Logical change-of-state alarm
        /// </summary>
        ALARM = 22,
        /// <summary>
        /// HI alarm
        /// </summary>
        HIHI = 23,
        /// <summary>
        /// LO alarm
        /// </summary>
        LOLO = 24,
        /// <summary>
        /// HI warning
        /// </summary>
        HI = 25,
        /// <summary>
        /// LO warning
        /// </summary>
        LO = 26,
        /// <summary>
        /// Deleted from alarm checks
        /// </summary>
        DELETED_ALARM = 27,
        /// <summary>
        /// Inhibited by cutout point
        /// </summary>
        INHIBITED = 28,
        /// <summary>
        /// Good
        /// </summary>
        GOOD = 29
    };


    /// <summary>
    /// Print quality enumerator to an output stream
    /// </summary>
    inline std::ostream& operator<<(std::ostream& os, Quality qual)
    {
        switch ((int)qual)
        {
            case (-1): os << "AUTO_DETERMINED"; break;
            case (0):  os << "UNKNOWN";         break;
            case (1):  os << "DELETED";         break;
            case (2):  os << "NOT_CALCULABLE";  break;
            case (3):  os << "INVALID";         break;
            case (4):  os << "READ_ERROR";      break;
            case (5):  os << "OPEN_THRM_CPL";   break;
            case (6):  os << "BAD";             break;
            case (7):  os << "HI_RSN_LIMIT";    break;
            case (8):  os << "LOW_RSN_LIMIT";   break;
            case (9):  os << "OLD";             break;
            case (10): os << "SUSPECT_HIHI";    break;
            case (11): os << "SUSPECT_LOLO";    break;
            case (12): os << "SUSPECT_HI";      break;
            case (13): os << "SUSPECT_LO";      break;
            case (14): os << "SUSPECT";         break;
            case (15): os << "SUSPECT_ALARM";   break;
            case (16): os << "INSERTED_HIHI";   break;
            case (17): os << "INSERTED_LOLO";   break;
            case (18): os << "INSERTED_HI";     break;
            case (19): os << "INSERTED_LO";     break;
            case (20): os << "INSERTED";        break;
            case (21): os << "INSERTED_ALARM";  break;
            case (22): os << "ALARM";           break;
            case (23): os << "HIHI";            break;
            case (24): os << "LOLO";            break;
            case (25): os << "HI";              break;
            case (26): os << "LO";              break;
            case (27): os << "DELETED_ALARM";   break;
            case (28): os << "INHIBITED";       break;
            case (29): os << "GOOD";            break;
        }
        return os;
    }

    /// <summary>
    /// Converts a Quality int into a Quality enumerator.
    /// </summary>
    /// <param name="qual">[IN] Integer value of the PMS quality.</param>
    /// <returns>Quality enumerator</returns>
    Quality ConvertQuality(const int qual);
}
