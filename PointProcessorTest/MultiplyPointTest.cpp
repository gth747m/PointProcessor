#include "pch.h"

using namespace PointProcessor;

TEST(MultiplyPoint, MultiplyPointInt32)
{
    auto inpA = ExternalPoint<int32_t>();
    auto inpB = ExternalPoint<int32_t>();
    auto div = MultiplyPoint<int32_t>();
    inpA.set_value(4);
    inpB.set_value(4);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    div.add_input(&inpA);
    div.add_input(&inpB);
    div.calculate();
    EXPECT_EQ(div.get_value<int32_t>(), 16);
    EXPECT_EQ(div.get_quality(), Quality::GOOD);
    inpB.set_value(2);
    div.calculate();
    EXPECT_EQ(div.get_value<int32_t>(), 8);
    EXPECT_EQ(div.get_quality(), Quality::GOOD);
}

TEST(MultiplyPoint, MultiplyPointInt64)
{
    auto inpA = ExternalPoint<int64_t>();
    auto inpB = ExternalPoint<int64_t>();
    auto div = MultiplyPoint<int64_t>();
    inpA.set_value(4);
    inpB.set_value(4);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    div.add_input(&inpA);
    div.add_input(&inpB);
    div.calculate();
    EXPECT_EQ(div.get_value<int64_t>(), 16);
    EXPECT_EQ(div.get_quality(), Quality::GOOD);
    inpB.set_value(2);
    div.calculate();
    EXPECT_EQ(div.get_value<int64_t>(), 8);
    EXPECT_EQ(div.get_quality(), Quality::GOOD);
}

TEST(MultiplyPoint, MultiplyPointFloat)
{
    auto inpA = ExternalPoint<float>();
    auto inpB = ExternalPoint<float>();
    auto div = MultiplyPoint<float>();
    inpA.set_value(4.0f);
    inpB.set_value(4.0f);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    div.add_input(&inpA);
    div.add_input(&inpB);
    div.calculate();
    EXPECT_EQ(div.get_value<float>(), 16.0f);
    EXPECT_EQ(div.get_quality(), Quality::GOOD);
    inpA.set_value(2.0f);
    div.calculate();
    EXPECT_EQ(div.get_value<float>(), 8.0f);
    EXPECT_EQ(div.get_quality(), Quality::GOOD);
}

TEST(MultiplyPoint, MultiplyPointDouble)
{
    auto inpA = ExternalPoint<double>();
    auto inpB = ExternalPoint<double>();
    auto div = MultiplyPoint<double>();
    inpA.set_value(4.0);
    inpB.set_value(4.0);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    div.add_input(&inpA);
    div.add_input(&inpB);
    div.calculate();
    EXPECT_EQ(div.get_value<double>(), 16.0);
    EXPECT_EQ(div.get_quality(), Quality::GOOD);
    inpA.set_value(2);
    div.calculate();
    EXPECT_EQ(div.get_value<double>(), 8.0);
    EXPECT_EQ(div.get_quality(), Quality::GOOD);
}