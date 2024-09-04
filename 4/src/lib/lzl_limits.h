#ifndef LZL_LIMITS_H
#define LZL_LIMITS_H

#include "utils/math.h"

#include <algorithm>

#if defined(_WIN64) || defined(__x86_64__) || defined(__ppc64__)
    #define MAX_MEMORY_LIMIT 0x0000ffffffffffffULL // 48 bits
#else
    #define MAX_MEMORY_LIMIT 0x00ffffffUL // 32 bits
#endif

#define UNIT_BLOCK_MIN_SIZE 64

// #define __LZL_TEST 1

#if __LZL_TEST
    #define private public
    #define protected public
#endif

namespace lzl
{
// namespace interface
// {

template <typename T, typename SIZE_T = size_t>
class _max_size_interface
{
public:
    using size_type = SIZE_T;
    using value_type = T;

    virtual ~_max_size_interface() = default;

    /**
     * at <https://stackoverflow.com/questions/3813124/c-vector-max-size>
     * 
     * The "run-out of RAM" comment was regarding a 32-bit address space. 
     * There might be some CPUs with a 52-bit address space; 
     * I know Intel proposed a 57-bit addressing model, 
     * but I stand by the statement that they are "often" limited to 48 bits 
     *          --  Anthony Williams 
     *              <https://stackoverflow.com/users/5597/anthony-williams>
     * 
     * so I choose 24 bits for 32-bit address space and 48 bits for 64-bit address space.
     */
    constexpr size_type max_size() const noexcept
    {
        return static_cast<size_type>(::std::min(
            static_cast<size_t>(MAX_MEMORY_LIMIT / sizeof(value_type)),
            static_cast<size_t>(lzl::utils::max_value<size_type>())
        ));
    }
};

// } // namespace interface
} // namespace lzl

#endif // LZL_LIMITS_H
