#include "pch.h"

using namespace PointProcessor;

TEST(ExternalPoint, Int32)
{
    auto ext = ExternalPoint<int32_t>();
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
    auto ext = ExternalPoint<int64_t>();
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
    auto ext = ExternalPoint<float>();
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
    auto ext = ExternalPoint<double>();
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
