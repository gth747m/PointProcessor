#include "pch.h"

using namespace point_processor;

TEST(EqualSelectPoint, Int32)
{
    double values[5] = { 0.0 };
    Quality qualities[5] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[5];
    auto inpA = ExternalPoint<int32_t>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<int32_t>(&values[1], &qualities[1], &durations[1]);
    auto outA = ExternalPoint<int32_t>(&values[2], &qualities[2], &durations[2]);
    auto outB = ExternalPoint<int32_t>(&values[3], &qualities[3], &durations[3]);
    auto point = EqualSelectPoint<int32_t>(&values[4], &qualities[4], &durations[4]);
    point.set_inputs(&inpA, &inpB);
    point.set_outputs(&outA, &outB);
    inpA.set_value(2);
    inpB.set_value(2);
    outA.set_value(2);
    outB.set_value(4);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    outA.set_quality(Quality::GOOD);
    outB.set_quality(Quality::GOOD);
    point.calculate();
    EXPECT_EQ(point.get_value<int32_t>(), 2);
    inpA.set_value(4);
    point.calculate();
    EXPECT_EQ(point.get_value<int32_t>(), 4);
    inpB.set_value(4);
    point.calculate();
    EXPECT_EQ(point.get_value<int32_t>(), 2);
}

TEST(EqualSelectPoint, Int64)
{
    double values[5] = { 0.0 };
    Quality qualities[5] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[5];
    auto inpA = ExternalPoint<int64_t>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<int64_t>(&values[1], &qualities[1], &durations[1]);
    auto outA = ExternalPoint<int64_t>(&values[2], &qualities[2], &durations[2]);
    auto outB = ExternalPoint<int64_t>(&values[3], &qualities[3], &durations[3]);
    auto point = EqualSelectPoint<int64_t>(&values[4], &qualities[4], &durations[4]);
    point.set_inputs(&inpA, &inpB);
    point.set_outputs(&outA, &outB);
    inpA.set_value(255);
    inpB.set_value(-200);
    outA.set_value(69);
    outB.set_value(420);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    outA.set_quality(Quality::GOOD);
    outB.set_quality(Quality::GOOD);
    point.calculate();
    EXPECT_EQ(point.get_value<int64_t>(), 420);
    inpA.set_value(-200);
    point.calculate();
    EXPECT_EQ(point.get_value<int64_t>(), 69);
    inpB.set_value(-420);
    point.calculate();
    EXPECT_EQ(point.get_value<int64_t>(), 420);
}

