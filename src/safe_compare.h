/*******************************************************************************
 *
 * MIT License
 *
 * Copyright (c) 2018 Joshua Koch
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ******************************************************************************/

#pragma once

#include <type_traits>

namespace safe_compare
{

///
template< bool B, typename T = void >
using enable_if_t = typename std::enable_if< B, T >::type;

///
template< typename T >
using make_unsigned_t = typename std::make_unsigned< T >::type;

///
template< typename T, typename U >
struct both_arithmetic
{
    static constexpr bool value =
        std::is_arithmetic< T >::value && std::is_arithmetic< U >::value;
};

///
template< typename T, typename U >
struct needs_cast
{
    static constexpr bool value =
        ( std::is_integral< T >::value && std::is_integral< U >::value ) && (
        ( std::is_signed< T >::value && std::is_unsigned< U >::value ) ||
        ( std::is_unsigned< T >::value && std::is_signed< U >::value ) );
};

///
template< typename A, typename B, typename =
    enable_if_t< both_arithmetic< A, B >::value > >
struct greater
{
    ///
    template< typename T = A, typename U = B >
    enable_if_t< !needs_cast< T, U >::value, bool >
    constexpr operator()( T lhs, U rhs ) const
    {
        return ( lhs > rhs );
    }

    ///
    template< typename T = A, typename U = B >
    enable_if_t< needs_cast< T, U >::value && std::is_signed< T >::value, bool >
    constexpr operator()( T lhs, U rhs ) const
    {
        return ( lhs >= 0 ) &&
            ( static_cast< make_unsigned_t< T > >( lhs ) > rhs );
    }

    ///
    template< typename T = A, typename U = B >
    enable_if_t< needs_cast< T, U >::value && std::is_signed< U >::value, bool >
    constexpr operator()( T lhs, U rhs ) const
    {
        return ( rhs < 0 ) ||
            ( lhs > static_cast< make_unsigned_t< U > >( rhs ) );
    }
};

///
template< typename A, typename B, typename =
    enable_if_t< both_arithmetic< A, B >::value > >
struct less
{
    ///
    template< typename T = A, typename U = B >
    enable_if_t< !needs_cast< T, U >::value, bool >
    constexpr operator()( T lhs, U rhs ) const
    {
        return ( lhs < rhs );
    }

    ///
    template< typename T = A, typename U = B >
    enable_if_t< needs_cast< T, U >::value && std::is_signed< T >::value, bool >
    constexpr operator()( T lhs, U rhs ) const
    {
        return ( lhs < 0 ) ||
            ( static_cast< make_unsigned_t< T > >( lhs ) < rhs );
    }

    ///
    template< typename T = A, typename U = B >
    enable_if_t< needs_cast< T, U >::value && std::is_signed< U >::value, bool >
    constexpr operator()( T lhs, U rhs ) const
    {
        return ( rhs >= 0 ) &&
            ( lhs < static_cast< make_unsigned_t< U > >( rhs ) );
    }
};

///
template< typename A, typename B, typename =
    enable_if_t< both_arithmetic< A, B >::value > >
struct greater_equal
{
    ///
    template< typename T = A, typename U = B >
    enable_if_t< !needs_cast< T, U >::value, bool >
    constexpr operator()( T lhs, U rhs ) const
    {
        return ( lhs >= rhs );
    }

    ///
    template< typename T = A, typename U = B >
    enable_if_t< needs_cast< T, U >::value && std::is_signed< T >::value, bool >
    constexpr operator()( T lhs, U rhs ) const
    {
        return ( lhs >= 0 ) &&
            ( static_cast< make_unsigned_t< T > >( lhs ) >= rhs );
    }

    ///
    template< typename T = A, typename U = B >
    enable_if_t< needs_cast< T, U >::value && std::is_signed< U >::value, bool >
    constexpr operator()( T lhs, U rhs ) const
    {
        return ( rhs < 0 ) ||
            ( lhs >= static_cast< make_unsigned_t< U > >( rhs ) );
    }
};

///
template< typename A, typename B, typename =
    enable_if_t< both_arithmetic< A, B >::value > >
struct less_equal
{
    ///
    template< typename T = A, typename U = B >
    enable_if_t< !needs_cast< T, U >::value, bool >
    constexpr operator()( T lhs, U rhs ) const
    {
        return ( lhs <= rhs );
    }

    ///
    template< typename T = A, typename U = B >
    enable_if_t< needs_cast< T, U >::value && std::is_signed< T >::value, bool >
    constexpr operator()( T lhs, U rhs ) const
    {
        return ( lhs < 0 ) ||
            ( static_cast< make_unsigned_t< T > >( lhs ) <= rhs );
    }

    ///
    template< typename T = A, typename U = B >
    enable_if_t< needs_cast< T, U >::value && std::is_signed< U >::value, bool >
    constexpr operator()( T lhs, U rhs ) const
    {
        return ( rhs >= 0 ) &&
            ( lhs <= static_cast< make_unsigned_t< U > >( rhs ) );
    }
};

///
template< typename T, typename U, typename =
    enable_if_t< both_arithmetic< T, U >::value > >
constexpr bool is_greater( T lhs, U rhs )
{
    return greater< T, U >()( lhs, rhs );
}

///
template< typename T, typename U, typename =
    enable_if_t< both_arithmetic< T, U >::value > >
constexpr bool is_less( T lhs, U rhs )
{
    return less< T, U >()( lhs, rhs );
}

///
template< typename T, typename U, typename =
    enable_if_t< both_arithmetic< T, U >::value > >
constexpr bool is_greater_equal( T lhs, U rhs )
{
    return greater_equal< T, U >()( lhs, rhs );
}

///
template< typename T, typename U, typename =
    enable_if_t< both_arithmetic< T, U >::value > >
constexpr bool is_less_equal( T lhs, U rhs )
{
    return less_equal< T, U >()( lhs, rhs );
}

} //end safe_compare
