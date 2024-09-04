#ifndef LZL_UTILS_THROW_IF_H
#define LZL_UTILS_THROW_IF_H

namespace lzl::utils
{

void throw_if(bool condition, const char* which = nullptr, const char* what = nullptr);

} // namespace lzl::utils

#endif // LZL_UTILS_THROW_IF_H
