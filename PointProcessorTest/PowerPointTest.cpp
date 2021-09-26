#include "pch.h"

using namespace point_processor;

TEST(PowerPointTest, Int32)
{
    auto inp = ExternalPoint<int32_t>();
    auto power = PowerPoint<int32_t>();
    inp.set_value(2);
    inp.set_quality(Quality::GOOD);
    power.set_input(&inp);
    power.set_power(2);
    power.calculate();
    EXPECT_EQ(power.get_value<int32_t>(), 4);
    EXPECT_EQ(power.get_quality(), Quality::GOOD);
    inp.set_value(3);
    power.calculate();
    EXPECT_EQ(power.get_value<int32_t>(), 9);
    EXPECT_EQ(power.get_quality(), Quality::GOOD);
    power.set_power(3);
    power.calculate();
    EXPECT_EQ(power.get_value<int32_t>(), 27);
    EXPECT_EQ(power.get_quality(), Quality::GOOD);
}

TEST(PowerPointTest, Int64)
{
    auto inp = ExternalPoint<int64_t>();
    auto power = PowerPoint<int64_t>();
    inp.set_value(2);
    inp.set_quality(Quality::GOOD);
    power.set_input(&inp);
    power.set_power(2);
    power.calculate();
    EXPECT_EQ(power.get_value<int64_t>(), 4);
    EXPECT_EQ(power.get_quality(), Quality::GOOD);
    inp.set_value(3);
    power.calculate();
    EXPECT_EQ(power.get_value<int64_t>(), 9);
    EXPECT_EQ(power.get_quality(), Quality::GOOD);
    inp.set_value(2147483647);
    power.calculate();
    EXPECT_EQ(power.get_value<int64_t>(), 4611686014132420608);
    EXPECT_EQ(power.get_quality(), Quality::GOOD);
}

TEST(PowerPointTest, Float)
{
    auto inp = ExternalPoint<float>();
    auto power = PowerPoint<float>();
    inp.set_value(2);
    inp.set_quality(Quality::GOOD);
    power.set_input(&inp);
    power.set_power(2);
    power.calculate();
    EXPECT_FLOAT_EQ(power.get_value<float>(), 4.0f);
    EXPECT_EQ(power.get_quality(), Quality::GOOD);
    inp.set_value(3.0f);
    power.calculate();
    EXPECT_FLOAT_EQ(power.get_value<float>(), 9.0f);
    EXPECT_EQ(power.get_quality(), Quality::GOOD);
    power.set_power(3.0f);
    power.calculate();
    EXPECT_FLOAT_EQ(power.get_value<float>(), 27.0f);
    EXPECT_EQ(power.get_quality(), Quality::GOOD);
    inp.set_value(9.0f);
    power.set_power(0.5f);
    power.calculate();
    EXPECT_FLOAT_EQ(power.get_value<float>(), 3.0f);
    EXPECT_EQ(power.get_quality(), Quality::GOOD);
}

TEST(PowerPointTest, Double)
{
    auto inp = ExternalPoint<double>();
    auto power = PowerPoint<double>();
    inp.set_value(2.0);
    inp.set_quality(Quality::GOOD);
    power.set_input(&inp);
    power.set_power(2);
    power.calculate();
    EXPECT_DOUBLE_EQ(power.get_value<double>(), 4.0);
    EXPECT_EQ(power.get_quality(), Quality::GOOD);
    inp.set_value(3.0);
    power.calculate();
    EXPECT_DOUBLE_EQ(power.get_value<double>(), 9.0);
    EXPECT_EQ(power.get_quality(), Quality::GOOD);
    inp.set_value(2147483647.0);
    power.calculate();
    EXPECT_DOUBLE_EQ(power.get_value<double>(), 4611686014132420608.0);
    EXPECT_EQ(power.get_quality(), Quality::GOOD);
    inp.set_value(9.0);
    power.set_power(0.5);
    power.calculate();
    EXPECT_DOUBLE_EQ(power.get_value<float>(), 3);
    EXPECT_EQ(power.get_quality(), Quality::GOOD);
}
