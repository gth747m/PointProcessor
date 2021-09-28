#include "pch.h"

using namespace point_processor;

TEST(ExternalPoint, Int32)
{
    double values[2] = { 0.0 };
    Quality qualities[2] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[2];
    auto ext = ExternalPoint<int32_t>(&values[0], &qualities[0], &durations[0]);
    ext.set_quality(Quality::GOOD);
    for (int i = 0; i < 1000; i++)
    {
        ext.set_value(i);
        EXPECT_EQ(ext.get_value<int32_t>(), i);
        EXPECT_EQ(ext.get_quality(), Quality::GOOD);
    }
}

TEST(ExternalPoint, Int64)
{
    double values[2] = { 0.0 };
    Quality qualities[2] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[2];
    auto ext = ExternalPoint<int64_t>(&values[0], &qualities[0], &durations[0]);
    ext.set_quality(Quality::GOOD);
    for (int i = 0; i < 1000; i++)
    {
        ext.set_value(i);
        EXPECT_EQ(ext.get_value<int64_t>(), i);
        EXPECT_EQ(ext.get_quality(), Quality::GOOD);
    }
}

TEST(ExternalPoint, Float)
{
    double values[2] = { 0.0 };
    Quality qualities[2] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[2];
    auto ext = ExternalPoint<float>(&values[0], &qualities[0], &durations[0]);
    ext.set_value(10.0f);
    ext.set_quality(Quality::GOOD);
    EXPECT_EQ(ext.get_value<float>(), 10.0f);
    EXPECT_EQ(ext.get_quality(), Quality::GOOD);
    for (int i = 0; i < 1000; i++)
    {
        ext.set_value(i * 1.0f);
        EXPECT_EQ(ext.get_value<float>(), i * 1.0f);
        EXPECT_EQ(ext.get_quality(), Quality::GOOD);
    }
}

TEST(ExternalPoint, Double)
{
    double values[2] = { 0.0 };
    Quality qualities[2] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[2];
    auto ext = ExternalPoint<double>(&values[0], &qualities[0], &durations[0]);
    ext.set_value(10.0);
    ext.set_quality(Quality::GOOD);
    EXPECT_EQ(ext.get_value<double>(), 10.0);
    EXPECT_EQ(ext.get_quality(), Quality::GOOD);
    for (int i = 0; i < 1000; i++)
    {
        ext.set_value(i * 1.0);
        EXPECT_EQ(ext.get_value<double>(), i * 1.0);
        EXPECT_EQ(ext.get_quality(), Quality::GOOD);
    }
}
