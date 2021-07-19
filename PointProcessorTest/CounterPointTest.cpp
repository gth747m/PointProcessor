#include "pch.h"

using namespace PointProcessor;

TEST(CounterPoint, Int32)
{
    auto counter = CounterPoint<int32_t>();
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
    auto counter = CounterPoint<int64_t>();
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