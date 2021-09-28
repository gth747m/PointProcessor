#include "pch.h"

using namespace point_processor;

TEST(GreaterThanEqualSelectPoint, Int32)
{
    double values[5] = { 0.0 };
    Quality qualities[5] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[5];
    auto inpA = ExternalPoint<int32_t>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<int32_t>(&values[1], &qualities[1], &durations[1]);
    auto outA = ExternalPoint<int32_t>(&values[2], &qualities[2], &durations[2]);
    auto outB = ExternalPoint<int32_t>(&values[3], &qualities[3], &durations[3]);
    auto point = GreaterThanEqualSelectPoint<int32_t>(&values[4], &qualities[4], &durations[4]);
    point.set_inputs(&inpA, &inpB);
    point.set_outputs(&outA, &outB);
    inpA.set_value(2);
    inpB.set_value(1);
    outA.set_value(2);
    outB.set_value(4);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    outA.set_quality(Quality::GOOD);
    outB.set_quality(Quality::GOOD);
    point.calculate();
    EXPECT_EQ(point.get_value<int32_t>(), 2);
    inpB.set_value(2);
    point.calculate();
    EXPECT_EQ(point.get_value<int32_t>(), 2);
    inpB.set_value(3);
    point.calculate();
    EXPECT_EQ(point.get_value<int32_t>(), 4);
}

TEST(GreaterThanEqualSelectPoint, Int64)
{
    double values[5] = { 0.0 };
    Quality qualities[5] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[5];
    auto inpA = ExternalPoint<int64_t>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<int64_t>(&values[1], &qualities[1], &durations[1]);
    auto outA = ExternalPoint<int64_t>(&values[2], &qualities[2], &durations[2]);
    auto outB = ExternalPoint<int64_t>(&values[3], &qualities[3], &durations[3]);
    auto point = GreaterThanEqualSelectPoint<int64_t>(&values[4], &qualities[4], &durations[4]);
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
    EXPECT_EQ(point.get_value<int64_t>(), 69);
    inpA.set_value(-256);
    point.calculate();
    EXPECT_EQ(point.get_value<int64_t>(), 420);
    inpB.set_value(-420);
    point.calculate();
    EXPECT_EQ(point.get_value<int64_t>(), 69);
}

TEST(GreaterThanEqualSelectPoint, Float)
{
    double values[5] = { 0.0 };
    Quality qualities[5] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[5];
    auto inpA = ExternalPoint<float>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<float>(&values[1], &qualities[1], &durations[1]);
    auto outA = ExternalPoint<float>(&values[2], &qualities[2], &durations[2]);
    auto outB = ExternalPoint<float>(&values[3], &qualities[3], &durations[3]);
    auto point = GreaterThanEqualSelectPoint<float>(&values[4], &qualities[4], &durations[4]);
    point.set_inputs(&inpA, &inpB);
    point.set_outputs(&outA, &outB);
    inpA.set_value(255.0f);
    inpB.set_value(-200.0f);
    outA.set_value(69.0f);
    outB.set_value(420.0f);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    outA.set_quality(Quality::GOOD);
    outB.set_quality(Quality::GOOD);
    point.calculate();
    EXPECT_EQ(point.get_value<float>(), 69.0f);
    inpA.set_value(-256.0f);
    point.calculate();
    EXPECT_EQ(point.get_value<float>(), 420.0f);
    inpB.set_value(-420.0f);
    point.calculate();
    EXPECT_EQ(point.get_value<float>(), 69.0f);
}

TEST(GreaterThanEqualSelectPoint, Double)
{
    double values[5] = { 0.0 };
    Quality qualities[5] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[5];
    auto inpA = ExternalPoint<double>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<double>(&values[1], &qualities[1], &durations[1]);
    auto outA = ExternalPoint<double>(&values[2], &qualities[2], &durations[2]);
    auto outB = ExternalPoint<double>(&values[3], &qualities[3], &durations[3]);
    auto point = GreaterThanEqualSelectPoint<double>(&values[4], &qualities[4], &durations[4]);
    point.set_inputs(&inpA, &inpB);
    point.set_outputs(&outA, &outB);
    inpA.set_value(255.0);
    inpB.set_value(255.4);
    outA.set_value(1.0);
    outB.set_value(999.0);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    outA.set_quality(Quality::GOOD);
    outB.set_quality(Quality::GOOD);
    point.calculate();
    EXPECT_EQ(point.get_value<double>(), 999.0);
    inpA.set_value(255.5);
    point.calculate();
    EXPECT_EQ(point.get_value<double>(), 1.0);
    inpB.set_value(255.5);
    point.calculate();
    EXPECT_EQ(point.get_value<double>(), 1.0);
}
