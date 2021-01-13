#include "pch.h"

using namespace PointProcessor;

TEST(CToFPoint, CToFFloat)
{
    auto inp = Point<float>();
    auto celsius = CToFPoint<float>();
    celsius.set_input(&inp);
    inp.set_value(0.0f);
    celsius.calculate();
    ASSERT_EQ(celsius.get_value(), 32.0f);
    inp.set_value(20.0f);
    celsius.calculate();
    ASSERT_EQ(celsius.get_value(), 68.0f);
    inp.set_value(100.0f);
    celsius.calculate();
    ASSERT_EQ(celsius.get_value(), 212.0f);
}

TEST(CToFPoint, CToFDouble)
{
    auto inp = Point<double>();
    auto celsius = CToFPoint<double>();
    celsius.set_input(&inp);
    inp.set_value(0.0);
    celsius.calculate();
    ASSERT_EQ(celsius.get_value(), 32.0);
    inp.set_value(20.0);
    celsius.calculate();
    ASSERT_EQ(celsius.get_value(), 68.0);
    inp.set_value(100.0);
    celsius.calculate();
    ASSERT_EQ(celsius.get_value(), 212.0);
}
