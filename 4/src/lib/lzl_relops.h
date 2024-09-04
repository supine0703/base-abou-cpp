#ifndef LZL_RELOPS_H
#define LZL_RELOPS_H

namespace lzl
{

template <typename T>
constexpr bool operator!=(const T& x, const T& y)
{
    return !(x == y);
}

template <typename T>
constexpr bool operator>(const T& x, const T& y)
{
    return y < x;
}

template <typename T>
constexpr bool operator<=(const T& x, const T& y)
{
    return !(y < x);
}

template <typename T>
constexpr bool operator>=(const T& x, const T& y)
{
    return !(x < y);
}

} // namespace lzl

#endif // LZL_RELOPS_H
