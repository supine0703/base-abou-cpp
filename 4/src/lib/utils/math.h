#ifndef LZL_UTILS_MATH_H
#define LZL_UTILS_MATH_H

#include <limits>

namespace lzl::utils
{

template <typename T>
constexpr T max_value() noexcept
{
    // int lower overflow (0 - 1)
    // return ((static_cast<T>(static_cast<T>(-1) < 0) << ((sizeof(T) << 3) - 1)) - 1);
    // too complex
    // return static_cast<T>(-1) > 0
    //            ? static_cast<size_t>(static_cast<T>(-1))
    //            : (static_cast<size_t>(-1) << ((sizeof(T) << 3) - 1)) ^ static_cast<size_t>(-1);
    return std::numeric_limits<T>::max();
}

} // namespace lzl::utils

#endif // LZL_UTILS_MATH_H
