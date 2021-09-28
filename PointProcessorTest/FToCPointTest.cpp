#include "pch.h"

using namespace point_processor;

TEST(FToCPoint, Float)
{
    double values[2] = { 0.0 };
    Quality qualities[2] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[2];
    auto inp = ExternalPoint<float>(&values[0], &qualities[0], &durations[0]);
    auto celsius = FToCPoint<float>(&values[1], &qualities[1], &durations[1]);
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

TEST(FToCPoint, Double)
{
    double values[2] = { 0.0 };
    Quality qualities[2] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[2];
    auto inp = ExternalPoint<double>(&values[0], &qualities[0], &durations[0]);
    auto celsius = FToCPoint<double>(&values[1], &qualities[1], &durations[1]);
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