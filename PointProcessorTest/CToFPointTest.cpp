#include "pch.h"

using namespace PointProcessor;

TEST(CToFPoint, CToFFloat)
{
    auto inp = ExternalPoint<float>();
    auto celsius = CToFPoint<float>();
    celsius.set_input(&inp);
    inp.set_value(0.0f);
    celsius.calculate();
    EXPECT_FLOAT_EQ(celsius.get_value<float>(), 32.0f);
    inp.set_value(20.0f);
    celsius.calculate();
    EXPECT_FLOAT_EQ(celsius.get_value<float>(), 68.0f);
    inp.set_value(100.0f);
    celsius.calculate();
    EXPECT_FLOAT_EQ(celsius.get_value<float>(), 212.0f);
}

TEST(CToFPoint, CToFDouble)
{
    auto inp = ExternalPoint<double>();
    auto celsius = CToFPoint<double>();
    celsius.set_input(&inp);
    inp.set_value(0.0);
    celsius.calculate();
    EXPECT_DOUBLE_EQ(celsius.get_value<double>(), 32.0);
    inp.set_value(20.0);
    celsius.calculate();
    EXPECT_DOUBLE_EQ(celsius.get_value<double>(), 68.0);
    inp.set_value(100.0);
    celsius.calculate();
    EXPECT_DOUBLE_EQ(celsius.get_value<double>(), 212.0);
}
