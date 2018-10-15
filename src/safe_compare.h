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

// --- Standard Includes --- //
#include <type_traits>

namespace safe_compare
{

///For c++11
template< bool B, typename T = void >
using enable_if_t = typename std::enable_if< B, T >::type;

///For c++11
template< typename T >
using make_unsigned_t = typename std::make_unsigned< T >::type;

///For c++11
template< typename T >
constexpr bool is_arithmetic_v = std::is_arithmetic< T >::value;

///For c++11
template< typename T >
constexpr bool is_integral_v = std::is_integral< T >::value;

///For c++11
template< typename T >
constexpr bool is_signed_v = std::is_signed< T >::value;

///
template< typename T, typename U >
constexpr bool both_arithmetic_v =
    is_arithmetic_v< T > && is_arithmetic_v< U >;

///
template< typename T, typename U >
constexpr bool both_integral_v =
    is_integral_v< T > && is_integral_v< U >;

///
template< typename T, typename U >
constexpr bool both_signed_v =
    is_signed_v< T > && is_signed_v< U >;

///
template< typename T, typename U >
constexpr bool both_unsigned_v =
    !is_signed_v< T > && !is_signed_v< U >;

///
template< typename T, typename U >
constexpr bool needs_cast_v =
    both_integral_v< T, U > &&
    !( both_signed_v< T, U > || both_unsigned_v< T, U > );

///
template< typename A, typename B, typename =
    enable_if_t< both_arithmetic_v< A, B > > >
struct greater
{
    ///
    template< typename T = A, typename U = B >
    constexpr enable_if_t< !needs_cast_v< T, U >, bool >
    operator()( T lhs, U rhs ) const
    {
        return ( lhs > rhs );
    }

    ///
    template< typename T = A, typename U = B >
    constexpr enable_if_t< needs_cast_v< T, U > && is_signed_v< T >, bool >
    operator()( T lhs, U rhs ) const
    {
        return ( lhs >= 0 ) &&
            ( static_cast< make_unsigned_t< T > >( lhs ) > rhs );
    }

    ///
    template< typename T = A, typename U = B >
    constexpr enable_if_t< needs_cast_v< T, U > && is_signed_v< U >, bool >
    operator()( T lhs, U rhs ) const
    {
        return ( rhs < 0 ) ||
            ( lhs > static_cast< make_unsigned_t< U > >( rhs ) );
    }
};

///
template< typename A, typename B, typename =
    enable_if_t< both_arithmetic_v< A, B > > >
struct greater_equal
{
    ///
    template< typename T = A, typename U = B >
    constexpr enable_if_t< !needs_cast_v< T, U >, bool >
    operator()( T lhs, U rhs ) const
    {
        return ( lhs >= rhs );
    }

    ///
    template< typename T = A, typename U = B >
    constexpr enable_if_t< needs_cast_v< T, U > && is_signed_v< T >, bool >
    operator()( T lhs, U rhs ) const
    {
        return ( lhs >= 0 ) &&
            ( static_cast< make_unsigned_t< T > >( lhs ) >= rhs );
    }

    ///
    template< typename T = A, typename U = B >
    constexpr enable_if_t< needs_cast_v< T, U > && is_signed_v< U >, bool >
    operator()( T lhs, U rhs ) const
    {
        return ( rhs < 0 ) ||
            ( lhs >= static_cast< make_unsigned_t< U > >( rhs ) );
    }
};

///
template< typename A, typename B, typename =
    enable_if_t< both_arithmetic_v< A, B > > >
class less
{
    ///
    template< typename T = A, typename U = B >
    constexpr enable_if_t< !needs_cast_v< T, U >, bool >
    operator()( T lhs, U rhs ) const
    {
        return ( lhs < rhs );
    }

    ///
    template< typename T = A, typename U = B >
    constexpr enable_if_t< needs_cast_v< T, U > && is_signed_v< T >, bool >
    operator()( T lhs, U rhs ) const
    {
        return ( lhs < 0 ) ||
            ( static_cast< make_unsigned_t< T > >( lhs ) < rhs );
    }

    ///
    template< typename T = A, typename U = B >
    constexpr enable_if_t< needs_cast_v< T, U > && is_signed_v< U >, bool >
    operator()( T lhs, U rhs ) const
    {
        return ( rhs >= 0 ) &&
            ( lhs < static_cast< make_unsigned_t< U > >( rhs ) );
    }
};

///
template< typename A, typename B, typename =
    enable_if_t< both_arithmetic_v< A, B > > >
class less_equal
{
    ///
    template< typename T = A, typename U = B >
    constexpr enable_if_t< !needs_cast_v< T, U >, bool >
    operator()( T lhs, U rhs ) const
    {
        return ( lhs <= rhs );
    }

    ///
    template< typename T = A, typename U = B >
    constexpr enable_if_t< needs_cast_v< T, U > && is_signed_v< T >, bool >
    operator()( T lhs, U rhs ) const
    {
        return ( lhs < 0 ) ||
            ( static_cast< make_unsigned_t< T > >( lhs ) <= rhs );
    }

    ///
    template< typename T = A, typename U = B >
    constexpr enable_if_t< needs_cast_v< T, U > && is_signed_v< U >, bool >
    operator()( T lhs, U rhs ) const
    {
        return ( rhs >= 0 ) &&
            ( lhs <= static_cast< make_unsigned_t< U > >( rhs ) );
    }
};

} //end safe_compare
