#include "pch.h"

using namespace point_processor;

TEST(CToFPoint, Float)
{
    double values[2] = { 0.0 };
    Quality qualities[2] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[2];
    auto inp = ExternalPoint<float>(&values[0], &qualities[0], &durations[0]);
    auto farenheit = CToFPoint<float>(&values[1], &qualities[1], &durations[1]);
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
    double values[2] = { 0.0 };
    Quality qualities[2] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[2];
    auto inp = ExternalPoint<double>(&values[0], &qualities[0], &durations[0]);
    auto farenheit = CToFPoint<double>(&values[1], &qualities[1], &durations[1]);
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
