#include "pch.h"

using namespace point_processor;

TEST(SubtractPoint, Int32)
{
    double values[4] = { 0.0 };
    Quality qualities[4] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[4];
    auto inpA = ExternalPoint<int32_t>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<int32_t>(&values[1], &qualities[1], &durations[1]);
    auto inpC = ExternalPoint<int32_t>(&values[2], &qualities[2], &durations[2]);
    auto subtract = SubtractPoint<int32_t>(&values[3], &qualities[3], &durations[3]);
    subtract.add_input(&inpA);
    subtract.add_input(&inpB);
    subtract.add_input(&inpC);
    inpA.set_value(1);
    inpB.set_value(2);
    inpC.set_value(3);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    inpC.set_quality(Quality::GOOD);
    subtract.calculate();
    EXPECT_EQ(subtract.get_value<int32_t>(), -4);
    EXPECT_EQ(subtract.get_quality(), Quality::GOOD);
    inpA.set_value(6);
    inpB.set_value(2);
    inpC.set_value(1);
    subtract.calculate();
    EXPECT_EQ(subtract.get_value<int32_t>(), 3);
    EXPECT_EQ(subtract.get_quality(), Quality::GOOD);
}

TEST(SubtractPoint, Int64)
{
    double values[4] = { 0.0 };
    Quality qualities[4] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[4];
    auto inpA = ExternalPoint<int64_t>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<int64_t>(&values[1], &qualities[1], &durations[1]);
    auto inpC = ExternalPoint<int64_t>(&values[2], &qualities[2], &durations[2]);
    auto subtract = SubtractPoint<int64_t>(&values[3], &qualities[3], &durations[3]);
    subtract.add_input(&inpA);
    subtract.add_input(&inpB);
    subtract.add_input(&inpC);
    inpA.set_value(1);
    inpB.set_value(2);
    inpC.set_value(3);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    inpC.set_quality(Quality::GOOD);
    subtract.calculate();
    EXPECT_EQ(subtract.get_value<int64_t>(), -4);
    EXPECT_EQ(subtract.get_quality(), Quality::GOOD);
    inpA.set_value(6);
    inpB.set_value(2);
    inpC.set_value(1);
    subtract.calculate();
    EXPECT_EQ(subtract.get_value<int64_t>(), 3);
    EXPECT_EQ(subtract.get_quality(), Quality::GOOD);
}

TEST(SubtractPoint, Float)
{
    double values[4] = { 0.0 };
    Quality qualities[4] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[4];
    auto inpA = ExternalPoint<float>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<float>(&values[1], &qualities[1], &durations[1]);
    auto inpC = ExternalPoint<float>(&values[2], &qualities[2], &durations[2]);
    auto subtract = SubtractPoint<float>(&values[3], &qualities[3], &durations[3]);
    subtract.add_input(&inpA);
    subtract.add_input(&inpB);
    subtract.add_input(&inpC);
    inpA.set_value(1.5f);
    inpB.set_value(2.2f);
    inpC.set_value(3.3f);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    inpC.set_quality(Quality::GOOD);
    subtract.calculate();
    EXPECT_FLOAT_EQ(subtract.get_value<float>(), -4.0f);
    EXPECT_EQ(subtract.get_quality(), Quality::GOOD);
    inpA.set_value(35.2f);
    inpB.set_value(15.0f);
    inpC.set_value(10.2f);
    subtract.calculate();
    EXPECT_FLOAT_EQ(subtract.get_value<float>(), 10.0f);
    EXPECT_EQ(subtract.get_quality(), Quality::GOOD);
}

TEST(SubtractPoint, Double)
{
    double values[4] = { 0.0 };
    Quality qualities[4] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[4];
    auto inpA = ExternalPoint<double>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<double>(&values[1], &qualities[1], &durations[1]);
    auto inpC = ExternalPoint<double>(&values[2], &qualities[2], &durations[2]);
    auto subtract = SubtractPoint<double>(&values[3], &qualities[3], &durations[3]);
    subtract.add_input(&inpA);
    subtract.add_input(&inpB);
    subtract.add_input(&inpC);
    inpA.set_value(1.5);
    inpB.set_value(2.2);
    inpC.set_value(3.3);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    inpC.set_quality(Quality::GOOD);
    subtract.calculate();
    EXPECT_DOUBLE_EQ(subtract.get_value<double>(), -4.0);
    EXPECT_EQ(subtract.get_quality(), Quality::GOOD);
    inpA.set_value(35.2);
    inpB.set_value(15);
    inpC.set_value(10.2);
    subtract.calculate();
    EXPECT_DOUBLE_EQ(subtract.get_value<double>(), 10.0);
    EXPECT_EQ(subtract.get_quality(), Quality::GOOD);
}
