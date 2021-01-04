#include "Quality.h"

namespace PointProcessor
{
    /// <summary>
    /// Converts a Quality int into a Quality enumerator.
    /// </summary>
    /// <param name="qual">[IN] Integer value of the PMS quality.</param>
    /// <returns>Quality enumerator</returns>
    Quality ConvertQuality(const int qual)
    {
        switch (qual)
        {
            case (1):  return Quality::DELETED;
            case (2):  return Quality::NOT_CALCULABLE;
            case (3):  return Quality::INVALID;
            case (4):  return Quality::READ_ERROR;
            case (5):  return Quality::OPEN_THRM_CPL;
            case (6):  return Quality::BAD;
            case (7):  return Quality::HI_RSN_LIMIT;
            case (8):  return Quality::LOW_RSN_LIMIT;
            case (9):  return Quality::OLD;
            case (10): return Quality::SUSPECT_HIHI;
            case (11): return Quality::SUSPECT_LOLO;
            case (12): return Quality::SUSPECT_HI;
            case (13): return Quality::SUSPECT_LO;
            case (14): return Quality::SUSPECT;
            case (15): return Quality::SUSPECT_ALARM;
            case (16): return Quality::INSERTED_HIHI;
            case (17): return Quality::INSERTED_LOLO;
            case (18): return Quality::INSERTED_HI;
            case (19): return Quality::INSERTED_LO;
            case (20): return Quality::INSERTED;
            case (21): return Quality::INSERTED_ALARM;
            case (22): return Quality::ALARM;
            case (23): return Quality::HIHI;
            case (24): return Quality::LOLO;
            case (25): return Quality::HI;
            case (26): return Quality::LO;
            case (27): return Quality::DELETED_ALARM;
            case (28): return Quality::INHIBITED;
            case (29): return Quality::GOOD;
            case (-1): return Quality::AUTO_DETERMINED;
            default:   return Quality::UNKNOWN;
        }
    }
}