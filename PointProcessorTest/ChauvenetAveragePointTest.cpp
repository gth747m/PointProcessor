#include "pch.h"

using namespace point_processor;

TEST(ChauvenetAveragePoint, Int32)
{
    double values[5] = { 0.0 };
    Quality qualities[5] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[5];
    auto inpA = ExternalPoint<int32_t>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<int32_t>(&values[1], &qualities[1], &durations[1]);
    auto inpC = ExternalPoint<int32_t>(&values[2], &qualities[2], &durations[2]);
    auto num = ExternalPoint<int32_t>(&values[3], &qualities[3], &durations[3]);
    auto avg = ChauvenetAveragePoint<int32_t>(&values[4], &qualities[4], &durations[4]);
    avg.add_input(&inpA);
    avg.add_input(&inpB);
    avg.add_input(&inpC);
    avg.set_min_good_points(&num);
    inpA.set_value(1);
    inpB.set_value(2);
    inpC.set_value(3);
    num.set_value(3);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    inpC.set_quality(Quality::GOOD);
    num.set_quality(Quality::GOOD);
    avg.calculate();
    EXPECT_EQ(avg.get_value<int32_t>(), 2);
    EXPECT_EQ(avg.get_quality(), Quality::GOOD);
}

TEST(ChauvenetAveragePoint, Int64)
{
    double values[6] = { 0.0 };
    Quality qualities[6] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[6];
    auto inpA = ExternalPoint<int64_t>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<int64_t>(&values[1], &qualities[1], &durations[1]);
    auto inpC = ExternalPoint<int64_t>(&values[2], &qualities[2], &durations[2]);
    auto inpD = ExternalPoint<int64_t>(&values[3], &qualities[3], &durations[3]);
    auto num = ExternalPoint<int32_t>(&values[4], &qualities[4], &durations[4]);
    auto avg = ChauvenetAveragePoint<int64_t>(&values[5], &qualities[5], &durations[5]);
    avg.add_input(&inpA);
    avg.add_input(&inpB);
    avg.add_input(&inpC);
    avg.add_input(&inpD);
    avg.set_min_good_points(&num);
    inpA.set_value(25);
    inpB.set_value(25);
    inpC.set_value(25);
    inpD.set_value(25);
    num.set_value(3);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    inpC.set_quality(Quality::NOT_CALCULABLE);
    inpD.set_quality(Quality::GOOD);
    num.set_quality(Quality::GOOD);
    avg.calculate();
    EXPECT_EQ(avg.get_value<int64_t>(), 25);
    EXPECT_EQ(avg.get_quality(), Quality::GOOD);
}

TEST(ChauvenetAveragePoint, Float)
{
    double values[9] = { 0.0 };
    Quality qualities[9] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[9];
    auto inpA = ExternalPoint<float>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<float>(&values[1], &qualities[1], &durations[1]);
    auto inpC = ExternalPoint<float>(&values[2], &qualities[2], &durations[2]);
    auto inpD = ExternalPoint<float>(&values[3], &qualities[3], &durations[3]);
    auto inpE = ExternalPoint<float>(&values[4], &qualities[4], &durations[4]);
    auto inpF = ExternalPoint<float>(&values[5], &qualities[5], &durations[5]);
    auto inpG = ExternalPoint<float>(&values[6], &qualities[6], &durations[6]);
    auto num = ExternalPoint<int32_t>(&values[7], &qualities[7], &durations[7]);
    auto avg = ChauvenetAveragePoint<float>(&values[8], &qualities[8], &durations[8]);
    avg.add_input(&inpA);
    avg.add_input(&inpB);
    avg.add_input(&inpC);
    avg.add_input(&inpD);
    avg.add_input(&inpE);
    avg.add_input(&inpF);
    avg.add_input(&inpG);
    avg.set_min_good_points(&num);
    // One value way outside the average
    inpA.set_value(2.3f);
    inpB.set_value(2.4f);
    inpC.set_value(2.5f);
    inpD.set_value(2.6f);
    inpE.set_value(992.5f);
    inpF.set_value(2.5f);
    inpG.set_value(2.7f);
    num.set_value(5);
    // Different point with a bad quality
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    inpC.set_quality(Quality::GOOD);
    inpD.set_quality(Quality::GOOD);
    inpE.set_quality(Quality::GOOD);
    inpF.set_quality(Quality::DELETED);
    inpG.set_quality(Quality::GOOD);
    num.set_quality(Quality::GOOD);
    avg.calculate();
    EXPECT_FLOAT_EQ(avg.get_value<float>(), 2.5f);
    EXPECT_EQ(avg.get_quality(), Quality::GOOD);
}

TEST(ChauvenetAveragePoint, Double)
{
    double values[6] = { 0.0 };
    Quality qualities[6] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[6];
    auto inpA = ExternalPoint<double>(&values[0], &qualities[0], &durations[0]);
    auto inpB = ExternalPoint<double>(&values[1], &qualities[1], &durations[1]);
    auto inpC = ExternalPoint<double>(&values[2], &qualities[2], &durations[2]);
    auto inpD = ExternalPoint<double>(&values[3], &qualities[3], &durations[3]);
    auto num = ExternalPoint<int32_t>(&values[4], &qualities[4], &durations[4]);
    auto avg = ChauvenetAveragePoint<double>(&values[5], &qualities[5], &durations[5]);
    avg.add_input(&inpA);
    avg.add_input(&inpB);
    avg.add_input(&inpC);
    avg.add_input(&inpD);
    avg.set_min_good_points(&num);
    inpA.set_value(25.28);
    inpB.set_value(25.25);
    inpC.set_value(25.22);
    inpD.set_value(20.00);
    num.set_value(3);
    inpA.set_quality(Quality::GOOD);
    inpB.set_quality(Quality::GOOD);
    inpC.set_quality(Quality::GOOD);
    inpD.set_quality(Quality::GOOD);
    num.set_quality(Quality::GOOD);
    avg.calculate();
    EXPECT_DOUBLE_EQ(avg.get_value<double>(), 25.25);
    EXPECT_EQ(avg.get_quality(), Quality::GOOD);
}
