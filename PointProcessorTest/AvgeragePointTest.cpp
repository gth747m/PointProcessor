#include "pch.h"

using namespace point_processor;

TEST(AveragePoint, Int32)
{
    auto inpA = ExternalPoint<int32_t>();
    auto inpB = ExternalPoint<int32_t>();
    auto inpC = ExternalPoint<int32_t>();
    auto avg = AveragePoint<int32_t>();
    avg.add_input(&inpA);
    avg.add_input(&inpB);
    avg.add_input(&inpC);
    inpA.set_value(2);
    inpB.set_value(4);
    inpC.set_value(3);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    inpC.set_quality(Quality::GOOD);
    avg.calculate();
    EXPECT_EQ(avg.get_value<int32_t>(), 3);
}

TEST(AveragePoint, Int64)
{
    auto inpA = ExternalPoint<int64_t>();
    auto inpB = ExternalPoint<int64_t>();
    auto inpC = ExternalPoint<int64_t>();
    auto avg = AveragePoint<int64_t>();
    avg.add_input(&inpA);
    avg.add_input(&inpB);
    avg.add_input(&inpC);
    inpA.set_value(25);
    inpB.set_value(45);
    inpC.set_value(20);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    inpC.set_quality(Quality::GOOD);
    avg.calculate();
    EXPECT_EQ(avg.get_value<int64_t>(), 30);
}

TEST(AveragePoint, Float)
{
    auto inpA = ExternalPoint<float>();
    auto inpB = ExternalPoint<float>();
    auto inpC = ExternalPoint<float>();
    auto avg = AveragePoint<float>();
    avg.add_input(&inpA);
    avg.add_input(&inpB);
    avg.add_input(&inpC);
    inpA.set_value(2.5f);
    inpB.set_value(9.5f);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    inpC.set_quality(Quality::GOOD);
    avg.calculate();
    EXPECT_FLOAT_EQ(avg.get_value<float>(), 4.0f);
}

TEST(AveragePoint, Double)
{
    auto inpA = ExternalPoint<double>();
    auto inpB = ExternalPoint<double>();
    auto avg = AveragePoint<double>();
    avg.add_input(&inpA);
    avg.add_input(&inpB);
    inpA.set_value(25.25);
    inpB.set_value(45.25);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    avg.calculate();
    EXPECT_DOUBLE_EQ(avg.get_value<double>(), 35.25);
}
