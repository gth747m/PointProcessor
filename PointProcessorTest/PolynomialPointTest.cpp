#include "pch.h"

using namespace PointProcessor;

TEST(PolynomialPoint, Int32)
{
    auto coeffA = ExternalPoint<int32_t>();
    auto varA = ExternalPoint<int32_t>();
    auto coeffB = ExternalPoint<int32_t>();
    auto varB = ExternalPoint<int32_t>();
    auto poly = PolynomialPoint<int32_t>();
    poly.add_input(&coeffA, &varA);
    poly.add_input(&coeffB, &varB);
    coeffA.set_value(-2);
    varA.set_value(2);
    coeffB.set_value(4);
    varB.set_value(3);
    coeffA.set_quality(Quality::GOOD);
    varA.set_quality(Quality::GOOD);
    coeffB.set_quality(Quality::GOOD);
    varB.set_quality(Quality::GOOD);
    poly.calculate();
    // should be  4(3^1) + (-2)
    EXPECT_EQ(poly.get_value<int32_t>(), 10);
    EXPECT_EQ(poly.get_quality(), Quality::GOOD);
    auto coeffC = ExternalPoint<int32_t>();
    auto varC = ExternalPoint<int32_t>();
    poly.add_input(&coeffC, &varC);
    coeffA.set_value(9999);
    varA.set_value(0);
    coeffB.set_value(3);
    varB.set_value(4);
    coeffC.set_value(5);
    varC.set_value(9);
    coeffC.set_quality(Quality::GOOD);
    varC.set_quality(Quality::GOOD);
    poly.calculate();
    // should be  5(9^2) + 3(4^1) + (9999)
    EXPECT_EQ(poly.get_value<int32_t>(), 10416);
    EXPECT_EQ(poly.get_quality(), Quality::GOOD);
    auto coeffD = ExternalPoint<int32_t>();
    auto varD = ExternalPoint<int32_t>();
    poly.add_input(&coeffD, &varD);
    coeffD.set_value(-1);
    varD.set_value(22);
    coeffD.set_quality(Quality::GOOD);
    varD.set_quality(Quality::GOOD);
    poly.calculate();
    // should be  -1(22^3) + 5(9^2) + 3(4^1) + (9999)
    EXPECT_EQ(poly.get_value<int32_t>(), -232);
    EXPECT_EQ(poly.get_quality(), Quality::GOOD);
}

TEST(PolynomialPoint, Int64)
{
    auto coeffA = ExternalPoint<int64_t>();
    auto varA = ExternalPoint<int64_t>();
    auto coeffB = ExternalPoint<int64_t>();
    auto varB = ExternalPoint<int64_t>();
    auto poly = PolynomialPoint<int64_t>();
    auto coeffC = ExternalPoint<int64_t>();
    auto varC = ExternalPoint<int64_t>();
    auto coeffD = ExternalPoint<int64_t>();
    auto varD = ExternalPoint<int64_t>();
    poly.add_input(&coeffA, &varA);
    poly.add_input(&coeffB, &varB);
    poly.add_input(&coeffC, &varC);
    poly.add_input(&coeffD, &varD);
    coeffA.set_value(-644);
    varA.set_value(999);
    coeffB.set_value(9);
    varB.set_value(8);
    coeffC.set_value(7);
    varC.set_value(6);
    coeffD.set_value(5);
    varD.set_value(4);
    coeffA.set_quality(Quality::GOOD);
    varA.set_quality(Quality::GOOD);
    coeffB.set_quality(Quality::GOOD);
    varB.set_quality(Quality::GOOD);
    coeffC.set_quality(Quality::GOOD);
    varC.set_quality(Quality::GOOD);
    coeffD.set_quality(Quality::GOOD);
    varD.set_quality(Quality::GOOD);
    poly.calculate();
    // should be  5(4^3) + 7(6^2) + 9(8^1) - 644
    EXPECT_EQ(poly.get_value<int64_t>(), 0);
    EXPECT_EQ(poly.get_quality(), Quality::GOOD);
}

TEST(PolynomialPoint, Float)
{
    auto coeffA = ExternalPoint<float>();
    auto varA = ExternalPoint<float>();
    auto coeffB = ExternalPoint<float>();
    auto varB = ExternalPoint<float>();
    auto poly = PolynomialPoint<float>();
    poly.add_input(&coeffA, &varA);
    poly.add_input(&coeffB, &varB);
    coeffA.set_value(-2);
    varA.set_value(2);
    coeffB.set_value(4);
    varB.set_value(3);
    coeffA.set_quality(Quality::GOOD);
    varA.set_quality(Quality::GOOD);
    coeffB.set_quality(Quality::GOOD);
    varB.set_quality(Quality::GOOD);
    poly.calculate();
    // should be  4(3^1) + (-2)
    EXPECT_FLOAT_EQ(poly.get_value<float>(), 10.0f);
    EXPECT_EQ(poly.get_quality(), Quality::GOOD);
    auto coeffC = ExternalPoint<float>();
    auto varC = ExternalPoint<float>();
    poly.add_input(&coeffC, &varC);
    coeffA.set_value(9999.0f);
    varA.set_value(0.0f);
    coeffB.set_value(3.0f);
    varB.set_value(4.0f);
    coeffC.set_value(5.0f);
    varC.set_value(9.0f);
    coeffC.set_quality(Quality::GOOD);
    varC.set_quality(Quality::GOOD);
    poly.calculate();
    // should be  5(9^2) + 3(4^1) + (9999)
    EXPECT_FLOAT_EQ(poly.get_value<float>(), 10416.0f);
    EXPECT_EQ(poly.get_quality(), Quality::GOOD);
    auto coeffD = ExternalPoint<float>();
    auto varD = ExternalPoint<float>();
    poly.add_input(&coeffD, &varD);
    coeffD.set_value(-1.0f);
    varD.set_value(22.0f);
    coeffD.set_quality(Quality::GOOD);
    varD.set_quality(Quality::GOOD);
    poly.calculate();
    // should be  -1(22^3) + 5(9^2) + 3(4^1) + (9999)
    EXPECT_FLOAT_EQ(poly.get_value<float>(), -232.0f);
    EXPECT_EQ(poly.get_quality(), Quality::GOOD);
}

TEST(PolynomialPoint, Double)
{
    auto coeffA = ExternalPoint<double>();
    auto varA = ExternalPoint<double>();
    auto coeffB = ExternalPoint<double>();
    auto varB = ExternalPoint<double>();
    auto poly = PolynomialPoint<double>();
    auto coeffC = ExternalPoint<double>();
    auto varC = ExternalPoint<double>();
    auto coeffD = ExternalPoint<double>();
    auto varD = ExternalPoint<double>();
    poly.add_input(&coeffA, &varA);
    poly.add_input(&coeffB, &varB);
    poly.add_input(&coeffC, &varC);
    poly.add_input(&coeffD, &varD);
    coeffA.set_value(-644.0);
    varA.set_value(999.0);
    coeffB.set_value(9.0);
    varB.set_value(8.0);
    coeffC.set_value(7.0);
    varC.set_value(6.0);
    coeffD.set_value(5.0);
    varD.set_value(4.0);
    coeffA.set_quality(Quality::GOOD);
    varA.set_quality(Quality::GOOD);
    coeffB.set_quality(Quality::GOOD);
    varB.set_quality(Quality::GOOD);
    coeffC.set_quality(Quality::GOOD);
    varC.set_quality(Quality::GOOD);
    coeffD.set_quality(Quality::GOOD);
    varD.set_quality(Quality::GOOD);
    poly.calculate();
    // should be  5(4^3) + 7(6^2) + 9(8^1) - 644
    EXPECT_DOUBLE_EQ(poly.get_value<double>(), 0.0);
    EXPECT_EQ(poly.get_quality(), Quality::GOOD);
}