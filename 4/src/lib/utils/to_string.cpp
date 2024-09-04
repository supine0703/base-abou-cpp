#include "to_string.h"

#include <cmath>

std::string lzl::utils::to_power_of_2(size_t num)
{
    if (num == 0)
    {
        return "0";
    }

    int n = static_cast<int>(std::log2(static_cast<double>(num)) + 0.5);
    size_t powerOfTwo = n == 64 ? static_cast<size_t>(-1) : (static_cast<size_t>(1) << n) - 1;
    // size_t powerOfTwo = (static_cast<size_t>(n < 64) << n) - 1;

    std::string res("2^" + std::to_string(n));

    if (--num > powerOfTwo)
    {
        res += " + " + std::to_string(num - powerOfTwo);
    }
    else if (num < powerOfTwo)
    {
        res += " - " + std::to_string(powerOfTwo - num);
    }
    return res;
}
