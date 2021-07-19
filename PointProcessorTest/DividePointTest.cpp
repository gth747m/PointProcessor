#include "pch.h"

using namespace PointProcessor;

TEST(DividePoint, Int32)
{
    auto inpA = ExternalPoint<int32_t>();
    auto inpB = ExternalPoint<int32_t>();
    auto div = DividePoint<int32_t>();
    inpA.set_value(4);
    inpB.set_value(4);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    div.add_input(&inpA);
    div.add_input(&inpB);
    div.calculate();
    EXPECT_EQ(div.get_value<int32_t>(), 1);
    EXPECT_EQ(div.get_quality(), Quality::GOOD);
    inpB.set_value(2);
    div.calculate();
    EXPECT_EQ(div.get_value<int32_t>(), 2);
    EXPECT_EQ(div.get_quality(), Quality::GOOD);
    inpB.set_value(0);
    div.calculate();
    EXPECT_EQ(div.get_quality(), Quality::NOT_CALCULABLE);
}

TEST(DividePoint, Int64)
{
    auto inpA = ExternalPoint<int64_t>();
    auto inpB = ExternalPoint<int64_t>();
    auto div = DividePoint<int64_t>();
    inpA.set_value(4);
    inpB.set_value(4);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    div.add_input(&inpA);
    div.add_input(&inpB);
    div.calculate();
    EXPECT_EQ(div.get_value<int64_t>(), 1);
    EXPECT_EQ(div.get_quality(), Quality::GOOD);
    inpB.set_value(2);
    div.calculate();
    EXPECT_EQ(div.get_value<int64_t>(), 2);
    EXPECT_EQ(div.get_quality(), Quality::GOOD);
    inpB.set_value(0);
    div.calculate();
    EXPECT_EQ(div.get_quality(), Quality::NOT_CALCULABLE);
}

TEST(DividePoint, Float)
{
    auto inpA = ExternalPoint<float>();
    auto inpB = ExternalPoint<float>();
    auto div = DividePoint<float>();
    inpA.set_value(4.0f);
    inpB.set_value(4.0f);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    div.add_input(&inpA);
    div.add_input(&inpB);
    div.calculate();
    EXPECT_EQ(div.get_value<float>(), 1.0f);
    EXPECT_EQ(div.get_quality(), Quality::GOOD);
    inpA.set_value(2.0f);
    div.calculate();
    EXPECT_EQ(div.get_value<float>(), 0.5f);
    EXPECT_EQ(div.get_quality(), Quality::GOOD);
    inpB.set_value(0.0f);
    div.calculate();
    EXPECT_EQ(div.get_quality(), Quality::NOT_CALCULABLE);
}

TEST(DividePoint, Double)
{
    auto inpA = ExternalPoint<double>();
    auto inpB = ExternalPoint<double>();
    auto div = DividePoint<double>();
    inpA.set_value(4.0);
    inpB.set_value(4.0);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    div.add_input(&inpA);
    div.add_input(&inpB);
    div.calculate();
    EXPECT_EQ(div.get_value<double>(), 1.0);
    EXPECT_EQ(div.get_quality(), Quality::GOOD);
    inpA.set_value(2);
    div.calculate();
    EXPECT_EQ(div.get_value<double>(), 0.5);
    EXPECT_EQ(div.get_quality(), Quality::GOOD);
    inpB.set_value(0.0);
    div.calculate();
    EXPECT_EQ(div.get_quality(), Quality::NOT_CALCULABLE);
}