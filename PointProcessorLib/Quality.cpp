#include "Quality.h"

namespace PointProcessor
{
    /// <summary>
    /// Converts a Quality int into a Quality enumerator.
    /// </summary>
    /// <param name="qual">[IN] Integer value of the PMS quality.</param>
    /// <returns>Quality enumerator</returns>
    Quality ConvertQuality(const uint qual)
    {
        switch (qual)
        {
            case (0xFFFFFFFF): return Quality::AUTO_DETERMINED;
            case (0x00000002): return Quality::DELETED;
            case (0x00000004): return Quality::NOT_CALCULABLE;
            case (0x00000008): return Quality::INVALID;
            case (0x00000010): return Quality::READ_ERROR;
            case (0x00000020): return Quality::OPEN_THRM_CPL;
            case (0x00000040): return Quality::BAD;
            case (0x00000080): return Quality::HI_RSN_LIMIT;
            case (0x00000100): return Quality::LOW_RSN_LIMIT;
            case (0x00000200): return Quality::OLD;
            case (0x00000400): return Quality::SUSPECT_HIHI;
            case (0x00000800): return Quality::SUSPECT_LOLO;
            case (0x00001000): return Quality::SUSPECT_HI;
            case (0x00002000): return Quality::SUSPECT_LO;
            case (0x00004000): return Quality::SUSPECT;
            case (0x00008000): return Quality::SUSPECT_ALARM;
            case (0x00010000): return Quality::INSERTED_HIHI;
            case (0x00020000): return Quality::INSERTED_LOLO;
            case (0x00040000): return Quality::INSERTED_HI;
            case (0x00080000): return Quality::INSERTED_LO;
            case (0x00100000): return Quality::INSERTED;
            case (0x00200000): return Quality::INSERTED_ALARM;
            case (0x00400000): return Quality::ALARM;
            case (0x00800000): return Quality::HIHI;
            case (0x01000000): return Quality::LOLO;
            case (0x02000000): return Quality::HI;
            case (0x04000000): return Quality::LO;
            case (0x08000000): return Quality::DELETED_ALARM;
            case (0x10000000): return Quality::INHIBITED;
            case (0x20000000): return Quality::GOOD;
            default:           return Quality::UNKNOWN;
        }
    }

    /// <summary>
    /// Check if this quality is usable for calculations
    /// <summary>
    /// <param name="qual">[IN] Quality to test</param>
    /// <returns>Whether or not the quality is usable for calculation</returns>
    bool IsUsableQuality(const Quality qual)
    {
        return (uint)qual & (
            (uint)Quality::HI_RSN_LIMIT   |
            (uint)Quality::LOW_RSN_LIMIT  |
            (uint)Quality::SUSPECT_HIHI   |
            (uint)Quality::SUSPECT_LOLO   |
            (uint)Quality::SUSPECT_HI     |
            (uint)Quality::SUSPECT_LO     |
            (uint)Quality::SUSPECT        |
            (uint)Quality::SUSPECT_ALARM  |
            (uint)Quality::INSERTED_HIHI  |
            (uint)Quality::INSERTED_LOLO  |
            (uint)Quality::INSERTED_HI    |
            (uint)Quality::INSERTED_LO    |
            (uint)Quality::INSERTED       |
            (uint)Quality::INSERTED_ALARM |
            (uint)Quality::ALARM          |
            (uint)Quality::HIHI           |
            (uint)Quality::LOLO           |
            (uint)Quality::HI             |
            (uint)Quality::LO             |
            (uint)Quality::GOOD
        );
    }
}