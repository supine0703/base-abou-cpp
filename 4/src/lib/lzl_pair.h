#ifndef LZL_PAIR_H
#define LZL_PAIR_H

#include <type_traits>
#include <utility>

namespace lzl
{

template <typename T1, typename T2>
struct pair
{
public:
    using first_type = T1;
    using second_type = T2;

    T1 first;  // the first stored value
    T2 second; // the second stored value

    constexpr pair(const pair&) = default;
    constexpr pair(pair&&) = default;

    constexpr explicit pair()
        requires(::std::is_default_constructible_v<T1> && ::std::is_default_constructible_v<T2>)
        : first(), second()
    {}

    constexpr void swap(pair& o)
    {
        if (this != ::std::addressof(o))
        {
            ::std::swap(first, o.first);
            ::std::swap(second, o.second);
        }
    }

private:
    // @c++11 Constructible
    template <typename U1, typename U2>
    static constexpr bool s_constructible()
    {
        return ::std::is_constructible_v<T1, U1> && ::std::is_constructible_v<T2, U2>;
    }

    template <typename U1, typename U2>
    static constexpr bool s_nothrow_constructible()
    {
        return ::std::is_nothrow_constructible_v<T1, U1> &&
               ::std::is_nothrow_constructible_v<T2, U2>;
    }

    // @c++11 Convertible
    template <typename U1, typename U2>
    static constexpr bool s_convertible()
    {
        return ::std::is_convertible_v<U1, T1> && ::std::is_convertible_v<U2, T2>;
    }

    // @c++17 Assignable
    template <typename U1, typename U2>
    static constexpr bool s_assignable()
    {
        return ::std::is_assignable_v<T1&, U1> && ::std::is_assignable_v<T2&, U2>;
    }

    template <typename U1, typename U2>
    static constexpr bool s_nothrow_assignable()
    {
        return ::std::is_nothrow_assignable_v<T1&, U1> && ::std::is_nothrow_assignable_v<T2&, U2>;
    }

public:
    // Need type conversion for construction and assignment
    // Constructor
    // Constructor accepting left values of `first_type` and `second_type`
    constexpr explicit(!s_convertible<const T1&, const T2&>())
        pair(const T1& x, const T2& y) noexcept(s_nothrow_constructible<const T1&, const T2&>())
        requires(s_constructible<const T1&, const T2&>())
        : first(x), second(y)
    {}

    // Constructor accepting two values of arbitrary types
    template <typename U1, typename U2>
    constexpr explicit(!s_convertible<U1, U2>())
        pair(U1 x, U2 y) noexcept(s_nothrow_constructible<U1, U2>())
        requires(s_constructible<U1, U2>())
        : first(::std::forward<U1>(x)), second(::std::forward<U2>(y))
    {}

    // Converting constructor from a const `pair<U1, U2>` lvalue
    template <typename U1, typename U2>
    constexpr explicit(!s_convertible<const U1&, const U2&>())
        pair(const pair<U1, U2>& o) noexcept(s_nothrow_constructible<const U1&, const U2&>())
        requires(s_constructible<const U1&, const U2&>())
        : first(o.first), second(o.second)
    {}

    // Converting constructor from a non-const `pair<U1, U2>` rvalue
    template <typename U1, typename U2>
    constexpr explicit(!s_convertible<U1, U2>())
        pair(pair<U1, U2>&& o) noexcept(s_nothrow_constructible<U1, U2>())
        requires(s_constructible<U1, U2>())
        : first(::std::forward<U1>(o.first)), second(::std::forward<U2>(o.second))
    {}

    // Assignment
    pair& operator=(const volatile pair&) = delete;

    // Copy assignment operator
    constexpr pair& operator=(const pair& o) noexcept(s_nothrow_assignable<const T1&, const T2&>())
        requires(s_assignable<const T1&, const T2&>())
    {
        first = o.first;
        second = o.second;
        return *this;
    }

    // Move assignment operator
    constexpr pair& operator=(pair&& o) noexcept(s_nothrow_assignable<T1, T2>())
        requires(s_assignable<T1, T2>())
    {
        first = ::std::forward<first_type>(o.first);
        second = ::std::forward<second_type>(o.second);
        return *this;
    }

    // Converting assignment from a const `pair<U1, U2>` lvalue
    template <typename U1, typename U2>
    constexpr pair& operator=(const pair<U1, U2>& o
    ) noexcept(s_nothrow_assignable<const U1&, const U2&>())
        requires(s_assignable<const U1&, const U2&>())
    {
        first = o.first;
        second = o.second;
        return *this;
    }

    // Converting assignment from a non-const `pair<U1, U2>` rvalue
    template <typename U1, typename U2>
    constexpr pair& operator=(pair<U1, U2>&& o) noexcept(s_nothrow_assignable<U1, U2>())
        requires(s_assignable<U1, U2>())
    {
        first = ::std::forward<U1>(o.first);
        second = ::std::forward<U2>(o.second);
        return *this;
    }

    // Swap: Make swap more possible, but also potentially more risky
    template <typename U1, typename U2>
    constexpr void swap(pair<U1, U2>& o) noexcept(s_nothrow_assignable<U1, U2>())
        requires(s_constructible<U1, U2>() && (::std::is_convertible_v<T1, U1> && ::std::is_convertible_v<T2, U2>) && !::std::is_same_v<pair<T1, T2>, pair<U1, U2>>)
    {
        auto tmp = ::std::move(*this);
        *this = ::std::move(o);
        o = ::std::move(tmp);
    }
};

template <typename T1, typename T2, typename U1, typename U2>
constexpr bool operator==(const pair<T1, T2>& x, const pair<U1, U2>& y)
{
    return x.first == y.first && x.second == y.second;
}

template <typename T1, typename T2, typename U1, typename U2>
constexpr auto operator<=>(const pair<T1, T2>& x, const pair<U1, U2>& y)
{
    if (auto cmp = x.first <=> y.first; cmp != 0)
    {
        return cmp;
    }
    return x.second <=> y.second;
}

template <typename T1, typename T2>
constexpr pair<typename ::std::decay_t<T1>, typename ::std::decay_t<T2>> make_pair(T1&& x, T2&& y)
{
    using PAIR_T = pair<::std::decay_t<T1>, ::std::decay_t<T2>>;
    return PAIR_T(::std::forward<T1>(x), ::std::forward<T2>(y));
}

template <typename T1, typename T2>
constexpr void swap(pair<T1, T2>& x, pair<T1, T2>& y) noexcept(noexcept(x.swap(y)))
{
    x.swap(y);
}

} // namespace lzl

#endif // LZL_PAIR_H
