#ifndef LZL_BASE_CAP_H
#define LZL_BASE_CAP_H

#include "utils/throw_if.h"

#include <cassert>
#include <cstdint>

namespace lzl::base
{

template <typename SIZE_T = size_t>
class _size
{
public:
    using size_type = SIZE_T;

    virtual ~_size() = default;

    size_type size() const { return m_size; }

    bool empty() const { return m_size == 0; }

protected:
    _size() : m_size(0) {}

    _size(size_type size) : m_size(size) {}

    void throw_if_empty(const char* name) const { lzl::utils::throw_if(empty(), name, "is empty"); }

    size_type m_size;
};


template <typename SIZE_T = size_t>
class _cap : public _size<SIZE_T>
{
public:
    using base_type = _size<SIZE_T>;
    using typename base_type::size_type;

    virtual ~_cap() = default;

    size_type capacity() const { return m_cap; }

    bool full() const { return m_size == m_cap; }

    using base_type::empty;
    using base_type::size;

protected:
    _cap() : base_type(), m_cap(0) {}

    _cap(size_type cap) : base_type(), m_cap(cap) {}

    _cap(size_type cap, size_type size) : base_type(size), m_cap(cap) { assert(size <= cap); }

    void throw_if_full(const char* name) const { lzl::utils::throw_if(full(), name, "is full"); }

    using base_type::throw_if_empty;

    using base_type::m_size;
    size_type m_cap;
};

} // namespace lzl::base

#endif // LZL_BASE_CAP_H
