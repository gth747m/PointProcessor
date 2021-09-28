#include "pch.h"

using namespace point_processor;

TEST(AveragePoint, Int32)
{
    double values[4] = { 0.0 };
    Quality qualities[4] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[4];
    auto inpA = ExternalPoint<int32_t>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<int32_t>(&values[1], &qualities[1], &durations[1]);
    auto inpC = ExternalPoint<int32_t>(&values[2], &qualities[2], &durations[2]);
    auto avg = AveragePoint<int32_t>(&values[3], &qualities[3], &durations[3]);
    avg.add_input(&inpA);
    avg.add_input(&inpB);
    avg.add_input(&inpC);
    inpA.set_value(2);
    inpB.set_value(4);
    inpC.set_value(3);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    inpC.set_quality(Quality::GOOD);
    avg.calculate();
    EXPECT_EQ(avg.get_value<int32_t>(), 3);
}

TEST(AveragePoint, Int64)
{
    double values[4] = { 0.0 };
    Quality qualities[4] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[4];
    auto inpA = ExternalPoint<int64_t>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<int64_t>(&values[1], &qualities[1], &durations[1]);
    auto inpC = ExternalPoint<int64_t>(&values[2], &qualities[2], &durations[2]);
    auto avg = AveragePoint<int64_t>(&values[3], &qualities[3], &durations[3]);
    avg.add_input(&inpA);
    avg.add_input(&inpB);
    avg.add_input(&inpC);
    inpA.set_value(25);
    inpB.set_value(45);
    inpC.set_value(20);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    inpC.set_quality(Quality::GOOD);
    avg.calculate();
    EXPECT_EQ(avg.get_value<int64_t>(), 30);
}

TEST(AveragePoint, Float)
{
    double values[4] = { 0.0 };
    Quality qualities[4] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[4];
    auto inpA = ExternalPoint<float>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<float>(&values[1], &qualities[1], &durations[1]);
    auto inpC = ExternalPoint<float>(&values[2], &qualities[2], &durations[2]);
    auto avg = AveragePoint<float>(&values[3], &qualities[3], &durations[3]);
    avg.add_input(&inpA);
    avg.add_input(&inpB);
    avg.add_input(&inpC);
    inpA.set_value(2.5f);
    inpB.set_value(9.5f);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    inpC.set_quality(Quality::GOOD);
    avg.calculate();
    EXPECT_FLOAT_EQ(avg.get_value<float>(), 4.0f);
}

TEST(AveragePoint, Double)
{
    double values[3] = { 0.0 };
    Quality qualities[3] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[3];
    auto inpA = ExternalPoint<double>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<double>(&values[1], &qualities[1], &durations[1]);
    auto avg = AveragePoint<double>(&values[2], &qualities[2], &durations[2]);
    avg.add_input(&inpA);
    avg.add_input(&inpB);
    inpA.set_value(25.25);
    inpB.set_value(45.25);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    avg.calculate();
    EXPECT_DOUBLE_EQ(avg.get_value<double>(), 35.25);
}
