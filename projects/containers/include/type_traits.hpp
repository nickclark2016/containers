#ifndef type_traits_hpp__
#define type_traits_hpp__

/// \file type_traits.hpp
/// <summary>
/// File containing implementation of type traits needed for containers.
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

namespace containers
{
    /// <summary>
    /// Structure providing a type alias based on a compile-time boolean expression.  If the <c>B == true</c>, the alias
    /// <c>type</c> is set to <typeparamref name="T" /> else, the alias is set to <typeparamref name="F" />.
    /// </summary>
    /// <typeparam name="T">Type of conditional alias if <c>B == true</c></typeparam>
    /// <typeparam name="F">Type of conditional alias if <c>B == false</c></typeparam>
    template <bool B, typename T, typename F>
    struct conditional
    {
        using type = T;
    };

    template <typename T, typename F>
    struct conditional<false, T, F>
    {
        using type = F;
    };

    /// <summary>
    /// Alias based on a compile-time boolean expression.  If the <c>B == true</c>, the alias
    /// <c>type</c> is set to <typeparamref name="T" /> else, the alias is set to <typeparamref name="F" />.
    /// </summary>
    /// <typeparam name="T">Type of conditional alias if <c>B == true</c></typeparam>
    /// <typeparam name="F">Type of conditional alias if <c>B == false</c></typeparam>
    template <bool B, typename T, typename F>
    using conditional_t = typename conditional<B, T, F>::type;

    /// <summary>
    /// Structure providing type alias for <typeparamref name="T" /> without any references.
    /// </summary>
    /// <typeparam name="T">
    /// Type to remove reference from
    /// </typeparam>
    template <typename T>
    struct remove_reference
    {
        /// <summary>
        /// Type alias without references.
        /// </summary>
        using type = T;
    };

    template <typename T>
    struct remove_reference<T&>
    {
        using type = T;
    };

    template <typename T>
    struct remove_reference<T&&>
    {
        using type = T;
    };

    /// <summary>
    /// Alias for <typeparamref name="T" /> without any references.
    /// </summary>
    /// <typeparam name="T">
    /// Type to remove reference from
    /// </typeparam>
    template <typename T>
    using remove_reference_t = typename remove_reference<T>::type;
} // namespace containers

#endif // type_traits_hpp__