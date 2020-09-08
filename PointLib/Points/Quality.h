#pragma once

enum Quality
{
    /// <summary>
    /// Good
    /// </summary>
    QUAL_GOOD = 0,
    /// <summary>
    /// Low Alarm Limit
    /// </summary>
    QUAL_LOLO,
    /// <summary>
    /// Low Reasonable Limit
    /// </summary>
    QUAL_LO,
    /// <summary>
    /// High Reasonable Limit
    /// </summary>
    QUAL_HI,
    /// <summary>
    /// High Alarm Limit
    /// </summary>
    QUAL_HIHI,
    /// <summary>
    /// Bad
    /// </summary>
    QUAL_BAD,
    /// <summary>
    /// Unknown
    /// </summary>
    QUAL_UNK
};