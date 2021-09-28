#include "pch.h"

using namespace point_processor;

TEST(SumPoint, Int32)
{
    double values[4] = { 0.0 };
    Quality qualities[4] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[4];
    auto inpA = ExternalPoint<int32_t>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<int32_t>(&values[1], &qualities[1], &durations[1]);
    auto inpC = ExternalPoint<int32_t>(&values[2], &qualities[2], &durations[2]);
    auto sum = SumPoint<int32_t>(&values[3], &qualities[3], &durations[3]);
    sum.add_input(&inpA);
    sum.add_input(&inpB);
    sum.add_input(&inpC);
    inpA.set_value(1);
    inpB.set_value(2);
    inpC.set_value(3);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    inpC.set_quality(Quality::GOOD);
    sum.calculate();
    EXPECT_EQ(sum.get_value<int32_t>(), 6);
    EXPECT_EQ(sum.get_quality(), Quality::GOOD);
    inpA.set_value(4);
    inpB.set_value(5);
    inpC.set_value(6);
    sum.calculate();
    EXPECT_EQ(sum.get_value<int32_t>(), 15);
    EXPECT_EQ(sum.get_quality(), Quality::GOOD);
}

TEST(SumPoint, Int64)
{
    double values[4] = { 0.0 };
    Quality qualities[4] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[4];
    auto inpA = ExternalPoint<int64_t>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<int64_t>(&values[1], &qualities[1], &durations[1]);
    auto inpC = ExternalPoint<int64_t>(&values[2], &qualities[2], &durations[2]);
    auto sum = SumPoint<int64_t>(&values[3], &qualities[3], &durations[3]);
    sum.add_input(&inpA);
    sum.add_input(&inpB);
    sum.add_input(&inpC);
    inpA.set_value(1);
    inpB.set_value(2);
    inpC.set_value(3);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    inpC.set_quality(Quality::GOOD);
    sum.calculate();
    EXPECT_EQ(sum.get_value<int64_t>(), 6);
    EXPECT_EQ(sum.get_quality(), Quality::GOOD);
    inpA.set_value(4);
    inpB.set_value(5);
    inpC.set_value(6);
    sum.calculate();
    EXPECT_EQ(sum.get_value<int64_t>(), 15);
    EXPECT_EQ(sum.get_quality(), Quality::GOOD);
}

TEST(SumPoint, Float)
{
    double values[4] = { 0.0 };
    Quality qualities[4] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[4];
    auto inpA = ExternalPoint<float>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<float>(&values[1], &qualities[1], &durations[1]);
    auto inpC = ExternalPoint<float>(&values[2], &qualities[2], &durations[2]);
    auto sum = SumPoint<float>(&values[3], &qualities[3], &durations[3]);
    sum.add_input(&inpA);
    sum.add_input(&inpB);
    sum.add_input(&inpC);
    inpA.set_value(1.5f);
    inpB.set_value(2.2f);
    inpC.set_value(3.3f);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    inpC.set_quality(Quality::GOOD);
    sum.calculate();
    EXPECT_FLOAT_EQ(sum.get_value<float>(), 7.0f);
    EXPECT_EQ(sum.get_quality(), Quality::GOOD);
    inpA.set_value(15.0f);
    inpB.set_value(35.2f);
    inpC.set_value(18.8f);
    sum.calculate();
    EXPECT_FLOAT_EQ(sum.get_value<float>(), 69.0f);
    EXPECT_EQ(sum.get_quality(), Quality::GOOD);
}

TEST(SumPoint, Double)
{
    double values[4] = { 0.0 };
    Quality qualities[4] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[4];
    auto inpA = ExternalPoint<double>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<double>(&values[1], &qualities[1], &durations[1]);
    auto inpC = ExternalPoint<double>(&values[2], &qualities[2], &durations[2]);
    auto sum = SumPoint<double>(&values[3], &qualities[3], &durations[3]);
    sum.add_input(&inpA);
    sum.add_input(&inpB);
    sum.add_input(&inpC);
    inpA.set_value(1.5);
    inpB.set_value(2.2);
    inpC.set_value(3.3);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    inpC.set_quality(Quality::GOOD);
    sum.calculate();
    EXPECT_DOUBLE_EQ(sum.get_value<double>(), 7.0);
    EXPECT_EQ(sum.get_quality(), Quality::GOOD);
    inpA.set_value(15);
    inpB.set_value(35.2);
    inpC.set_value(18.8);
    sum.calculate();
    EXPECT_DOUBLE_EQ(sum.get_value<double>(), 69.0);
    EXPECT_EQ(sum.get_quality(), Quality::GOOD);
}