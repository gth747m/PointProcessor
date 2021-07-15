#include "pch.h"

using namespace PointProcessor;

TEST(DigitalFilterPoint, DigitalFilterFloat)
{
    auto inp = ExternalPoint<float>();
    auto filter = DigitalFilterPoint<float>();
    filter.set_input(&inp);
    inp.set_value(1.0f);
    inp.set_quality(Quality::GOOD);
    filter.calculate();
    EXPECT_FLOAT_EQ(filter.get_value<float>(), 1.0f);
    EXPECT_EQ(filter.get_quality(), Quality::GOOD);
    inp.set_value(2.0f);
    filter.calculate();
    EXPECT_FLOAT_EQ(filter.get_value<float>(), 1.1f);
    EXPECT_EQ(filter.get_quality(), Quality::GOOD);
    filter.calculate();
    EXPECT_FLOAT_EQ(filter.get_value<float>(), 1.19f);
    EXPECT_EQ(filter.get_quality(), Quality::GOOD);
    filter.calculate();
    EXPECT_FLOAT_EQ(filter.get_value<float>(), 1.271f);
    EXPECT_EQ(filter.get_quality(), Quality::GOOD);
    filter.calculate();
    EXPECT_FLOAT_EQ(filter.get_value<float>(), 1.3439f);
    EXPECT_EQ(filter.get_quality(), Quality::GOOD);
    filter.calculate();
    EXPECT_FLOAT_EQ(filter.get_value<float>(), 1.40951f);
    EXPECT_EQ(filter.get_quality(), Quality::GOOD);
    filter.calculate();
    EXPECT_FLOAT_EQ(filter.get_value<float>(), 1.468559f);
    EXPECT_EQ(filter.get_quality(), Quality::GOOD);
    filter.set_filter_fraction(1.0);
    filter.calculate();
    EXPECT_FLOAT_EQ(filter.get_value<float>(), 2.0f);
    EXPECT_EQ(filter.get_quality(), Quality::GOOD);
}

TEST(DigitalFilterPoint, DigitalFilterDouble)
{
    auto inp = ExternalPoint<double>();
    auto filter = DigitalFilterPoint<double>();
    filter.set_input(&inp);
    inp.set_value(1.0);
    inp.set_quality(Quality::GOOD);
    filter.calculate();
    EXPECT_DOUBLE_EQ(filter.get_value<double>(), 1.0);
    EXPECT_EQ(filter.get_quality(), Quality::GOOD);
    inp.set_value(2.0);
    filter.calculate();
    EXPECT_DOUBLE_EQ(filter.get_value<double>(), 1.1);
    EXPECT_EQ(filter.get_quality(), Quality::GOOD);
    filter.calculate();
    EXPECT_DOUBLE_EQ(filter.get_value<double>(), 1.19);
    EXPECT_EQ(filter.get_quality(), Quality::GOOD);
    filter.calculate();
    EXPECT_DOUBLE_EQ(filter.get_value<double>(), 1.271);
    EXPECT_EQ(filter.get_quality(), Quality::GOOD);
    filter.calculate();
    EXPECT_DOUBLE_EQ(filter.get_value<double>(), 1.3439);
    EXPECT_EQ(filter.get_quality(), Quality::GOOD);
    filter.calculate();
    EXPECT_DOUBLE_EQ(filter.get_value<double>(), 1.40951);
    EXPECT_EQ(filter.get_quality(), Quality::GOOD);
    filter.calculate();
    EXPECT_DOUBLE_EQ(filter.get_value<double>(), 1.468559);
    EXPECT_EQ(filter.get_quality(), Quality::GOOD);
    filter.set_filter_fraction(1.0);
    filter.calculate();
    EXPECT_DOUBLE_EQ(filter.get_value<float>(), 2.0);
    EXPECT_EQ(filter.get_quality(), Quality::GOOD);
}