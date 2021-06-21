#include "pch.h"

using namespace PointProcessor;

TEST(SelectPoint, SelectUInt32)
{
    auto inpA = ExternalPoint<int32_t>();
    auto inpB = ExternalPoint<int32_t>();
    auto inpC = ExternalPoint<int32_t>();
    auto indx = ExternalPoint<uint32_t>();
    auto point = SelectPoint<int32_t>();
    point.add_input(&inpA);
    point.add_input(&inpB);
    point.add_input(&inpC);
    point.set_index_point(&indx);
    inpA.set_value(2);
    inpB.set_value(4);
    inpC.set_value(6);
    indx.set_value(1);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    inpC.set_quality(Quality::GOOD);
    indx.set_quality(Quality::GOOD);
    point.calculate();
    EXPECT_EQ(point.get_value<int32_t>(), 2);
    EXPECT_EQ(point.get_quality(), Quality::GOOD);
    indx.set_value(2);
    point.calculate();
    EXPECT_EQ(point.get_value<int32_t>(), 4);
    EXPECT_EQ(point.get_quality(), Quality::GOOD);
    indx.set_value(3);
    point.calculate();
    EXPECT_EQ(point.get_value<int32_t>(), 6);
    EXPECT_EQ(point.get_quality(), Quality::GOOD);
    indx.set_value(0);
    point.calculate();
    EXPECT_EQ(point.get_quality(), Quality::NOT_CALCULABLE);
    indx.set_value(1);
    indx.set_quality(Quality::DELETED);
    point.calculate();
    EXPECT_EQ(point.get_quality(), Quality::NOT_CALCULABLE);
}

TEST(SelectPoint, SelectInt32)
{
    auto inpA = ExternalPoint<int32_t>();
    auto inpB = ExternalPoint<int32_t>();
    auto inpC = ExternalPoint<int32_t>();
    auto indx = ExternalPoint<int32_t>();
    auto point = SelectPoint<int32_t>();
    point.add_input(&inpA);
    point.add_input(&inpB);
    point.add_input(&inpC);
    point.set_index_point(&indx);
    inpA.set_value(2);
    inpB.set_value(4);
    inpC.set_value(6);
    indx.set_value(1);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    inpC.set_quality(Quality::GOOD);
    indx.set_quality(Quality::GOOD);
    point.calculate();
    EXPECT_EQ(point.get_value<int32_t>(), 2);
    EXPECT_EQ(point.get_quality(), Quality::GOOD);
    indx.set_value(2);
    point.calculate();
    EXPECT_EQ(point.get_value<int32_t>(), 4);
    EXPECT_EQ(point.get_quality(), Quality::GOOD);
    indx.set_value(3);
    point.calculate();
    EXPECT_EQ(point.get_value<int32_t>(), 6);
    EXPECT_EQ(point.get_quality(), Quality::GOOD);
    indx.set_value(0);
    point.calculate();
    EXPECT_EQ(point.get_quality(), Quality::NOT_CALCULABLE);
    indx.set_value(1);
    indx.set_quality(Quality::DELETED);
    point.calculate();
    EXPECT_EQ(point.get_quality(), Quality::NOT_CALCULABLE);
}

TEST(SelectPoint, SelectInt64)
{
    auto inpA = ExternalPoint<int64_t>();
    auto inpB = ExternalPoint<int64_t>();
    auto inpC = ExternalPoint<int64_t>();
    auto indx = ExternalPoint<uint64_t>();
    auto point = SelectPoint<int64_t>();
    point.add_input(&inpA);
    point.add_input(&inpB);
    point.add_input(&inpC);
    point.set_index_point(&indx);
    inpA.set_value(2);
    inpB.set_value(4);
    inpC.set_value(6);
    indx.set_value(1);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    inpC.set_quality(Quality::GOOD);
    indx.set_quality(Quality::GOOD);
    point.calculate();
    EXPECT_EQ(point.get_value<int64_t>(), 2);
    EXPECT_EQ(point.get_quality(), Quality::GOOD);
    indx.set_value(2);
    point.calculate();
    EXPECT_EQ(point.get_value<int64_t>(), 4);
    EXPECT_EQ(point.get_quality(), Quality::GOOD);
    indx.set_value(3);
    point.calculate();
    EXPECT_EQ(point.get_value<int64_t>(), 6);
    EXPECT_EQ(point.get_quality(), Quality::GOOD);
    indx.set_value(0);
    point.calculate();
    EXPECT_EQ(point.get_quality(), Quality::NOT_CALCULABLE);
    indx.set_value(1);
    indx.set_quality(Quality::DELETED);
    point.calculate();
    EXPECT_EQ(point.get_quality(), Quality::NOT_CALCULABLE);
}

TEST(SelectPoint, SelectFloat)
{
    auto inpA = ExternalPoint<float>();
    auto inpB = ExternalPoint<float>();
    auto inpC = ExternalPoint<float>();
    auto indx = ExternalPoint<uint32_t>();
    auto point = SelectPoint<float>();
    point.add_input(&inpA);
    point.add_input(&inpB);
    point.add_input(&inpC);
    point.set_index_point(&indx);
    inpA.set_value(2.5f);
    inpB.set_value(4.2f);
    inpC.set_value(6.7f);
    indx.set_value(1);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    inpC.set_quality(Quality::GOOD);
    indx.set_quality(Quality::GOOD);
    point.calculate();
    EXPECT_FLOAT_EQ(point.get_value<float>(), 2.5f);
    EXPECT_EQ(point.get_quality(), Quality::GOOD);
    indx.set_value(2);
    point.calculate();
    EXPECT_FLOAT_EQ(point.get_value<float>(), 4.2f);
    EXPECT_EQ(point.get_quality(), Quality::GOOD);
    indx.set_value(3);
    point.calculate();
    EXPECT_FLOAT_EQ(point.get_value<float>(), 6.7f);
    EXPECT_EQ(point.get_quality(), Quality::GOOD);
    indx.set_value(0);
    point.calculate();
    EXPECT_EQ(point.get_quality(), Quality::NOT_CALCULABLE);
    indx.set_value(1);
    indx.set_quality(Quality::DELETED);
    point.calculate();
    EXPECT_EQ(point.get_quality(), Quality::NOT_CALCULABLE);
}

TEST(SelectPoint, SelectDouble)
{
    auto inpA = ExternalPoint<double>();
    auto inpB = ExternalPoint<double>();
    auto inpC = ExternalPoint<double>();
    auto indx = ExternalPoint<int64_t>();
    auto point = SelectPoint<double>();
    point.add_input(&inpA);
    point.add_input(&inpB);
    point.add_input(&inpC);
    point.set_index_point(&indx);
    inpA.set_value(2.5);
    inpB.set_value(4.2);
    inpC.set_value(6.7);
    indx.set_value(1);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    inpC.set_quality(Quality::GOOD);
    indx.set_quality(Quality::GOOD);
    point.calculate();
    EXPECT_DOUBLE_EQ(point.get_value<double>(), 2.5);
    EXPECT_EQ(point.get_quality(), Quality::GOOD);
    indx.set_value(2);
    point.calculate();
    EXPECT_DOUBLE_EQ(point.get_value<double>(), 4.2);
    EXPECT_EQ(point.get_quality(), Quality::GOOD);
    indx.set_value(3);
    point.calculate();
    EXPECT_DOUBLE_EQ(point.get_value<double>(), 6.7);
    EXPECT_EQ(point.get_quality(), Quality::GOOD);
    indx.set_value(0);
    point.calculate();
    EXPECT_EQ(point.get_quality(), Quality::NOT_CALCULABLE);
    indx.set_value(1);
    indx.set_quality(Quality::DELETED);
    point.calculate();
    EXPECT_EQ(point.get_quality(), Quality::NOT_CALCULABLE);
}
