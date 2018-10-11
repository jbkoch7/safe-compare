#pragma once

// --- Standard Includes --- //
#include <iostream>
#include <type_traits>

namespace safe_compare
{

///For c++11
template< bool B, typename T = void >
using enable_if_t = typename std::enable_if< B, T >::type;

///For c++11
template< class T >
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
            ( static_cast< std::make_unsigned_t< T > >( lhs ) > rhs );
    }

    ///
    template< typename T = A, typename U = B >
    constexpr enable_if_t< needs_cast_v< T, U > && is_signed_v< U >, bool >
    operator()( T lhs, U rhs ) const
    {
        return ( rhs < 0 ) ||
            ( lhs > static_cast< std::make_unsigned_t< U > >( rhs ) );
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
            ( static_cast< std::make_unsigned_t< T > >( lhs ) >= rhs );
    }

    ///
    template< typename T = A, typename U = B >
    constexpr enable_if_t< needs_cast_v< T, U > && is_signed_v< U >, bool >
    operator()( T lhs, U rhs ) const
    {
        return ( rhs < 0 ) ||
            ( lhs >= static_cast< std::make_unsigned_t< U > >( rhs ) );
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
            ( static_cast< std::make_unsigned_t< T > >( lhs ) < rhs );
    }

    ///
    template< typename T = A, typename U = B >
    constexpr enable_if_t< needs_cast_v< T, U > && is_signed_v< U >, bool >
    operator()( T lhs, U rhs ) const
    {
        return ( rhs >= 0 ) &&
            ( lhs < static_cast< std::make_unsigned_t< U > >( rhs ) );
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
            ( static_cast< std::make_unsigned_t< T > >( lhs ) <= rhs );
    }

    ///
    template< typename T = A, typename U = B >
    constexpr enable_if_t< needs_cast_v< T, U > && is_signed_v< U >, bool >
    operator()( T lhs, U rhs ) const
    {
        return ( rhs >= 0 ) &&
            ( lhs <= static_cast< std::make_unsigned_t< U > >( rhs ) );
    }
};

} //end safe_compare
