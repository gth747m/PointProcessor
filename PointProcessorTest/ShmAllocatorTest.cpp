#include "pch.h"

using namespace point_processor;

TEST(ShmAllocator, VectorInt32)
{
    ShmVector<int32_t> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.clear();
}

TEST(ShmAllocator, VectorInt64)
{
    ShmVector<int64_t> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.clear();
}

TEST(ShmAllocator, VectorFloat)
{
    ShmVector<float> vec;
    vec.push_back(1.0f);
    vec.push_back(2.0f);
    vec.push_back(3.0f);
    vec.clear();
}

TEST(ShmAllocator, VectorDouble)
{
    ShmVector<double> vec;
    vec.push_back(1.0);
    vec.push_back(2.0);
    vec.push_back(3.0);
    vec.clear();
}

TEST(ShmAllocator, String)
{
    ShmString str("Hello World");
    ASSERT_STREQ(str.c_str(), "Hello World");
    str.append("!");
    ASSERT_STREQ(str.c_str(), "Hello World!");
}