#include "pch.h"

using namespace PointProcessor;

TEST(CToFPoint, Float)
{
    auto inp = ExternalPoint<float>();
    auto farenheit = CToFPoint<float>();
    farenheit.set_input(&inp);
    inp.set_value(0.0f);
    inp.set_quality(Quality::GOOD);
    farenheit.calculate();
    EXPECT_FLOAT_EQ(farenheit.get_value<float>(), 32.0f);
    EXPECT_EQ(farenheit.get_quality(), Quality::GOOD);
    inp.set_value(20.0f);
    farenheit.calculate();
    EXPECT_FLOAT_EQ(farenheit.get_value<float>(), 68.0f);
    EXPECT_EQ(farenheit.get_quality(), Quality::GOOD);
    inp.set_value(100.0f);
    farenheit.calculate();
    EXPECT_FLOAT_EQ(farenheit.get_value<float>(), 212.0f);
    EXPECT_EQ(farenheit.get_quality(), Quality::GOOD);
}

TEST(CToFPoint, Double)
{
    auto inp = ExternalPoint<double>();
    auto farenheit = CToFPoint<double>();
    farenheit.set_input(&inp);
    inp.set_value(0.0);
    inp.set_quality(Quality::GOOD);
    farenheit.calculate();
    EXPECT_DOUBLE_EQ(farenheit.get_value<double>(), 32.0);
    EXPECT_EQ(farenheit.get_quality(), Quality::GOOD);
    inp.set_value(20.0);
    farenheit.calculate();
    EXPECT_DOUBLE_EQ(farenheit.get_value<double>(), 68.0);
    EXPECT_EQ(farenheit.get_quality(), Quality::GOOD);
    inp.set_value(100.0);
    farenheit.calculate();
    EXPECT_DOUBLE_EQ(farenheit.get_value<double>(), 212.0);
    EXPECT_EQ(farenheit.get_quality(), Quality::GOOD);
}
