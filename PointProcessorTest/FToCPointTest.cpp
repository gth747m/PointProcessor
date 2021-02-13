#include "pch.h"

using namespace PointProcessor;

TEST(FToCPoint, FToCFloat)
{
    auto inp = ExternalPoint<float>();
    auto celsius = FToCPoint<float>();
    celsius.set_input(&inp);
    inp.set_value(32.0f);
    celsius.calculate();
    ASSERT_EQ(celsius.get_value(), 0.0f);
    inp.set_value(68.0);
    celsius.calculate();
    ASSERT_EQ(celsius.get_value(), 20.0f);
    inp.set_value(212.0f);
    celsius.calculate();
    ASSERT_EQ(celsius.get_value(), 100.0f);
}

TEST(FToCPoint, FToCDouble)
{
    auto inp = ExternalPoint<double>();
    auto celsius = FToCPoint<double>();
    celsius.set_input(&inp);
    inp.set_value(32.0);
    celsius.calculate();
    ASSERT_EQ(celsius.get_value(), 0.0);
    inp.set_value(68.0);
    celsius.calculate();
    ASSERT_EQ(celsius.get_value(), 20.0);
    inp.set_value(212.0);
    celsius.calculate();
    ASSERT_EQ(celsius.get_value(), 100.0);
}