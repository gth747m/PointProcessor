#include "pch.h"

using namespace PointProcessor;

TEST(SumPoint, SumInt)
{
    Point<int> inpA = Point<int>();
    Point<int> inpB = Point<int>();
    Point<int> inpC = Point<int>();
    SumPoint<int> sum = SumPoint<int>();
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
    Point<float> inpA = Point<float>();
    Point<float> inpB = Point<float>();
    Point<float> inpC = Point<float>();
    SumPoint<float> sum = SumPoint<float>();
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