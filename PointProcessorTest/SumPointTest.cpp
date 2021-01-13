#include "pch.h"

using namespace PointProcessor;

TEST(SumPoint, SumInt32)
{
    auto inpA = Point<int32_t>();
    auto inpB = Point<int32_t>();
    auto inpC = Point<int32_t>();
    auto sum = SumPoint<int32_t>();
    sum.add_input(&inpA);
    sum.add_input(&inpB);
    sum.add_input(&inpC);
    inpA.set_value(1);
    inpB.set_value(2);
    inpC.set_value(3);
    sum.calculate();
    ASSERT_EQ(sum.get_value(), 6);
    inpA.set_value(4);
    inpB.set_value(5);
    inpC.set_value(6);
    sum.calculate();
    ASSERT_EQ(sum.get_value(), 15);
}

TEST(SumPoint, SumInt64)
{
    auto inpA = Point<int64_t>();
    auto inpB = Point<int64_t>();
    auto inpC = Point<int64_t>();
    auto sum = SumPoint<int64_t>();
    sum.add_input(&inpA);
    sum.add_input(&inpB);
    sum.add_input(&inpC);
    inpA.set_value(1);
    inpB.set_value(2);
    inpC.set_value(3);
    sum.calculate();
    ASSERT_EQ(sum.get_value(), 6);
    inpA.set_value(4);
    inpB.set_value(5);
    inpC.set_value(6);
    sum.calculate();
    ASSERT_EQ(sum.get_value(), 15);
}

TEST(SumPoint, SumFloat)
{
    auto inpA = Point<float>();
    auto inpB = Point<float>();
    auto inpC = Point<float>();
    auto sum = SumPoint<float>();
    sum.add_input(&inpA);
    sum.add_input(&inpB);
    sum.add_input(&inpC);
    inpA.set_value(1.5);
    inpB.set_value(2.2);
    inpC.set_value(3.3);
    sum.calculate();
    ASSERT_EQ(sum.get_value(), 7.0);
    inpA.set_value(15);
    inpB.set_value(35.2);
    inpC.set_value(18.8);
    sum.calculate();
    ASSERT_EQ(sum.get_value(), 69.0);
}

TEST(SumPoint, SumDouble)
{
    auto inpA = Point<double>();
    auto inpB = Point<double>();
    auto inpC = Point<double>();
    auto sum = SumPoint<double>();
    sum.add_input(&inpA);
    sum.add_input(&inpB);
    sum.add_input(&inpC);
    inpA.set_value(1.5);
    inpB.set_value(2.2);
    inpC.set_value(3.3);
    sum.calculate();
    ASSERT_EQ(sum.get_value(), 7.0);
    inpA.set_value(15);
    inpB.set_value(35.2);
    inpC.set_value(18.8);
    sum.calculate();
    ASSERT_EQ(sum.get_value(), 69.0);
}