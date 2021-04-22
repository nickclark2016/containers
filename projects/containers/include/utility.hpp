#ifndef utility_hpp__
#define utility_hpp__

/// \file utility.hpp
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
///
/// <summary>
/// File containing implementation of utility functions.
/// </summary>

#include "type_traits.hpp"

namespace containers
{
    /// <summary>
    /// Function used to indicate that the value <paramref name="arg" may be moved from, allowing the compiler to
    /// efficiently transfer resources to another object.
    /// </summary>
    /// <typeparam name="T">
    /// Type of the value to move.
    /// </typeparam>
    /// <param name="arg">
    /// Object to be moved.
    /// </param>
    /// <returns>
    /// Value of object with move semantics.
    /// </returns>
    template <typename T>
    inline remove_reference_t<T>&& move(T&& arg)
    {
        return static_cast<remove_reference_t<T>&&>(arg);
    }
} // namespace containers

#endif // utility_hpp__
