#include "throw_if.h"

#include <stdexcept>

void lzl::utils::throw_if(bool condition, const char* which, const char* what)
{
    if (condition)
    {
        throw std::out_of_range(
            std::string(which ? which : "unknow") + " " + (what ? what : "exception")
        );
    }
}
