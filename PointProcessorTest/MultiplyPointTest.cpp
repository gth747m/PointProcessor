#include "pch.h"

using namespace point_processor;

TEST(MultiplyPoint, Int32)
{
    double values[3] = { 0.0 };
    Quality qualities[3] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[3];
    auto inpA = ExternalPoint<int32_t>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<int32_t>(&values[1], &qualities[1], &durations[1]);
    auto div = MultiplyPoint<int32_t>(&values[2], &qualities[2], &durations[2]);
    inpA.set_value(4);
    inpB.set_value(4);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    div.add_input(&inpA);
    div.add_input(&inpB);
    div.calculate();
    EXPECT_EQ(div.get_value<int32_t>(), 16);
    EXPECT_EQ(div.get_quality(), Quality::GOOD);
    inpB.set_value(2);
    div.calculate();
    EXPECT_EQ(div.get_value<int32_t>(), 8);
    EXPECT_EQ(div.get_quality(), Quality::GOOD);
}

TEST(MultiplyPoint, Int64)
{
    double values[3] = { 0.0 };
    Quality qualities[3] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[3];
    auto inpA = ExternalPoint<int64_t>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<int64_t>(&values[1], &qualities[1], &durations[1]);
    auto div = MultiplyPoint<int64_t>(&values[2], &qualities[2], &durations[2]);
    inpA.set_value(4);
    inpB.set_value(4);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    div.add_input(&inpA);
    div.add_input(&inpB);
    div.calculate();
    EXPECT_EQ(div.get_value<int64_t>(), 16);
    EXPECT_EQ(div.get_quality(), Quality::GOOD);
    inpB.set_value(2);
    div.calculate();
    EXPECT_EQ(div.get_value<int64_t>(), 8);
    EXPECT_EQ(div.get_quality(), Quality::GOOD);
}

TEST(MultiplyPoint, Float)
{
    double values[3] = { 0.0 };
    Quality qualities[3] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[3];
    auto inpA = ExternalPoint<float>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<float>(&values[1], &qualities[1], &durations[1]);
    auto div = MultiplyPoint<float>(&values[2], &qualities[2], &durations[2]);
    inpA.set_value(4.0f);
    inpB.set_value(4.0f);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    div.add_input(&inpA);
    div.add_input(&inpB);
    div.calculate();
    EXPECT_EQ(div.get_value<float>(), 16.0f);
    EXPECT_EQ(div.get_quality(), Quality::GOOD);
    inpA.set_value(2.0f);
    div.calculate();
    EXPECT_EQ(div.get_value<float>(), 8.0f);
    EXPECT_EQ(div.get_quality(), Quality::GOOD);
}

TEST(MultiplyPoint, Double)
{
    double values[3] = { 0.0 };
    Quality qualities[3] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[3];
    auto inpA = ExternalPoint<double>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<double>(&values[1], &qualities[1], &durations[1]);
    auto div = MultiplyPoint<double>(&values[2], &qualities[2], &durations[2]);
    inpA.set_value(4.0);
    inpB.set_value(4.0);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    div.add_input(&inpA);
    div.add_input(&inpB);
    div.calculate();
    EXPECT_EQ(div.get_value<double>(), 16.0);
    EXPECT_EQ(div.get_quality(), Quality::GOOD);
    inpA.set_value(2);
    div.calculate();
    EXPECT_EQ(div.get_value<double>(), 8.0);
    EXPECT_EQ(div.get_quality(), Quality::GOOD);
}