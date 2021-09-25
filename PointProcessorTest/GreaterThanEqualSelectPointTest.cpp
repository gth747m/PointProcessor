#include "pch.h"

using namespace PointProcessor;

TEST(GreaterThanEqualSelectPoint, Int32)
{
    auto inpA = ExternalPoint<int32_t>();
    auto inpB = ExternalPoint<int32_t>();
    auto outA = ExternalPoint<int32_t>();
    auto outB = ExternalPoint<int32_t>();
    auto point = GreaterThanEqualSelectPoint<int32_t>();
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
    auto inpA = ExternalPoint<int64_t>();
    auto inpB = ExternalPoint<int64_t>();
    auto outA = ExternalPoint<int64_t>();
    auto outB = ExternalPoint<int64_t>();
    auto point = GreaterThanEqualSelectPoint<int64_t>();
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
    auto inpA = ExternalPoint<float>();
    auto inpB = ExternalPoint<float>();
    auto outA = ExternalPoint<float>();
    auto outB = ExternalPoint<float>();
    auto point = GreaterThanEqualSelectPoint<float>();
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
    auto inpA = ExternalPoint<double>();
    auto inpB = ExternalPoint<double>();
    auto outA = ExternalPoint<double>();
    auto outB = ExternalPoint<double>();
    auto point = GreaterThanEqualSelectPoint<double>();
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
