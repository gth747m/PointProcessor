#include "pch.h"

using namespace point_processor;

TEST(SumPoint, Int32)
{
    auto inpA = ExternalPoint<int32_t>();
    auto inpB = ExternalPoint<int32_t>();
    auto inpC = ExternalPoint<int32_t>();
    auto sum = SumPoint<int32_t>();
    sum.add_input(&inpA);
    sum.add_input(&inpB);
    sum.add_input(&inpC);
    inpA.set_value(1);
    inpB.set_value(2);
    inpC.set_value(3);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    inpC.set_quality(Quality::GOOD);
    sum.calculate();
    EXPECT_EQ(sum.get_value<int32_t>(), 6);
    EXPECT_EQ(sum.get_quality(), Quality::GOOD);
    inpA.set_value(4);
    inpB.set_value(5);
    inpC.set_value(6);
    sum.calculate();
    EXPECT_EQ(sum.get_value<int32_t>(), 15);
    EXPECT_EQ(sum.get_quality(), Quality::GOOD);
}

TEST(SumPoint, Int64)
{
    auto inpA = ExternalPoint<int64_t>();
    auto inpB = ExternalPoint<int64_t>();
    auto inpC = ExternalPoint<int64_t>();
    auto sum = SumPoint<int64_t>();
    sum.add_input(&inpA);
    sum.add_input(&inpB);
    sum.add_input(&inpC);
    inpA.set_value(1);
    inpB.set_value(2);
    inpC.set_value(3);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    inpC.set_quality(Quality::GOOD);
    sum.calculate();
    EXPECT_EQ(sum.get_value<int64_t>(), 6);
    EXPECT_EQ(sum.get_quality(), Quality::GOOD);
    inpA.set_value(4);
    inpB.set_value(5);
    inpC.set_value(6);
    sum.calculate();
    EXPECT_EQ(sum.get_value<int64_t>(), 15);
    EXPECT_EQ(sum.get_quality(), Quality::GOOD);
}

TEST(SumPoint, Float)
{
    auto inpA = ExternalPoint<float>();
    auto inpB = ExternalPoint<float>();
    auto inpC = ExternalPoint<float>();
    auto sum = SumPoint<float>();
    sum.add_input(&inpA);
    sum.add_input(&inpB);
    sum.add_input(&inpC);
    inpA.set_value(1.5f);
    inpB.set_value(2.2f);
    inpC.set_value(3.3f);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    inpC.set_quality(Quality::GOOD);
    sum.calculate();
    EXPECT_FLOAT_EQ(sum.get_value<float>(), 7.0f);
    EXPECT_EQ(sum.get_quality(), Quality::GOOD);
    inpA.set_value(15.0f);
    inpB.set_value(35.2f);
    inpC.set_value(18.8f);
    sum.calculate();
    EXPECT_FLOAT_EQ(sum.get_value<float>(), 69.0f);
    EXPECT_EQ(sum.get_quality(), Quality::GOOD);
}

TEST(SumPoint, Double)
{
    auto inpA = ExternalPoint<double>();
    auto inpB = ExternalPoint<double>();
    auto inpC = ExternalPoint<double>();
    auto sum = SumPoint<double>();
    sum.add_input(&inpA);
    sum.add_input(&inpB);
    sum.add_input(&inpC);
    inpA.set_value(1.5);
    inpB.set_value(2.2);
    inpC.set_value(3.3);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    inpC.set_quality(Quality::GOOD);
    sum.calculate();
    EXPECT_DOUBLE_EQ(sum.get_value<double>(), 7.0);
    EXPECT_EQ(sum.get_quality(), Quality::GOOD);
    inpA.set_value(15);
    inpB.set_value(35.2);
    inpC.set_value(18.8);
    sum.calculate();
    EXPECT_DOUBLE_EQ(sum.get_value<double>(), 69.0);
    EXPECT_EQ(sum.get_quality(), Quality::GOOD);
}