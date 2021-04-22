/// \file slot_map.hpp
/// <summary>
/// File containing unit tests for stdint aliases.
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

#include <stdint.hpp>

#include <gtest/gtest.h>

using namespace containers;

/// <summary>
/// Tests to ensure u8 is 1 byte wide.
/// </summary>
TEST(stdint, u8_size)
{
    ASSERT_EQ(1, sizeof(u8));
}

/// <summary>
/// Tests to ensure u16 is 2 bytes wide.
/// </summary>
TEST(stdint, u16_size)
{
    ASSERT_EQ(2, sizeof(u16));
}

/// <summary>
/// Tests to ensure u32 is 4 bytes wide.
/// </summary>
TEST(stdint, u32_size)
{
    ASSERT_EQ(4, sizeof(u32));
}

/// <summary>
/// Tests to ensure u64 is 8 bytes wide.
/// </summary>
TEST(stdint, u64_size)
{
    ASSERT_EQ(8, sizeof(u64));
}

/// <summary>
/// Tests to ensure i8 is 1 byte wide.
/// </summary>
TEST(stdint, i8_size)
{
    ASSERT_EQ(1, sizeof(i8));
}

/// <summary>
/// Tests to ensure i16 is 2 bytes wide.
/// </summary>
TEST(stdint, i16_size)
{
    ASSERT_EQ(2, sizeof(i16));
}

/// <summary>
/// Tests to ensure i32 is 4 bytes wide.
/// </summary>
TEST(stdint, i32_size)
{
    ASSERT_EQ(4, sizeof(i32));
}

/// <summary>
/// Tests to ensure i64 is 8 bytes wide.
/// </summary>
TEST(stdint, i64_size)
{
    ASSERT_EQ(8, sizeof(i64));
}
