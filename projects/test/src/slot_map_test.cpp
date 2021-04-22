/// \file slot_map_test.cpp
/// <summary>
/// File containing unit tests for slot_map.
///
/// \author Nicholaus Clark
/// \copyright Copyright 2021 Nicholaus Clark
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
/// documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
/// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
/// permit persons to whom the Software is furnished to do so, subject to the following conditions: <br />
/// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
/// Software. <br />
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
/// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
/// OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
/// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
/// </summary>

#include <slot_map.hpp>

#include <gtest/gtest.h>

using namespace containers;

TEST(slot_map, default_constructor)
{
    slot_map<u32> map;
    ASSERT_EQ(0, map.size());
    ASSERT_LE(0, map.capacity());
}

TEST(slot_map, insert_single_value)
{
    const u32 value = 3;
    
    slot_map<u32> map;
    auto key = map.insert(value);

    const u32 actual = map.get(key);

    ASSERT_EQ(value, actual);
    ASSERT_EQ(1, map.size());
    ASSERT_LE(1, map.capacity());
}

TEST(slot_map, insert_multiple_values)
{
    const u32 value1 = 3;
    const u32 value2 = 4;
    
    slot_map<u32> map;
    auto key1 = map.insert(value1);
    auto key2 = map.insert(value2);

    const u32 actual1 = map.get(key1);
    const u32 actual2 = map.get(key2);

    ASSERT_EQ(value1, actual1);
    ASSERT_EQ(value2, actual2);
    ASSERT_EQ(2, map.size());
    ASSERT_LE(2, map.capacity());
}

TEST(slot_map, insert_then_remove_then_insert_value)
{
    const u32 value1 = 3;
    const u32 value2 = 4;
    
    slot_map<u32> map;
    auto key1 = map.insert(value1);
    map.erase(key1);
    auto key2 = map.insert(value2);

    const u32* actual1 = map.try_get(key1);
    const u32 actual2 = map.get(key2);

    ASSERT_EQ(nullptr, actual1);
    ASSERT_EQ(value2, actual2);
    ASSERT_EQ(1, map.size());
    ASSERT_LE(1, map.capacity());
}

TEST(slot_map, insert_then_remove_then_multiple_insert_values)
{
    const u32 value1 = 3;
    const u32 value2 = 4;
    const u32 value3 = 5;
    
    slot_map<u32> map;
    auto key1 = map.insert(value1);
    map.erase(key1);
    auto key2 = map.insert(value2);
    auto key3 = map.insert(value3);

    const u32* actual1 = map.try_get(key1);
    const u32 actual2 = map.get(key2);
    const u32 actual3 = map.get(key3);

    ASSERT_EQ(nullptr, actual1);
    ASSERT_EQ(value2, actual2);
    ASSERT_EQ(value3, actual3);
    ASSERT_EQ(2, map.size());
    ASSERT_LE(2, map.capacity());
}

TEST(slot_map, insert_multiple_then_remove_then_insert_value)
{
    const u32 value1 = 3;
    const u32 value2 = 4;
    const u32 value3 = 5;
    
    slot_map<u32> map;
    auto key1 = map.insert(value1);
    auto key2 = map.insert(value2);
    map.erase(key2);
    auto key3 = map.insert(value3);

    const u32 actual1 = map.get(key1);
    const u32* actual2 = map.try_get(key2);
    const u32 actual3 = map.get(key3);

    ASSERT_EQ(value1, actual1);
    ASSERT_EQ(nullptr, actual2);
    ASSERT_EQ(value3, actual3);
    ASSERT_EQ(2, map.size());
    ASSERT_LE(2, map.capacity());
}

TEST(slot_map, reserve_large_size)
{
    const u32 value1 = 3;
    const u32 value2 = 4;
    const u32 value3 = 5;
    
    slot_map<u32> map;
    map.reserve(4);

    ASSERT_EQ(0, map.size());
    ASSERT_TRUE(map.empty());
    ASSERT_LE(4, map.capacity());

    auto key1 = map.insert(value1);
    auto key2 = map.insert(value2);
    auto key3 = map.insert(value3);

    const u32 actual1 = map.get(key1);
    const u32 actual2 = map.get(key2);
    const u32 actual3 = map.get(key3);

    ASSERT_EQ(value1, actual1);
    ASSERT_EQ(value2, actual2);
    ASSERT_EQ(value3, actual3);
    ASSERT_EQ(3, map.size());
    ASSERT_LE(4, map.capacity());
}

TEST(slot_map, reserve_smaller_size)
{
    const u32 value1 = 3;
    const u32 value2 = 4;
    const u32 value3 = 5;
    
    slot_map<u32> map;

    ASSERT_EQ(0, map.size());
    ASSERT_TRUE(map.empty());
    ASSERT_LE(0, map.capacity());

    auto key1 = map.insert(value1);
    auto key2 = map.insert(value2);
    auto key3 = map.insert(value3);

    map.reserve(2);

    const u32 actual1 = map.get(key1);
    const u32 actual2 = map.get(key2);
    const u32 actual3 = map.get(key3);

    ASSERT_EQ(value1, actual1);
    ASSERT_EQ(value2, actual2);
    ASSERT_EQ(value3, actual3);
    ASSERT_EQ(3, map.size());
    ASSERT_LE(3, map.capacity());
}

TEST(slot_map, reserve_large_size_then_insert_values)
{
    const u32 value1 = 3;
    const u32 value2 = 4;
    const u32 value3 = 5;
    const u32 value4 = 6;
    
    slot_map<u32> map;

    ASSERT_EQ(0, map.size());
    ASSERT_TRUE(map.empty());

    auto key1 = map.insert(value1);
    auto key2 = map.insert(value2);
    auto key3 = map.insert(value3);
    auto key4 = map.insert(value4);

    map.reserve(6);

    const u32 actual1 = map.get(key1);
    const u32 actual2 = map.get(key2);
    const u32 actual3 = map.get(key3);
    const u32 actual4 = map.get(key4);

    ASSERT_EQ(value1, actual1);
    ASSERT_EQ(value2, actual2);
    ASSERT_EQ(value3, actual3);
    ASSERT_EQ(value4, actual4);
    ASSERT_EQ(4, map.size());
    ASSERT_LE(6, map.capacity());
}
