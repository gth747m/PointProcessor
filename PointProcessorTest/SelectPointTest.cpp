#include "pch.h"

using namespace PointProcessor;

TEST(SelectPoint, SelectInt32)
{
    auto selector = ExternalPoint<uint32_t>();
    auto inpA = ExternalPoint<int32_t>();
    auto inpB = ExternalPoint<int32_t>();
    auto inpC = ExternalPoint<int32_t>();
    auto slct = SelectPoint<int32_t>();
    slct.add_input(&inpA);
    slct.add_input(&inpB);
    slct.add_input(&inpC);
    slct.set_select_point(&selector);
    inpA.set_value(4);
    inpB.set_value(5);
    inpC.set_value(6);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    inpC.set_quality(Quality::GOOD);
    selector.set_value(2);
    selector.set_quality(Quality::GOOD);
    slct.calculate();
    ASSERT_EQ(slct.get_value(), 6);
    selector.set_value(1);
    slct.calculate();
    ASSERT_EQ(slct.get_value(), 5);
    selector.set_value(0);
    slct.calculate();
    ASSERT_EQ(slct.get_value(), 4);
}

TEST(SelectPoint, SelectInt64)
{
    auto selector = ExternalPoint<int32_t>();
    auto inpA = ExternalPoint<int64_t>();
    auto inpB = ExternalPoint<int64_t>();
    auto inpC = ExternalPoint<int64_t>();
    auto slct = SelectPoint<int64_t, int64_t, int32_t>();
    slct.add_input(&inpA);
    slct.add_input(&inpB);
    slct.add_input(&inpC);
    slct.set_select_point(&selector);
    inpA.set_value(8);
    inpB.set_value(16);
    inpC.set_value(32);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    inpC.set_quality(Quality::GOOD);
    selector.set_value(1);
    selector.set_quality(Quality::GOOD);
    slct.calculate();
    ASSERT_EQ(slct.get_value(), 16);
    selector.set_value(0);
    slct.calculate();
    ASSERT_EQ(slct.get_value(), 8);
    selector.set_value(2);
    slct.calculate();
    ASSERT_EQ(slct.get_value(), 32);
}

TEST(SelectPoint, SelectFloat)
{
    auto selector = ExternalPoint<uint32_t>();
    auto inpA = ExternalPoint<float>();
    auto inpB = ExternalPoint<float>();
    auto inpC = ExternalPoint<float>();
    auto slct = SelectPoint<float>();
    slct.add_input(&inpA);
    slct.add_input(&inpB);
    slct.add_input(&inpC);
    slct.set_select_point(&selector);
    inpA.set_value(4.0f);
    inpB.set_value(5.0f);
    inpC.set_value(6.0f);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    inpC.set_quality(Quality::GOOD);
    selector.set_value(2);
    selector.set_quality(Quality::GOOD);
    slct.calculate();
    EXPECT_FLOAT_EQ(slct.get_value(), 6.0f);
    selector.set_value(1);
    slct.calculate();
    EXPECT_FLOAT_EQ(slct.get_value(), 5.0f);
    selector.set_value(0);
    slct.calculate();
    EXPECT_FLOAT_EQ(slct.get_value(), 4.0f);
}

TEST(SelectPoint, SelectDouble)
{
    auto selector = ExternalPoint<char>();
    auto inpA = ExternalPoint<double>();
    auto inpB = ExternalPoint<double>();
    auto inpC = ExternalPoint<double>();
    auto slct = SelectPoint<double, double, char>();
    slct.add_input(&inpA);
    slct.add_input(&inpB);
    slct.add_input(&inpC);
    slct.set_select_point(&selector);
    inpA.set_value(8.0);
    inpB.set_value(16.0);
    inpC.set_value(32.0);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    inpC.set_quality(Quality::GOOD);
    selector.set_value(1);
    selector.set_quality(Quality::GOOD);
    slct.calculate();
    EXPECT_DOUBLE_EQ(slct.get_value(), 16.0);
    selector.set_value(0);
    slct.calculate();
    EXPECT_DOUBLE_EQ(slct.get_value(), 8.0);
    selector.set_value(2);
    slct.calculate();
    EXPECT_DOUBLE_EQ(slct.get_value(), 32.0);
}

