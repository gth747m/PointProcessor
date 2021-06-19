#include "pch.h"

using namespace PointProcessor;

TEST(SubtractPoint, SubtractInt32)
{
    auto inpA = ExternalPoint<int32_t>();
    auto inpB = ExternalPoint<int32_t>();
    auto inpC = ExternalPoint<int32_t>();
    auto subtract = SubtractPoint<int32_t>();
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
    ASSERT_EQ(subtract.get_value(), -4);
    inpA.set_value(6);
    inpB.set_value(2);
    inpC.set_value(1);
    subtract.calculate();
    ASSERT_EQ(subtract.get_value(), 3);
}

TEST(SubtractPoint, SubtractInt64)
{
    auto inpA = ExternalPoint<int64_t>();
    auto inpB = ExternalPoint<int64_t>();
    auto inpC = ExternalPoint<int64_t>();
    auto subtract = SubtractPoint<int64_t>();
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
    ASSERT_EQ(subtract.get_value(), -4);
    inpA.set_value(6);
    inpB.set_value(2);
    inpC.set_value(1);
    subtract.calculate();
    ASSERT_EQ(subtract.get_value(), 3);
}

TEST(SubtractPoint, SubtractFloat)
{
    auto inpA = ExternalPoint<float>();
    auto inpB = ExternalPoint<float>();
    auto inpC = ExternalPoint<float>();
    auto subtract = SubtractPoint<float>();
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
    EXPECT_FLOAT_EQ(subtract.get_value(), -4.0f);
    inpA.set_value(35.2f);
    inpB.set_value(15.0f);
    inpC.set_value(10.2f);
    subtract.calculate();
    EXPECT_FLOAT_EQ(subtract.get_value(), 10.0f);
}

TEST(SubtractPoint, SubtractDouble)
{
    auto inpA = ExternalPoint<double>();
    auto inpB = ExternalPoint<double>();
    auto inpC = ExternalPoint<double>();
    auto subtract = SubtractPoint<double>();
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
    EXPECT_DOUBLE_EQ(subtract.get_value(), -4.0);
    inpA.set_value(35.2);
    inpB.set_value(15);
    inpC.set_value(10.2);
    subtract.calculate();
    EXPECT_DOUBLE_EQ(subtract.get_value(), 10.0);
}
