#include "pch.h"

TEST(ShmAllocator, VectorInt32)
{
    std::vector<int32_t, ShmAllocator<int32_t>> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.clear();
}

TEST(ShmAllocator, VectorInt64)
{
    std::vector<int64_t, ShmAllocator<int64_t>> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.clear();
}

TEST(ShmAllocator, VectorFloat)
{
    std::vector<float, ShmAllocator<float>> vec;
    vec.push_back(1.0f);
    vec.push_back(2.0f);
    vec.push_back(3.0f);
    vec.clear();
}

TEST(ShmAllocator, VectorDouble)
{
    std::vector<double, ShmAllocator<double>> vec;
    vec.push_back(1.0);
    vec.push_back(2.0);
    vec.push_back(3.0);
    vec.clear();
}

TEST(ShmAllocator, String)
{
    using string = std::basic_string<char, 
            std::char_traits<char>, ShmAllocator<char>>;
    string str("Hello World");
    ASSERT_STREQ(str.c_str(), "Hello World");
    str.append("!");
    ASSERT_STREQ(str.c_str(), "Hello World!");
}