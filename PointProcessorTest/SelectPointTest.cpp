#include "pch.h"

using namespace point_processor;

TEST(SelectPoint, UInt32)
{
    double values[5] = { 0.0 };
    Quality qualities[5] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[5];
    auto inpA = ExternalPoint<int32_t>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<int32_t>(&values[1], &qualities[1], &durations[1]);
    auto inpC = ExternalPoint<int32_t>(&values[2], &qualities[2], &durations[2]);
    auto indx = ExternalPoint<uint32_t>(&values[3], &qualities[3], &durations[3]);
    auto point = SelectPoint<int32_t>(&values[4], &qualities[4], &durations[4]);
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

TEST(SelectPoint, Int32)
{
    double values[5] = { 0.0 };
    Quality qualities[5] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[5];
    auto inpA = ExternalPoint<int32_t>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<int32_t>(&values[1], &qualities[1], &durations[1]);
    auto inpC = ExternalPoint<int32_t>(&values[2], &qualities[2], &durations[2]);
    auto indx = ExternalPoint<int32_t>(&values[3], &qualities[3], &durations[3]);
    auto point = SelectPoint<int32_t>(&values[4], &qualities[4], &durations[4]);
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

TEST(SelectPoint, Int64)
{
    double values[5] = { 0.0 };
    Quality qualities[5] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[5];
    auto inpA = ExternalPoint<int64_t>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<int64_t>(&values[1], &qualities[1], &durations[1]);
    auto inpC = ExternalPoint<int64_t>(&values[2], &qualities[2], &durations[2]);
    auto indx = ExternalPoint<uint64_t>(&values[3], &qualities[3], &durations[3]);
    auto point = SelectPoint<int64_t>(&values[4], &qualities[4], &durations[4]);
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

TEST(SelectPoint, Float)
{
    double values[5] = { 0.0 };
    Quality qualities[5] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[5];
    auto inpA = ExternalPoint<float>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<float>(&values[1], &qualities[1], &durations[1]);
    auto inpC = ExternalPoint<float>(&values[2], &qualities[2], &durations[2]);
    auto indx = ExternalPoint<uint32_t>(&values[3], &qualities[3], &durations[3]);
    auto point = SelectPoint<float>(&values[4], &qualities[4], &durations[4]);
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

TEST(SelectPoint, Double)
{
    double values[5] = { 0.0 };
    Quality qualities[5] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[5];
    auto inpA = ExternalPoint<double>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<double>(&values[1], &qualities[1], &durations[1]);
    auto inpC = ExternalPoint<double>(&values[2], &qualities[2], &durations[2]);
    auto indx = ExternalPoint<int64_t>(&values[3], &qualities[3], &durations[3]);
    auto point = SelectPoint<double>(&values[4], &qualities[4], &durations[4]);
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
