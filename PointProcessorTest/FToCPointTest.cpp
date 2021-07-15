#include "pch.h"

using namespace PointProcessor;

TEST(FToCPoint, FToCFloat)
{
    auto inp = ExternalPoint<float>();
    auto celsius = FToCPoint<float>();
    celsius.set_input(&inp);
    inp.set_value(32.0f);
    inp.set_quality(Quality::GOOD);
    celsius.calculate();
    EXPECT_FLOAT_EQ(celsius.get_value<float>(), 0.0f);
    EXPECT_EQ(celsius.get_quality(), Quality::GOOD);
    inp.set_value(68.0f);
    celsius.calculate();
    EXPECT_FLOAT_EQ(celsius.get_value<float>(), 20.0f);
    EXPECT_EQ(celsius.get_quality(), Quality::GOOD);
    inp.set_value(212.0f);
    celsius.calculate();
    EXPECT_FLOAT_EQ(celsius.get_value<float>(), 100.0f);
    EXPECT_EQ(celsius.get_quality(), Quality::GOOD);
}

TEST(FToCPoint, FToCDouble)
{
    auto inp = ExternalPoint<double>();
    auto celsius = FToCPoint<double>();
    celsius.set_input(&inp);
    inp.set_value(32.0);
    inp.set_quality(Quality::GOOD);
    celsius.calculate();
    EXPECT_DOUBLE_EQ(celsius.get_value<double>(), 0.0);
    EXPECT_EQ(celsius.get_quality(), Quality::GOOD);
    inp.set_value(68.0);
    celsius.calculate();
    EXPECT_DOUBLE_EQ(celsius.get_value<double>(), 20.0);
    EXPECT_EQ(celsius.get_quality(), Quality::GOOD);
    inp.set_value(212.0);
    celsius.calculate();
    EXPECT_DOUBLE_EQ(celsius.get_value<double>(), 100.0);
    EXPECT_EQ(celsius.get_quality(), Quality::GOOD);
}