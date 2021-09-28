#include "pch.h"

using namespace point_processor;

TEST(IntegerPrecisionTest, Int32)
{
    double values[1] = { 0.0 };
    Quality qualities[1] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[1];
    auto ext = ExternalPoint<int32_t>(&values[0], &qualities[0], &durations[0]);
    int32_t val = std::numeric_limits<int32_t>::max();
    ext.set_value(val);
    EXPECT_EQ(ext.get_value<int32_t>(), val);
    val = 0;
    ext.set_value(val);
    EXPECT_EQ(ext.get_value<int32_t>(), val);
    val = std::numeric_limits<int32_t>::min();
    ext.set_value(val);
    EXPECT_EQ(ext.get_value<int32_t>(), val);
}

TEST(IntegerPrecisionTest, Int64)
{
    double values[1] = { 0.0 };
    Quality qualities[1] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[1];
    // Can't properly store integers above or below (+/-)2^53
    auto ext = ExternalPoint<int64_t>(&values[0], &qualities[0], &durations[0]);
    // below -2^53 we start losing precision, every other digit down to -2^54, 
    // then increasing precision loss from there
    int64_t val = -9007199254740993; // -2^53 - 1
    ext.set_value(++val); // -2^53
    EXPECT_EQ(ext.get_value<int64_t>(), val);
    val = 0;
    ext.set_value(val);
    EXPECT_EQ(ext.get_value<int64_t>(), val);
    // maximum precision we can handle storing everything in a double (2^53)
    val = 9007199254740992; // 2^53 
    ext.set_value(val);
    EXPECT_EQ(ext.get_value<int64_t>(), val);
    // above 2^53 we start losing precision, every other digit up to 2^54, 
    // then increasing precision loss from there
    ext.set_value(++val); // 2^53 + 1
    EXPECT_NE(ext.get_value<int64_t>(), val);
    ext.set_value(++val); // 2^53 + 2
    EXPECT_EQ(ext.get_value<int64_t>(), val);
    // Max Int64
    val = std::numeric_limits<int64_t>::max();
    ext.set_value(val);
    EXPECT_NE(ext.get_value<int64_t>(), val);
    /*
     * Don't verify this, it would take something like 27 years on my laptop
     *
    auto ext = ExternalPoint<int64_t>();
    int64_t val = -9007199254740993; // -2^53 - 1
    ext.set_value(val);
    EXPECT_NE(ext.get_value<int64_t>(), val);
    for (val++; val < 9007199254740993; val++)
    {
        ext.set_value(val);
        EXPECT_EQ(ext.get_value<int64_t>(), val);
    }
    */
}