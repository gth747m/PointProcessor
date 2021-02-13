#include "pch.h"

using namespace PointProcessor;

TEST(AveragePoint, AverageInt32)
{
    auto inpA = Point<int32_t>();
    auto inpB = Point<int32_t>();
    auto inpC = Point<int32_t>();
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
    ASSERT_EQ(avg.get_value(), 3);
}

TEST(AveragePoint, AverageInt64)
{
    auto inpA = Point<int64_t>();
    auto inpB = Point<int64_t>();
    auto inpC = Point<int64_t>();
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
    ASSERT_EQ(avg.get_value(), 30);
}

TEST(AveragePoint, AverageFloat)
{
    auto inpA = Point<float>();
    auto inpB = Point<float>();
    auto inpC = Point<float>();
    auto avg = AveragePoint<float>();
    avg.add_input(&inpA);
    avg.add_input(&inpB);
    avg.add_input(&inpC);
    inpA.set_value(2.5);
    inpB.set_value(9.5);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    inpC.set_quality(Quality::GOOD);
    avg.calculate();
    ASSERT_EQ(avg.get_value(), 4.0);
}

TEST(AveragePoint, AverageDouble)
{
    auto inpA = Point<double>();
    auto inpB = Point<double>();
    auto avg = AveragePoint<double>();
    avg.add_input(&inpA);
    avg.add_input(&inpB);
    inpA.set_value(25.25);
    inpB.set_value(45.25);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    avg.calculate();
    ASSERT_EQ(avg.get_value(), 35.25);
}
