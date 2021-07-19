#include "pch.h"

using namespace PointProcessor;

TEST(ChauvenetAveragePoint, Int32)
{
    auto inpA = ExternalPoint<int32_t>();
    auto inpB = ExternalPoint<int32_t>();
    auto inpC = ExternalPoint<int32_t>();
    auto num = ExternalPoint<int32_t>();
    auto avg = ChauvenetAveragePoint<int32_t>();
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
    auto inpA = ExternalPoint<int64_t>();
    auto inpB = ExternalPoint<int64_t>();
    auto inpC = ExternalPoint<int64_t>();
    auto inpD = ExternalPoint<int64_t>();
    auto num = ExternalPoint<int32_t>();
    auto avg = ChauvenetAveragePoint<int64_t>();
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
    auto inpA = ExternalPoint<float>();
    auto inpB = ExternalPoint<float>();
    auto inpC = ExternalPoint<float>();
    auto inpD = ExternalPoint<float>();
    auto inpE = ExternalPoint<float>();
    auto inpF = ExternalPoint<float>();
    auto inpG = ExternalPoint<float>();
    auto num = ExternalPoint<int32_t>();
    auto avg = ChauvenetAveragePoint<float>();
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
    auto inpA = ExternalPoint<double>();
    auto inpB = ExternalPoint<double>();
    auto inpC = ExternalPoint<double>();
    auto inpD = ExternalPoint<double>();
    auto num = ExternalPoint<int32_t>();
    auto avg = ChauvenetAveragePoint<double>();
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
