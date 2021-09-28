#include "pch.h"

using namespace point_processor;

TEST(DividePoint, Int32)
{
    double values[5] = { 0.0 };
    Quality qualities[5] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[5];
    auto inpA = ExternalPoint<int32_t>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<int32_t>(&values[1], &qualities[1], &durations[1]);
    auto div = DividePoint<int32_t>(&values[2], &qualities[2], &durations[2]);
    inpA.set_value(4);
    inpB.set_value(4);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    div.add_input(&inpA);
    div.add_input(&inpB);
    div.calculate();
    EXPECT_EQ(div.get_value<int32_t>(), 1);
    EXPECT_EQ(div.get_quality(), Quality::GOOD);
    inpB.set_value(2);
    div.calculate();
    EXPECT_EQ(div.get_value<int32_t>(), 2);
    EXPECT_EQ(div.get_quality(), Quality::GOOD);
    inpB.set_value(0);
    div.calculate();
    EXPECT_EQ(div.get_quality(), Quality::NOT_CALCULABLE);
}

TEST(DividePoint, Int64)
{
    double values[5] = { 0.0 };
    Quality qualities[5] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[5];
    auto inpA = ExternalPoint<int64_t>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<int64_t>(&values[1], &qualities[1], &durations[1]);
    auto div = DividePoint<int64_t>(&values[2], &qualities[2], &durations[2]);
    inpA.set_value(4);
    inpB.set_value(4);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    div.add_input(&inpA);
    div.add_input(&inpB);
    div.calculate();
    EXPECT_EQ(div.get_value<int64_t>(), 1);
    EXPECT_EQ(div.get_quality(), Quality::GOOD);
    inpB.set_value(2);
    div.calculate();
    EXPECT_EQ(div.get_value<int64_t>(), 2);
    EXPECT_EQ(div.get_quality(), Quality::GOOD);
    inpB.set_value(0);
    div.calculate();
    EXPECT_EQ(div.get_quality(), Quality::NOT_CALCULABLE);
}

TEST(DividePoint, Float)
{
    double values[5] = { 0.0 };
    Quality qualities[5] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[5];
    auto inpA = ExternalPoint<float>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<float>(&values[1], &qualities[1], &durations[1]);
    auto div = DividePoint<float>(&values[2], &qualities[2], &durations[2]);
    inpA.set_value(4.0f);
    inpB.set_value(4.0f);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    div.add_input(&inpA);
    div.add_input(&inpB);
    div.calculate();
    EXPECT_EQ(div.get_value<float>(), 1.0f);
    EXPECT_EQ(div.get_quality(), Quality::GOOD);
    inpA.set_value(2.0f);
    div.calculate();
    EXPECT_EQ(div.get_value<float>(), 0.5f);
    EXPECT_EQ(div.get_quality(), Quality::GOOD);
    inpB.set_value(0.0f);
    div.calculate();
    EXPECT_EQ(div.get_quality(), Quality::NOT_CALCULABLE);
}

TEST(DividePoint, Double)
{
    double values[5] = { 0.0 };
    Quality qualities[5] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[5];
    auto inpA = ExternalPoint<double>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<double>(&values[1], &qualities[1], &durations[1]);
    auto div = DividePoint<double>(&values[2], &qualities[2], &durations[2]);
    inpA.set_value(4.0);
    inpB.set_value(4.0);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    div.add_input(&inpA);
    div.add_input(&inpB);
    div.calculate();
    EXPECT_EQ(div.get_value<double>(), 1.0);
    EXPECT_EQ(div.get_quality(), Quality::GOOD);
    inpA.set_value(2);
    div.calculate();
    EXPECT_EQ(div.get_value<double>(), 0.5);
    EXPECT_EQ(div.get_quality(), Quality::GOOD);
    inpB.set_value(0.0);
    div.calculate();
    EXPECT_EQ(div.get_quality(), Quality::NOT_CALCULABLE);
}