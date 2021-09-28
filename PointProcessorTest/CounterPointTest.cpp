#include "pch.h"

using namespace point_processor;

TEST(CounterPoint, Int32)
{
    double values[1] = { 0.0 };
    Quality qualities[1] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[1];
    auto counter = CounterPoint<int32_t>(&values[0], &qualities[0], &durations[0]);
    for (int i = 0; i < 10; i++)
    {
        counter.increment();
    }
    counter.calculate();
    EXPECT_EQ(counter.get_value<int32_t>(), 10);
    EXPECT_EQ(counter.get_quality(), Quality::GOOD);
    for (int i = 0; i < 10; i++)
    {
        counter.increment();
    }
    for (int i = 0; i < 8; i++)
    {
        counter.decrement();
    }
    counter.calculate();
    EXPECT_EQ(counter.get_value<int32_t>(), 2);
    EXPECT_EQ(counter.get_quality(), Quality::GOOD);
}

TEST(CounterPoint, Int64)
{
    double values[1] = { 0.0 };
    Quality qualities[1] = { Quality::UNKNOWN };
    std::chrono::duration<int, std::micro> durations[1];
    auto counter = CounterPoint<int64_t>(&values[0], &qualities[0], &durations[0]);
    for (int i = 0; i < 10; i++)
    {
        counter.increment();
    }
    counter.calculate();
    EXPECT_EQ(counter.get_value<int64_t>(), 10);
    EXPECT_EQ(counter.get_quality(), Quality::GOOD);
    for (int i = 0; i < 10; i++)
    {
        counter.increment();
    }
    for (int i = 0; i < 8; i++)
    {
        counter.decrement();
    }
    counter.calculate();
    EXPECT_EQ(counter.get_value<int64_t>(), 2);
    EXPECT_EQ(counter.get_quality(), Quality::GOOD);
}