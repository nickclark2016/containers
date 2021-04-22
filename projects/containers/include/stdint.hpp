#ifndef stdint_hpp__
#define stdint_hpp__

/// \file stdint.hpp
/// <summary>
/// File containing implementation of type aliases for defining integral types with size information.
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

#include "type_traits.hpp"

namespace containers
{
    /// <summary>
    /// Unsigned integral type that is 8 bits wide.
    /// </summary>
    using u8 = unsigned char;

    /// <summary>
    /// Unsigned integral type that is 16 bits wide.
    /// </summary>
    using u16 = unsigned short;

    /// <summary>
    /// Unsigned integral type that is 32 bits wide.
    /// </summary>
    using u32 = unsigned int;

    /// <summary>
    /// Unsigned integral type that is 64 bits wide.
    /// </summary>
    using u64 = unsigned long long;

    /// <summary>
    /// Signed integral type that is 8 bits wide.
    /// </summary>
    using i8 = char;

    /// <summary>
    /// Signed integral type that is 16 bits wide.
    /// </summary>
    using i16 = short;

    /// <summary>
    /// Signed integral type that is 32 bits wide.
    /// </summary>
    using i32 = int;

    /// <summary>
    /// Signed integral type that is 64 bits wide.
    /// </summary>
    using i64 = long long;

    /// <summary>
    /// Unsigned integral type as wide as a pointer type.
    /// </summary>
    using size_t = conditional_t<sizeof(void*) == sizeof(u32), u32, u64>;
} // namespace containers

#endif // stdint_hpp__